#include <iostream>
#include <string>
#include <vector>

#include "cli/command.h"
#include "cli/console.h"
#include "data/library.h"
#include "model/book.h"
#include "service/library_service.h"

using biblioteca::cli::Command;
using biblioteca::data::Library;
using biblioteca::model::Book;
using biblioteca::service::LibraryService;
namespace Console = biblioteca::cli::Console;

namespace {

void showHelp() {
    Console::title("Comandos");
    Console::table(
        {"comando", "o que faz"},
        {
            {"listar", "mostra o acervo"},
            {"buscar <termo>", "procura por título, autor ou gênero"},
            {"emprestar <livro> <membro>", "empresta um exemplar a um membro"},
            {"devolver <livro> <membro>", "devolve um exemplar"},
            {"membro <id>", "mostra os empréstimos de um membro"},
            {"ajuda", "mostra esta lista"},
            {"sair", "encerra o programa"},
        });
}

/**
 * Comando de referência: se ficar em dúvida sobre estilo, copie o que está
 * aqui.
 *
 * TODO (Tarefa 1): hoje a tabela mostra quantos exemplares a biblioteca tem
 * no total. Ela precisa mostrar quantos estão disponíveis agora. Veja o
 * enunciado.
 */
void showCatalog(const LibraryService& service) {
    Console::title("Acervo");

    std::vector<std::vector<std::string>> rows;
    for (const Book& book : service.catalog()) {
        rows.push_back({
            std::to_string(book.id),
            book.title,
            book.author,
            book.genre,
            std::to_string(book.copies),
        });
    }

    Console::table({"id", "título", "autor", "gênero", "exemplares"}, rows);
}

} // namespace

int main() {
    Library library;
    LibraryService service(library);

    Console::title("Biblioteca");
    Console::info("Digite 'ajuda' para ver os comandos, 'sair' para encerrar.");

    std::string line;
    while (true) {
        std::cout << "\n> ";
        if (!std::getline(std::cin, line)) {
            return 0;
        }

        auto parsed = Command::parse(line);
        if (!parsed) {
            continue;
        }
        Command command = *parsed;

        if (command.name == "ajuda") {
            showHelp();
        } else if (command.name == "listar") {
            showCatalog(service);
        } else if (command.name == "sair") {
            Console::info("Até mais.");
            return 0;
        } else if (command.name == "buscar" || command.name == "emprestar" ||
                   command.name == "devolver" || command.name == "membro") {
            // TODO (Tarefas 2 a 4): implementar os comandos novos aqui.
            Console::error("comando '" + command.name + "' ainda não implementado");
        } else {
            Console::error("não conheço o comando '" + command.name + "'. Tente 'ajuda'.");
        }
    }
}
