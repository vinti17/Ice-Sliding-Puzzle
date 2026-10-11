#include "main.cpp"
#include "gtest/gtest.h"

const vector<vector<char>> BAD_FORMAT1 = {
    {'.', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', '?'}};
const vector<vector<char>> BAD_FORMAT2 = {
    {'.', '.', '.'},
    {'.', 'f', '.', '.'},
    {'.', '.', '.'}};
const vector<vector<char>> BAD_FORMAT3 = {
    {'.', '.', '.'},
    {'.', '.', '.'},
    {'.', '.', '.'}};
const vector<vector<char>> BAD_FORMAT4 = {
    {'.', '.', '.'},
    {'.', 'f', '.'},
    {'.', '.', 'f'}};
const vector<vector<char>> CHALLENGE_1 = {
    {'.', '.', '.', '.', 'r', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', 'r', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'f', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'x', '.', '.'}};
const vector<vector<char>> CHALLENGE_1_n = {
    {'.', '.', '.', '.', 'r', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'f', '.', '.', '.', 'r', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'x', '.', '.'}};
const vector<vector<char>> CHALLENGE_1_ne = {
    {'.', '.', '.', '.', 'r', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'f', 'r', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'x', '.', '.'}};
const vector<vector<char>> CHALLENGE_1_nes = {
    {'.', '.', '.', '.', 'r', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', 'r', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'F', '.', '.'}};

TEST(loading, bad_format1)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT1, puzzle));
}

TEST(loading, bad_format2)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT2, puzzle));
}

TEST(loading, bad_format3)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT3, puzzle));
}

TEST(loading, bad_format4)
{
    Puzzle puzzle;
    EXPECT_FALSE(load_puzzle(BAD_FORMAT4, puzzle));
}

TEST(loading, ok)
{
    Puzzle puzzle;
    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_n, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_ne, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_nes, puzzle));
}

TEST(puzzle, is_solvable)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_TRUE(is_solvable(puzzle)); // the test works fine until here

    Puzzle initial_puzzle = puzzle;
    int steps = 0;
    Pos pos = find_flamingo(puzzle);
    int i = pos.row;
    int j = pos.col;
    process_move(MoveNorth, puzzle, initial_puzzle, steps, i, j); // for some reason it does not work and I do not know why because in main it worked just fine in doing the action and updating the puzzle

    EXPECT_TRUE(is_solvable(puzzle));

    process_move(MoveWest, puzzle, puzzle, steps, i, j);

    EXPECT_FALSE(is_solvable(puzzle));
}

TEST(is_solved, challenge_1)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, challenge_1_n)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_n, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, challenge_1_ne)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_ne, puzzle));
    EXPECT_FALSE(is_solved(puzzle));
}

TEST(is_solved, challenge_1_nes)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_nes, puzzle));
    EXPECT_TRUE(is_solved(puzzle));
}

TEST(move, north)
{
    Puzzle puzzle;
    Puzzle expected;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_TRUE(load_puzzle(CHALLENGE_1_n, expected));

    Puzzle initial_puzzle = puzzle;
    int steps = 0;
    Pos pos = find_flamingo(puzzle);
    int i = pos.row;
    int j = pos.col;
    process_move(MoveNorth, puzzle, initial_puzzle, steps, i, j); // for some reason the function cannot update puzzle and therefore fails the test here too

    EXPECT_EQ(puzzle, expected);
}

TEST(find_flamingo, CHALLENGE_1)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1, puzzle));
    EXPECT_EQ(find_flamingo(puzzle).row, 4);
    EXPECT_EQ(find_flamingo(puzzle).col, 4);
}

TEST(find_flamingo, CHALLENGE_1_ne)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_ne, puzzle));
    EXPECT_EQ(find_flamingo(puzzle).row, 1);
    EXPECT_EQ(find_flamingo(puzzle).col, 7);
}

TEST(valid_position, CHALLENGE_1_ne)
{
    Puzzle puzzle;

    EXPECT_TRUE(load_puzzle(CHALLENGE_1_ne, puzzle));
    EXPECT_FALSE(valid_position(puzzle, -1, 1));
    EXPECT_TRUE(valid_position(puzzle, 2, 3));
    EXPECT_FALSE(valid_position(puzzle, 6, 4));
}
