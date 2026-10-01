# Spec: Five-Letter Word Guessing Game

## Objective

Provide a self-contained C++ console game for one local player. Each round
selects a random five-letter answer from a built-in word bank. The player has
six valid guesses to solve it and receives Wordle-style positional feedback.

Success means a player can complete a round, understand every feedback marker,
and choose to replay without restarting the program.

## Tech Stack

- C++17
- C++ standard library only; no external dependencies
- `g++` compiler and a small custom test harness

## Commands

Build and run:

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp game.cpp -o word_guessing_game
./word_guessing_game
```

Run tests:

```bash
./test_runner.sh
```

## Project Structure

- `main.cpp` — console prompts, round lifecycle, feedback display, and replay.
- `game.h` / `game.cpp` — reusable validation, scoring, and answer-selection
  logic.
- `tests/game_tests.cpp` — dependency-free unit tests for game logic.
- `test_runner.sh` — compiles and executes the unit test binary in `/tmp`.
- `specs/` — feature specifications.

## Game Rules and Interfaces

- A round chooses one random answer from the internal five-letter word bank.
- A guess is valid only when it contains exactly five alphabetic characters;
  case does not matter. Invalid input does not consume an attempt.
- The player has six valid attempts.
- Each evaluated letter is shown as:
  - `[G]` — correct letter in the correct position.
  - `[Y]` — correct letter in a different position.
  - `[-]` — absent, including a duplicate beyond the answer's available count.
- Duplicate scoring evaluates exact-position matches before other present
  letters.
- A round ends immediately on five `[G]` results or after the sixth valid
  miss. The answer is disclosed on a loss.
- After each completed round, a response beginning with `y` or `Y` starts a
  new round; any other response exits.

The game-logic interface is intentionally small:

```cpp
enum class LetterState { Correct, Present, Absent };
using Feedback = std::array<LetterState, 5>;

bool isValidGuess(std::string_view guess);
Feedback evaluateGuess(std::string_view answer, std::string_view guess);
std::string chooseAnswer(std::mt19937& generator);
```

## Code Style

- Use C++17 and standard-library facilities only.
- Keep game rules deterministic and separate from terminal I/O so they can be
  unit-tested.
- Use descriptive `camelCase` function and variable names, `constexpr` for
  fixed values, and two-space indentation.
- Guard character-classification calls by converting to `unsigned char`.

```cpp
if (!isValidGuess(guess)) {
  std::cout << "Enter exactly five alphabetic letters.\n";
  continue;
}
```

## Testing Strategy

Use the custom C++ test harness in `tests/game_tests.cpp` for deterministic
logic. Cover valid and invalid guesses, case-insensitive exact matches,
present/absent feedback, duplicate-letter scoring, and answer selection.

For each behavioral change, add a focused test before implementation, run
`./test_runner.sh`, compile with warning flags, and manually check the
interactive win, loss, invalid-input, and replay paths.

## Boundaries

- Always: validate all console guesses before scoring, preserve deterministic
  game logic tests, compile with `-Wall -Wextra -Wpedantic`, and run tests
  before committing.
- Ask first: adding a dependency, changing the answer-bank source, adding
  saved scores or persistence, changing the test runner, or changing the
  six-attempt rule.
- Never: commit secrets or generated executables, remove tests to hide a
  failure, add networked features, or add GUI, account, leaderboard, or
  dictionary-validation behavior without an approved scope change.

## Success Criteria

- The program builds using the documented C++17 command without warnings.
- Every round uses a five-letter built-in answer and accepts at most six valid
  guesses.
- Invalid guesses leave the current attempt number unchanged.
- Feedback correctly distinguishes exact, present, and absent letters,
  including duplicate letters.
- Win, loss, answer reveal, and replay behavior work from the terminal.
- `./test_runner.sh` passes.

## Open Questions

None. Future work requiring a larger dictionary, difficulty levels, scoring,
or persistence needs a separate approved specification.
