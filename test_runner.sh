#!/bin/bash

set -euo pipefail

test_binary=$(mktemp /tmp/word_guessing_game_tests.XXXXXX)
trap 'rm -f "$test_binary"' EXIT

g++ -std=c++17 -Wall -Wextra -Wpedantic game.cpp tests/game_tests.cpp -I. -o "$test_binary"
"$test_binary"
