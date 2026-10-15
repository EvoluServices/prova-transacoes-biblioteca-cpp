#pragma once

#include <vector>

#include "data/library.h"
#include "model/book.h"

namespace biblioteca::service {

/**
 * Onde moram as regras da biblioteca.
 *
 * Nada aqui dentro imprime na tela nem lê do teclado. Esta classe recebe
 * perguntas e devolve dados. Quem conversa com o usuário é a camada de `cli`.
 */
class LibraryService {
public:
    explicit LibraryService(data::Library& library);

    /** O acervo inteiro, na ordem em que está cadastrado. */
    std::vector<model::Book> catalog() const;

    // TODO (Tarefa 1): quantos exemplares deste título estão livres agora?

    // TODO (Tarefa 2): busca por título, autor ou gênero.

    // TODO (Tarefa 3): emprestar e devolver, com as regras do enunciado.

    // TODO (Tarefa 4): o que um membro tem em mãos, e o que está atrasado.

private:
    data::Library& library_;
};

} // namespace biblioteca::service
