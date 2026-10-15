#include "data/library.h"

#include <algorithm>

namespace biblioteca::data {

using model::Book;
using model::Date;
using model::Loan;
using model::Member;

Library::Library()
    : books_{
          {1, "Duna", "Frank Herbert", "Ficção Científica", 3},
          {2, "Ensaio sobre a Cegueira", "José Saramago", "Romance", 2},
          {3, "Memórias Póstumas de Brás Cubas", "Machado de Assis", "Romance", 4},
          {4, "Cem Anos de Solidão", "Gabriel García Márquez", "Realismo Mágico", 2},
          {5, "O Hobbit", "J. R. R. Tolkien", "Fantasia", 3},
          {6, "Neuromancer", "William Gibson", "Ficção Científica", 1},
          {7, "A Revolução dos Bichos", "George Orwell", "Fábula", 2},
          {8, "O Cortiço", "Aluísio Azevedo", "Naturalismo", 1},
          {9, "Vidas Secas", "Graciliano Ramos", "Romance", 2},
          {10, "Fahrenheit 451", "Ray Bradbury", "Ficção Científica", 1},
          {11, "O Nome do Vento", "Patrick Rothfuss", "Fantasia", 2},
          {12, "Torto Arado", "Itamar Vieira Junior", "Romance", 3},
      },
      members_{
          {1, "Ana Prado"},
          {2, "Bruno Sales"},
          {3, "Carla Nunes"},
          {4, "Diego Farias"},
      },
      loans_{
          {1, 1, Date::today().minusDays(3)},
          {5, 1, Date::today().minusDays(20)},
          {6, 2, Date::today().minusDays(5)},
          {1, 3, Date::today().minusDays(10)},
      } {
}

std::optional<Book> Library::findBook(int id) const {
    auto it = std::find_if(books_.begin(), books_.end(),
                            [id](const Book& book) { return book.id == id; });
    if (it == books_.end()) {
        return std::nullopt;
    }
    return *it;
}

std::optional<Member> Library::findMember(int id) const {
    auto it = std::find_if(members_.begin(), members_.end(),
                            [id](const Member& member) { return member.id == id; });
    if (it == members_.end()) {
        return std::nullopt;
    }
    return *it;
}

} // namespace biblioteca::data
