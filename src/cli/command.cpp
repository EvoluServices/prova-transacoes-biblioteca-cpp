#include "cli/command.h"

#include <algorithm>
#include <cctype>
#include <sstream>

namespace biblioteca::cli {

std::optional<std::string> Command::argument(std::size_t index) const {
    if (index < arguments.size()) {
        return arguments[index];
    }
    return std::nullopt;
}

std::optional<Command> Command::parse(const std::string& line) {
    std::istringstream stream(line);
    std::vector<std::string> parts;
    std::string part;
    while (stream >> part) {
        parts.push_back(part);
    }

    if (parts.empty()) {
        return std::nullopt;
    }

    std::string name = parts.front();
    std::transform(name.begin(), name.end(), name.begin(),
                    [](unsigned char c) { return std::tolower(c); });

    std::vector<std::string> arguments(parts.begin() + 1, parts.end());
    return Command{name, arguments};
}

} // namespace biblioteca::cli
