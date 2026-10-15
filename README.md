# Prova prática — Biblioteca (C++)

Olá! Este é um programa **inacabado**. A ideia da prova é pegar um projeto que já existe,
entender como ele está organizado e terminá-lo mantendo a coerência.

---

## Como rodar

Você precisa de um compilador C++17 (g++, clang ou MSVC) e, opcionalmente, do CMake.
Duas opções de build, escolha a que preferir:

### Make

```bash
make run
```

### CMake

```bash
cmake -S . -B build
cmake --build build
./build/biblioteca      # Linux/macOS
.\build\biblioteca.exe  # Windows
```

No Windows, com o MinGW instalado (por exemplo o que vem com o Qt, ou o
[MSYS2](https://www.msys2.org/)), os dois comandos acima funcionam normalmente
dentro do Git Bash ou do PowerShell, desde que `g++`/`mingw32-make`/`cmake`
estejam no `PATH`. Com CMake, gere para o MinGW explicitamente se o padrão do
seu sistema for outro:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

Para rodar os testes:

```bash
make test
```

ou, com CMake:

```bash
cmake --build build
ctest --test-dir build --output-on-failure
```

## O que o programa já faz

Sobe um terminal interativo. Hoje respondem só três comandos:

- `ajuda` mostra a lista de comandos
- `listar` mostra o acervo em tabela
- `sair` encerra

Os outros comandos são reconhecidos, mas respondem "ainda não implementado".

O acervo já vem preenchido com livros, membros e **alguns empréstimos em
aberto** (um deles atrasado), como se a biblioteca tivesse acabado de abrir as
portas hoje.

## Como o projeto está organizado

```
cli  ──▶  service  ──▶  data
(terminal)  (regras)   (acervo em memória)
              │
            model  (os tipos do domínio)
```

| Pasta           | Responsabilidade |
|-----------------|------------------|
| `src/cli/`      | Lê o comando digitado e imprime. É a única camada que conhece o terminal |
| `src/model/`    | Os tipos do domínio: `Book`, `Member`, `Loan`, e um `Date` simples (ano/mês/dia) no lugar do `LocalDate` do Java |
| `src/data/`     | `Library`: guarda os dados e não conhece nenhuma regra |
| `src/service/`  | `LibraryService`: as regras da biblioteca |
| `src/main.cpp`  | O laço do terminal e o despacho dos comandos |
| `tests/`        | Teste de exemplo, com um "mini-framework" próprio (sem bibliotecas externas) |

Duas convenções que valem para o código novo:

1. **Camada de regra de negócio não imprime.** O `LibraryService` responde perguntas e
   devolve dados; quem escreve na tela é o `cli`.
2. **Toda impressão passa pelo `Console`.** Nos comandos novos, chame as
   funções dele em vez de `std::cout` direto.

O comando `listar` é a referência: se ficar em dúvida sobre estilo, copie o que
está lá.

> Sobre o `Date` (`src/model/date.h`): existe só porque o C++17 não tem um tipo
> de calendário pronto na biblioteca padrão (isso chegou só no C++20). Ele faz
> o que o `LocalDate` do Java fazia aqui: "hoje", "daqui a N dias" e comparar
> duas datas. Sinta-se livre para mudar, é só um meio, não um fim.

---

## As tarefas

Não é uma corrida: preferimos 2 tarefas bem feitas e explicadas a 4 atropeladas.

### Tarefa 1 — Disponibilidade no `listar`

Hoje a tabela mostra quantos exemplares a biblioteca **tem**. Ela precisa
mostrar quantos estão **livres agora**.

A biblioteca tem 3 exemplares de Duna. Se um está emprestado, sobram 2 na
prateleira, e emprestar um exemplar não pode fazer os outros dois sumirem da
listagem.

### Tarefa 2 — `buscar <termo>`

Procura por **título, autor ou gênero** e mostra o resultado no mesmo formato do
`listar`.

A busca tem que funcionar independente do jeito que a pessoa digita: `SARAMAGO` e `saramago`
acham o mesmo livro, e `solidao` encontra `Cem Anos de Solidão`. Termo que não
acha nada precisa dizer isso, e não sair em branco.

### Tarefa 3 — `emprestar` e `devolver`

```
emprestar <livro> <membro>
devolver  <livro> <membro>
```

As regras:

- O prazo de devolução é de **14 dias**.
- Um membro pode ter no máximo **3 empréstimos** ao mesmo tempo.
- Quem tem devolução **atrasada** não pega livro novo.

Você está livre, e é encorajado, a criar quaisquer outras regras de negócio que achar válidas.

Em qualquer recusa, diga ao usuário **o motivo**.

### Tarefa 4 — `membro <id>`

Mostra os empréstimos ativos do membro, com a data de devolução de cada um e
quais estão atrasados.

### Bônus (só se sobrar tempo)

Nenhum destes é obrigatório, e não fazer nenhum não tira ponto:

- **Testes** do que você escreveu de regra de negócio. `tests/` já tem um
  teste de exemplo para usar como modelo.
- Guardar os empréstimos em arquivo, para sobreviverem ao fim do programa.
- Um comando de relatório: tudo que está atrasado, de todos os membros.

---

## Regras

- **Sem bibliotecas externas.** Só a biblioteca padrão do C++ (STL).
- Pode consultar documentação, Stack Overflow e IA à vontade, **mas você vai
  conversar com a gente sobre o seu próprio código na entrevista.**
  Não entregue nada que você não saiba explicar e defender.
- Não precisa fazer interface gráfica, banco de dados, login, nem se preocupar
  com vários usuários ao mesmo tempo.

### Sobre o código que já está aqui

O projeto tem um jeito de fazer as coisas, mas **isso não é lei.** Você está
livre para mudar o que quiser: tipos, assinaturas, camadas, a organização das
pastas. A estrutura inteira, se for o caso. Trocar o que existe por algo melhor
**não é desrespeitar o enunciado, é o tipo de coisa que a gente quer ver.**

O que pedimos é só isto: **se você mudar algo estrutural, escreva por que no
`ENTREGA.md`.** Uma frase basta. Nos mostre o seu raciocínio.

Seguir o que já existe também é uma escolha válida. Só queremos saber se foi
escolha ou piloto automático.

## O que entregar

1. O projeto (repositório Git ou um `.zip`).
2. Um **`ENTREGA.md`** curto respondendo:
   - as decisões técnicas que você tomou e por quê
   - o que você mudou no que já existia, se mudou, e o que te incomodou ali
   - o que ficou de fora e o motivo
   - o que você faria diferente com mais tempo

Esse arquivo pesa tanto quanto o código. Boa prova!
