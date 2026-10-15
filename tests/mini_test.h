#pragma once

#include <iostream>
#include <string>

/**
 * Um "framework" de teste mínimo, só com a biblioteca padrão.
 *
 * Não é JUnit, mas resolve: cada `CHECK` que falhar imprime o que esperava e
 * o que recebeu, e o `main.cpp` do teste devolve 1 se alguma falhou (0 se
 * todas passaram). É só um modelo — sinta-se livre para trocar por algo
 * melhor, se preferir.
 */
namespace minitest {

inline int& failureCount() {
    static int count = 0;
    return count;
}

template <typename Expected, typename Actual>
void checkEquals(const char* file, int line, const Expected& expected, const Actual& actual,
                  const std::string& description) {
    if (!(expected == actual)) {
        failureCount()++;
        std::cerr << file << ":" << line << ": FALHOU — " << description << "\n"
                  << "  esperado: " << expected << "\n"
                  << "  obtido:   " << actual << "\n";
    }
}

inline void checkTrue(const char* file, int line, bool condition, const std::string& description) {
    if (!condition) {
        failureCount()++;
        std::cerr << file << ":" << line << ": FALHOU — " << description << "\n";
    }
}

} // namespace minitest

#define CHECK_EQUALS(expected, actual, description) \
    minitest::checkEquals(__FILE__, __LINE__, (expected), (actual), (description))

#define CHECK_TRUE(condition, description) \
    minitest::checkTrue(__FILE__, __LINE__, (condition), (description))
