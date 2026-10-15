#include "service/library_service.h"

namespace biblioteca::service {

using data::Library;
using model::Book;

LibraryService::LibraryService(Library& library) : library_(library) {
}

std::vector<Book> LibraryService::catalog() const {
    return library_.books();
}

} // namespace biblioteca::service
