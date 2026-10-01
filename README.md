# Five-Letter Word Guessing Game

A self-contained C++ console game inspired by Wordle. Guess the randomly
selected five-letter word in six valid attempts.

## Build and run

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp game.cpp -o word_guessing_game
./word_guessing_game
```

Each guess must contain exactly five alphabetic letters. Feedback uses:

- `[G]` for a letter in the correct position
- `[Y]` for a letter that appears elsewhere in the answer
- `[-]` for a letter not present in the remaining answer letters

The game handles repeated letters using standard Wordle-style scoring and asks
whether to start a new round after each win or loss.

## Tests

```bash
./test_runner.sh
```
