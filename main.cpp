#include "game.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <string>

namespace {

constexpr int kMaxAttempts = 6;

char toUpper(char character) {
  return static_cast<char>(
      std::toupper(static_cast<unsigned char>(character)));
}

bool isWinningFeedback(const Feedback& feedback) {
  return std::all_of(feedback.begin(), feedback.end(), [](LetterState state) {
    return state == LetterState::Correct;
  });
}

void printFeedback(const std::string& guess, const Feedback& feedback) {
  std::cout << "Feedback: ";
  for (std::size_t index = 0; index < guess.size(); ++index) {
    const char letter = toUpper(guess[index]);
    switch (feedback[index]) {
      case LetterState::Correct:
        std::cout << "[G]";
        break;
      case LetterState::Present:
        std::cout << "[Y]";
        break;
      case LetterState::Absent:
        std::cout << "[-]";
        break;
    }
    std::cout << letter << ' ';
  }
  std::cout << "\n";
}

bool playRound(std::mt19937& generator) {
  const std::string answer = chooseAnswer(generator);

  std::cout << "\nGuess the five-letter word. You have " << kMaxAttempts
            << " attempts.\n";
  std::cout << "[G] correct position, [Y] present elsewhere, [-] absent\n";

  for (int attempt = 1; attempt <= kMaxAttempts;) {
    std::cout << "Guess " << attempt << '/' << kMaxAttempts << ": ";
    std::string guess;
    if (!std::getline(std::cin, guess)) {
      return false;
    }

    if (!isValidGuess(guess)) {
      std::cout << "Enter exactly five alphabetic letters.\n";
      continue;
    }

    const Feedback feedback = evaluateGuess(answer, guess);
    printFeedback(guess, feedback);
    if (isWinningFeedback(feedback)) {
      std::cout << "You won in " << attempt << " guess"
                << (attempt == 1 ? "!\n" : "es!\n");
      return true;
    }

    ++attempt;
  }

  std::cout << "Out of guesses. The word was " << answer << ".\n";
  return true;
}

bool wantsToPlayAgain() {
  std::cout << "Play again? (y/n): ";
  std::string response;
  if (!std::getline(std::cin, response)) {
    return false;
  }

  return !response.empty() && toUpper(response.front()) == 'Y';
}

}  // namespace

int main() {
  std::random_device randomDevice;
  std::mt19937 generator(randomDevice());

  std::cout << "Five-Letter Word Guessing Game\n";
  do {
    if (!playRound(generator)) {
      break;
    }
  } while (wantsToPlayAgain());

  std::cout << "Thanks for playing!\n";
  return 0;
}
