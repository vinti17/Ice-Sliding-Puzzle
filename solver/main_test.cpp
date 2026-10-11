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
const vector<vector<char>> UNSOLVABLE_CHALLENGE = {
    {'.', '.', 'x'},
    {'.', 'f', '.'},
    {'.', '.', '.'}};
const vector<vector<char>> CHALLENGE_0 = {
    {'.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', 'F'}};
const vector<vector<char>> CHALLENGE_1 = {
    {'.', '.', '.', '.', 'r', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', 'r', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'f', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'x', '.', '.'}};
const vector<vector<char>> CHALLENGE_2 = {
    {'.', '.', '.', '.', '.', 'r', '.'},
    {'r', '.', '.', '.', '.', '.', '.'},
    {'r', '.', 'f', '.', '.', '.', 'r'},
    {'.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', 'r', '.', '.'},
    {'.', 'r', '.', 'x', '.', '.', '.'}};
const vector<vector<char>> CHALLENGE_3 = {
    {'r', 'r', 'r', 'r', 'r', 'r', 'r'},
    {'.', '.', '.', '.', '.', '.', 'r'},
    {'.', 'r', 'r', 'r', '.', '.', '.'},
    {'.', '.', '.', 'x', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.'},
    {'.', 'r', '.', '.', '.', '.', '.'},
    {'f', '.', '.', '.', '.', 'r', '.'}};
const vector<vector<char>> CHALLENGE_4 = {
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'r', '.', '.'},
    {'r', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'r', '.', '.', '.'},
    {'.', '.', 'r', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', 'x', '.', 'r', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', 'r', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', 'f', '.', '.', '.', '.', 'r', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', 'r', '.', '.', '.', '.'},
    {'.', '.', '.', 'r', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', 'r', '.', 'r'},
    {'.', 'r', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.'}};

TEST(bfs, bad_format1)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT1, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format2)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT2, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format3)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT3, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, bad_format4)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = breadth_first(BAD_FORMAT4, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, no_solution)
{
    const int EXPECTED_STEPS = NO_SOLUTION;

    vector<Puzzle> solution_path;
    int actual = breadth_first(UNSOLVABLE_CHALLENGE, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(bfs, challenge0)
{
    const int EXPECTED_STEPS = 0;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_0, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(bfs, challenge1)
{
    const int EXPECTED_STEPS = 3;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_1, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(bfs, challenge2)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_2, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(bfs, challenge3)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_3, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(bfs, challenge4)
{
    const int EXPECTED_STEPS = 12;
    vector<Puzzle> solution_path;
    int actual = breadth_first(CHALLENGE_4, solution_path);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(dfs, bad_format1)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT1, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format2)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT2, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format3)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT3, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, bad_format4)
{
    const int EXPECTED_STEPS = BAD_FORMAT;

    vector<Puzzle> solution_path;
    int actual = depth_first(BAD_FORMAT4, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, no_solution)
{
    const int EXPECTED_STEPS = NO_SOLUTION;

    vector<Puzzle> solution_path;
    int actual = depth_first(UNSOLVABLE_CHALLENGE, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
}

TEST(dfs, challenge0)
{
    const int EXPECTED_STEPS = 0;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_0, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(dfs, challenge1)
{
    const int EXPECTED_STEPS = 3;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_1, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(dfs, challenge2)
{
    const int EXPECTED_STEPS = 4;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_2, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(dfs, challenge3)
{
    const int EXPECTED_STEPS = 6;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_3, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(dfs, challenge4)
{
    const int EXPECTED_STEPS = 12;
    vector<Puzzle> solution_path;
    int actual = depth_first(CHALLENGE_4, solution_path, NO_DEPTH_LIMIT);

    EXPECT_EQ(actual, EXPECTED_STEPS);
    EXPECT_EQ(size(solution_path), EXPECTED_STEPS + 1);
}

TEST(dfs, depth_limit)
{
    vector<Puzzle> solution_path;

    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 0), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 1), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 2), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 3), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 4), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 5), NO_SOLUTION);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 6), 6);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 7), 6);
    EXPECT_EQ(depth_first(CHALLENGE_3, solution_path, 8), 6);
}
