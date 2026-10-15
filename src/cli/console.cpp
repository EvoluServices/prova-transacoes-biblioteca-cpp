#include "cli/console.h"

#include <algorithm>
#include <iostream>

namespace biblioteca::cli::Console {

namespace {

/**
 * Quantidade de "caracteres visíveis" de uma string UTF-8.
 *
 * `std::string::size()` conta bytes, e acentos (ã, ç, é...) ocupam 2 bytes em
 * UTF-8. Sem isso, a tabela desalinha toda vez que uma célula tem acento.
 * Só conta os bytes que não são continuação (`10xxxxxx`).
 */
std::size_t displayWidth(const std::string& text) {
    std::size_t width = 0;
    for (unsigned char c : text) {
        if ((c & 0xC0) != 0x80) {
            width++;
        }
    }
    return width;
}

std::string pad(const std::vector<std::string>& cells, const std::vector<std::size_t>& widths) {
    std::string line;
    for (std::size_t index = 0; index < cells.size(); index++) {
        line += cells[index];
        if (index + 1 < cells.size()) {
            line.append(widths[index] - displayWidth(cells[index]), ' ');
            line += "  ";
        }
    }
    return line;
}

} // namespace

void title(const std::string& text) {
    std::cout << "\n";
    std::string upper = text;
    std::transform(upper.begin(), upper.end(), upper.begin(),
                    [](unsigned char c) { return std::toupper(c); });
    std::cout << upper << "\n";
    std::cout << std::string(displayWidth(text), '-') << "\n";
}

void info(const std::string& text) {
    std::cout << text << "\n";
}

void error(const std::string& text) {
    std::cout << "erro: " << text << "\n";
}

void table(const std::vector<std::string>& headers,
           const std::vector<std::vector<std::string>>& rows) {
    if (rows.empty()) {
        info("(nada para mostrar)");
        return;
    }

    std::vector<std::size_t> widths;
    for (std::size_t column = 0; column < headers.size(); column++) {
        std::size_t width = displayWidth(headers[column]);
        for (const auto& row : rows) {
            width = std::max(width, displayWidth(row[column]));
        }
        widths.push_back(width);
    }

    std::cout << pad(headers, widths) << "\n";

    std::string separator;
    for (std::size_t index = 0; index < widths.size(); index++) {
        separator += std::string(widths[index], '-');
        if (index + 1 < widths.size()) {
            separator += "  ";
        }
    }
    std::cout << separator << "\n";

    for (const auto& row : rows) {
        std::cout << pad(row, widths) << "\n";
    }
}

} // namespace biblioteca::cli::Console
