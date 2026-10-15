#include <iostream>

#include "cli/command.h"
#include "mini_test.h"

/**
 * Teste de exemplo — serve de modelo caso você escreva os seus (é bônus).
 */

using biblioteca::cli::Command;

namespace {

void quebraALinha() {
    Command command = Command::parse("emprestar 1 3").value();

    CHECK_EQUALS(std::string("emprestar"), command.name, "nome do comando");
    CHECK_TRUE(command.arguments == std::vector<std::string>({"1", "3"}), "argumentos do comando");
}

void ignoraEspacos() {
    Command command = Command::parse("   LISTAR   ").value();

    CHECK_EQUALS(std::string("listar"), command.name, "nome em caixa baixa");
    CHECK_TRUE(command.arguments.empty(), "sem argumentos");
}

void linhaEmBranco() {
    CHECK_TRUE(!Command::parse("    ").has_value(), "linha em branco devolve vazio");
}

} // namespace

int main() {
    quebraALinha();
    ignoraEspacos();
    linhaEmBranco();

    int failures = minitest::failureCount();
    if (failures == 0) {
        std::cout << "OK — todos os testes passaram.\n";
        return 0;
    }
    std::cout << failures << " teste(s) falharam.\n";
    return 1;
}
