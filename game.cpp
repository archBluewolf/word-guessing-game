#include "game.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <vector>

namespace {

constexpr std::size_t kWordLength = 5;

const std::vector<std::string> kAnswers = {
    "apple", "beach", "brave", "candy", "crane", "dream", "flame",
    "grape", "house", "light", "maple", "ocean", "plant", "smile",
    "stone", "tiger", "water", "zebra",
};

char toUpper(char character) {
  return static_cast<char>(
      std::toupper(static_cast<unsigned char>(character)));
}

}  // namespace

bool isValidGuess(std::string_view guess) {
  return guess.size() == kWordLength &&
         std::all_of(guess.begin(), guess.end(), [](char character) {
           return std::isalpha(static_cast<unsigned char>(character));
         });
}

Feedback evaluateGuess(std::string_view answer, std::string_view guess) {
  Feedback feedback{};
  feedback.fill(LetterState::Absent);

  std::array<int, 26> remaining{};
  for (std::size_t index = 0; index < kWordLength; ++index) {
    const char answerLetter = toUpper(answer[index]);
    const char guessLetter = toUpper(guess[index]);

    if (answerLetter == guessLetter) {
      feedback[index] = LetterState::Correct;
    } else {
      ++remaining[answerLetter - 'A'];
    }
  }

  for (std::size_t index = 0; index < kWordLength; ++index) {
    if (feedback[index] == LetterState::Correct) {
      continue;
    }

    const int letterIndex = toUpper(guess[index]) - 'A';
    if (remaining[letterIndex] > 0) {
      feedback[index] = LetterState::Present;
      --remaining[letterIndex];
    }
  }

  return feedback;
}

std::string chooseAnswer(std::mt19937& generator) {
  std::uniform_int_distribution<std::size_t> distribution(0,
                                                           kAnswers.size() - 1);
  return kAnswers[distribution(generator)];
}
