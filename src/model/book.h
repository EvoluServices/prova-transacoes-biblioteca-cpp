#pragma once

#include <string>

namespace biblioteca::model {

/**
 * Um título do acervo.
 *
 * `copies` é a quantidade de exemplares físicos que a biblioteca possui.
 */
struct Book {
    int id;
    std::string title;
    std::string author;
    std::string genre;
    int copies;
};

} // namespace biblioteca::model
