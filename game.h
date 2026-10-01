#ifndef WORD_GUESSING_GAME_H
#define WORD_GUESSING_GAME_H

#include <array>
#include <random>
#include <string>
#include <string_view>

enum class LetterState { Correct, Present, Absent };

using Feedback = std::array<LetterState, 5>;

bool isValidGuess(std::string_view guess);
Feedback evaluateGuess(std::string_view answer, std::string_view guess);
std::string chooseAnswer(std::mt19937& generator);

#endif
