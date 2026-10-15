#pragma once

#include "model/date.h"

namespace biblioteca::model {

/**
 * Um empréstimo.
 *
 * Vem com o mínimo: quem pegou, o que pegou e quando. Se precisar de mais
 * informação para resolver as tarefas, sinta-se livre para mudar este tipo.
 */
struct Loan {
    int bookId;
    int memberId;
    Date borrowedAt;
};

} // namespace biblioteca::model
