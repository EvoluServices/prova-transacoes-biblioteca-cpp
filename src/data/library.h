#pragma once

#include <optional>
#include <vector>

#include "model/book.h"
#include "model/loan.h"
#include "model/member.h"

namespace biblioteca::data {

/**
 * O acervo da biblioteca, em memória.
 *
 * Faz o papel de banco de dados: guarda os dados e não conhece nenhuma regra.
 * Os empréstimos já vêm com alguns registros em aberto.
 */
class Library {
public:
    Library();

    const std::vector<model::Book>& books() const { return books_; }
    const std::vector<model::Member>& members() const { return members_; }

    const std::vector<model::Loan>& loans() const { return loans_; }
    std::vector<model::Loan>& loans() { return loans_; }

    std::optional<model::Book> findBook(int id) const;
    std::optional<model::Member> findMember(int id) const;

private:
    std::vector<model::Book> books_;
    std::vector<model::Member> members_;
    std::vector<model::Loan> loans_;
};

} // namespace biblioteca::data
