#include "game.h"

#include <cstdlib>
#include <iostream>
#include <random>
#include <string>

namespace {

void require(bool condition, const std::string& message) {
  if (!condition) {
    std::cerr << "Test failed: " << message << '\n';
    std::exit(1);
  }
}

void testGuessValidation() {
  require(isValidGuess("crane"), "five lowercase letters are valid");
  require(isValidGuess("CRANE"), "five uppercase letters are valid");
  require(!isValidGuess("four"), "short guesses are invalid");
  require(!isValidGuess("longer"), "long guesses are invalid");
  require(!isValidGuess("cr4ne"), "nonalphabetic guesses are invalid");
}

void testFeedback() {
  const Feedback feedback = evaluateGuess("APPLE", "ALLEY");

  require(feedback[0] == LetterState::Correct,
          "exact letters are marked correct");
  require(feedback[1] == LetterState::Present,
          "letters elsewhere in the answer are marked present");
  require(feedback[2] == LetterState::Absent,
          "letters beyond the answer count are marked absent");
  require(feedback[3] == LetterState::Present,
          "a letter elsewhere in the answer is marked present");
  require(feedback[4] == LetterState::Absent,
          "missing letters are marked absent");
}

void testExactMatchFeedback() {
  const Feedback feedback = evaluateGuess("APPLE", "apple");

  for (const LetterState state : feedback) {
    require(state == LetterState::Correct,
            "case-insensitive exact guesses mark every letter correct");
  }
}

void testDuplicateLetterFeedback() {
  const Feedback feedback = evaluateGuess("SHEEP", "PEEPS");

  require(feedback[0] == LetterState::Present,
          "a misplaced letter is present");
  require(feedback[1] == LetterState::Present,
          "the second available duplicate is present");
  require(feedback[2] == LetterState::Correct,
          "exact duplicate matches take priority");
  require(feedback[3] == LetterState::Absent,
          "extra duplicate guesses are absent");
  require(feedback[4] == LetterState::Present,
          "another available letter remains present");
}

void testRandomAnswer() {
  std::mt19937 generator(42);
  const std::string answer = chooseAnswer(generator);

  require(isValidGuess(answer), "random answers are five-letter words");
}

}  // namespace

int main() {
  testGuessValidation();
  testFeedback();
  testExactMatchFeedback();
  testDuplicateLetterFeedback();
  testRandomAnswer();

  std::cout << "All game logic tests passed.\n";
  return 0;
}
