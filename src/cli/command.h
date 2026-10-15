#pragma once

#include <optional>
#include <string>
#include <vector>

namespace biblioteca::cli {

/**
 * Uma linha digitada no terminal, já quebrada em nome e argumentos.
 *
 * `emprestar 1 3` vira `Command{"emprestar", {"1", "3"}}`.
 */
struct Command {
    std::string name;
    std::vector<std::string> arguments;

    std::optional<std::string> argument(std::size_t index) const;

    /** Devolve vazio quando a linha está em branco. */
    static std::optional<Command> parse(const std::string& line);
};

} // namespace biblioteca::cli
