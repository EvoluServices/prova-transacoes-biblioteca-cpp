#pragma once

#include <string>
#include <vector>

namespace biblioteca::cli::Console {

/**
 * Tudo que o programa escreve na tela passa por aqui.
 *
 * Ao implementar os comandos novos, chame estas funções em vez de usar
 * `std::cout` direto. Dois motivos: o `buscar` sai com a mesma cara do
 * `listar`, e mudar o formato da tabela num lugar só muda em todos os
 * comandos de uma vez.
 */

void title(const std::string& text);
void info(const std::string& text);
void error(const std::string& text);

/** Imprime uma tabela alinhando as colunas pela maior célula de cada uma. */
void table(const std::vector<std::string>& headers,
           const std::vector<std::vector<std::string>>& rows);

} // namespace biblioteca::cli::Console
