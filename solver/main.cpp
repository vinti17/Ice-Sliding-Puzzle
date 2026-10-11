#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>
#include <algorithm>
#include <limits>

using namespace std;

const char ICE_CELL = '.';
const char ROCK_CELL = 'r';
const char FLAMINGO_CELL = 'f';
const char FLAMINGO_ON_RESCUE_CELL = 'F';
const char RESCUE_CELL = 'x';
const char UNKNOWN_CELL = '?';

const int NO_SOLUTION = -1;    // Puzzle has no solution
const int BAD_FORMAT = -2;     // Puzzle field has an invalid format
const int NO_PARENT = -1;      // Index of the parent of the root candidate
const int NO_DEPTH_LIMIT = -1; // Do not use a depth limit in depth first search

enum Action
{
    MoveNorth = 0,
    MoveEast,
    MoveSouth,
    MoveWest,
};

struct Pos
{
    int row;
    int col;
};

struct Puzzle
{
    vector<vector<char>> board;
    Pos flamingo;
    int parent;
};

ostream &operator<<(ostream &os, const Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: `puzzle` has been printed to `os`
     */
    int rows = puzzle.board.size();
    int columns = puzzle.board.at(0).size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            os << puzzle.board.at(i).at(j);
        os << '\n';
    }
    return os;
}

bool operator==(const Puzzle &lhs, const Puzzle &rhs)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if `lhs` and `rhs` have the same puzzle state
     */
    if (lhs.board.size() != rhs.board.size())
        return false;

    for (int i = 0; i < static_cast<int>(lhs.board.size()); i++)
        for (int j = 0; j < static_cast<int>(lhs.board.at(i).size()); j++)
            if (lhs.board.at(i).at(j) != rhs.board.at(i).at(j))
                return false;

    return true;
}

bool operator!=(const Puzzle &lhs, const Puzzle &rhs)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if `!(lhs == rhs)`
     */
    return !(lhs == rhs);
}

vector<vector<char>> read_field(istream &is)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is the field that has been read from `is`
     */
    vector<vector<char>> field;
    vector<char> line;
    char c;

    // Convert `is` to a 2d array of chars.
    while (is.get(c))
    {
        if (c == '\n')
        {
            field.push_back(line);
            line = {};
        }
        else
        {
            line.push_back(c);
        }
    }

    if (!line.empty())
    {
        field.push_back(line);
    }

    return field;
}

int load_puzzle(vector<vector<char>> field, Puzzle &puzzle)
{
    // Precondition:
    assert(true);
    /*  Postcondition: return value is true if `field` denotes a valid puzzle, in which case `field` has been parsed into `puzzle` */

    int rows = field.size();
    int columns = field[0].size();
    int flamingo = 0;
    int rescue = 0;
    int flamingo_on_rescue = 0;

    if (rows == 0 || field.at(0).empty()) // the puzzle is empty
        return 0;

    for (int i = 0; i < rows; i++)
    {
        if (static_cast<int>(field.at(i).size()) != columns) // we check that all rows have the same number of characters
            return BAD_FORMAT;

        for (int j = 0; j < columns; j++)
            if (field.at(i).at(j) == FLAMINGO_CELL)
                flamingo++;
            else if (field.at(i).at(j) == RESCUE_CELL)
                rescue++;
            else if (field.at(i).at(j) == FLAMINGO_ON_RESCUE_CELL)
                flamingo_on_rescue++;
    }

    if (flamingo + flamingo_on_rescue != 1 || (rescue == 0 && flamingo > 0)) // there must be only one flamingo and if there is 'f' there also must be a rescue cell for it
        return BAD_FORMAT;

    puzzle.board = field;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (field[i][j] == FLAMINGO_CELL || field[i][j] == FLAMINGO_ON_RESCUE_CELL)
            {
                puzzle.flamingo = {i, j}; // we get the position of the flamingo
                return 0;
            }

    return 0;
}

bool open_puzzle(string file, Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if a puzzle has been successfully read from filename `file` into `puzzle`
     */
    ifstream fs(file);
    vector<vector<char>> field = read_field(fs);

    if (!fs.is_open())
    {
        cout << "Failed to open file" << endl;
        return false;
    }
    else if (load_puzzle(field, puzzle) == BAD_FORMAT)
    {
        cout << "Puzzle has bad format" << endl;
        return false;
    }

    cout << "Loaded the puzzle shown below:\n";
    cout << puzzle << endl;

    return true;
}

bool is_solved(const Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if the flamingo is at the rescue position in `puzzle`
     */
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            char cell = puzzle.board.at(i).at(j);
            if (cell == FLAMINGO_ON_RESCUE_CELL) // if 'F' is on the board, then it means that the flamingo is on the rescue cell
                return true;
        }
    return false;
}

bool is_solvable(const Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if the flamingo in `puzzle` is alive
     */
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            char cell = puzzle.board.at(i).at(j); // we only check if 'f' exists on the board
            if (cell == FLAMINGO_CELL)
                return true;
        }
    return false;
}

Pos find_flamingo(const Puzzle &puzzle)
{
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();
    int row = -1;
    int col = -1;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            char cell = puzzle.board[i][j];
            if (cell == FLAMINGO_CELL || cell == FLAMINGO_ON_RESCUE_CELL) // finds the position of the flamingo
            {
                row = i;
                col = j;
            }
        }
    return {row, col};
}

bool valid_position(const Puzzle &puzzle, int i, int j)
{
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();

    return (i >= 0 && i < rows && j >= 0 && j < columns); // we check if the cell is out of bounds
}

bool valid_puzzle(const Puzzle &puzzle)
{
    // Precondition:
    assert(true);
    // Postcondition:

    if (is_solvable(puzzle) || is_solved(puzzle))
        return true;
    return false;
}

void process_move(int direction, Puzzle &puzzle, int &i, int &j)
{
    Action action = static_cast<Action>(direction);
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();

    switch (action)
    {
    case MoveNorth:
        while (((i > 0 && puzzle.board[i - 1][j] != ROCK_CELL) || i == 0) && puzzle.board[i][j] != RESCUE_CELL)
            i--;
        break;
    case MoveEast:
        while (((j < columns - 1 && puzzle.board[i][j + 1] != ROCK_CELL) || j == columns - 1) && puzzle.board[i][j] != RESCUE_CELL)
            j++;
        break;
    case MoveSouth:
        while (((i < rows - 1 && puzzle.board[i + 1][j] != ROCK_CELL) || i == rows - 1) && puzzle.board[i][j] != RESCUE_CELL)
            i++;
        break;
    case MoveWest:
        while (((j > 0 && puzzle.board[i][j - 1] != ROCK_CELL) || j == 0) && puzzle.board[i][j] != RESCUE_CELL)
            j--;
        break;
    }

    Pos pos = {i, j};
    puzzle.board[puzzle.flamingo.row][puzzle.flamingo.col] = ICE_CELL; // we replace the initial position of the flamingo with an ice cell and we update it

    if (valid_position(puzzle, i, j)) // only if that the flamingo did not slide off
    {
        if (puzzle.board[i][j] == RESCUE_CELL)
            puzzle.board[i][j] = FLAMINGO_ON_RESCUE_CELL; // if the flamingo lands on a rescue cell, the cell will become 'F'
        else
        {
            puzzle.board[i][j] = FLAMINGO_CELL; // otherwise, we simply update the position of the flamingo
            puzzle.flamingo = pos;
        }
    }
}

void try_move(vector<Puzzle> &path, int direction, int index)
{
    Puzzle candidate;
    candidate = path.at(index);
    candidate.flamingo = find_flamingo(candidate);
    int i = candidate.flamingo.row;
    int j = candidate.flamingo.col;

    process_move(direction, candidate, i, j);
    if (valid_puzzle(candidate))
    {
        candidate.parent = index;
        path.push_back(candidate);
    }
}

void load_solution_path(const vector<Puzzle> &path, vector<Puzzle> &solution_path, int index, int &steps)
{
    // Precondition:
    assert(true);
    /* Postcondition: */

    while (index != 0)
    {
        solution_path.push_back(path.at(index));
        index = path.at(index).parent;
        steps++;
    }

    solution_path.push_back(path.at(index));
}

int solve_bfs(Puzzle initial_puzzle, vector<Puzzle> &path, vector<Puzzle> &solution_path)
{
    // Precondition:
    assert(true);
    /* Postcondition: */

    int index = 0;
    int steps = 0;
    initial_puzzle.flamingo = find_flamingo(initial_puzzle);
    initial_puzzle.parent = NO_PARENT;
    path.push_back(initial_puzzle);

    while (index < static_cast<int>(path.size()) && !is_solved(path.at(index)))
    {
        for (int direction = 0; direction < 4; direction++)
            try_move(path, direction, index);

        index++;
    }

    // If the whole frontier was explored without ever reaching a solved state,
    // `index` now equals `path.size()`: the puzzle has no solution. Returning
    // here avoids an out-of-range `path.at(index)` in load_solution_path.
    if (index == static_cast<int>(path.size()))
        return NO_SOLUTION;

    load_solution_path(path, solution_path, index, steps);

    return steps;
}

/*
 * Breath first search
 */

int breadth_first(const vector<vector<char>> &field, vector<Puzzle> &solution_path)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is the minimal number of steps needed to solve the puzzle represented by `field` in which case `solution_path`
        will contain the solution path, or `BAD_FORMAT` if `field` does not represent a valid puzzle, or `NO_SOLUTION` if the puzzle has no solutions
    */
    // TODO: Implement this function.
    // Remember to first validate and convert `field` into your own Puzzle data structure before starting your search.
    // You are encouraged to implement and use a helper function to perform the actual breadth first search, which given at least the initial Puzzle state produces a solution path.
    // That way you are free to choose your own parameters and their types.

    // As we want to extract the solution path, rather than show it as demonstrated in the lecture, we need to use a slightly different approach:
    /*
        extract_path(C, i):
            if i == NO_PARENT: return {} // empty vector
            else:
                i' = C.at(i).parent_candidate;
                path = extract_path(C, i');
                path.push_back(C.at(i).candidate);
                return path;
    */
    Puzzle puzzle;
    vector<Puzzle> path;

    if (load_puzzle(field, puzzle) == BAD_FORMAT)
        return BAD_FORMAT;

    int steps = solve_bfs(puzzle, path, solution_path);

    if (steps == NO_SOLUTION)
        return NO_SOLUTION;

    reverse(solution_path.begin(), solution_path.end());

    return steps;
}

void improve(vector<Puzzle> &best, vector<Puzzle> &current)
{
    // Precondition:
    assert(true);
    /* Postcondition: */
    best.clear();
    for (int i = 0; i < static_cast<int>(current.size()); i++)
        best.push_back(current.at(i));
}

bool has_occured(vector<Puzzle> &current, Puzzle puzzle)
{
    // Precondition:
    assert(true);
    // Postcondition:

    for (int i = 0; i < static_cast<int>(current.size()); i++)
        if (current.at(i) == puzzle)
            return true;
    return false;
}

int solve_dfs(Puzzle initial_puzzle, vector<Puzzle> &best_attempt, vector<Puzzle> &current_attempt, int steps, int &shortest_solution)
{
    // Precondition:
    assert(true);
    /* Postcondition */

    if (is_solved(initial_puzzle))
    {
        if (best_attempt.size() == 0 || current_attempt.size() < best_attempt.size())
            improve(best_attempt, current_attempt);
        return steps;
    }

    if (steps >= shortest_solution)
        return shortest_solution;

    for (int direction = 0; direction < 4; direction++)
    {
        Puzzle puzzle = initial_puzzle;
        puzzle.flamingo = find_flamingo(initial_puzzle);
        int i = puzzle.flamingo.row;
        int j = puzzle.flamingo.col;

        process_move(direction, puzzle, i, j);

        if (valid_puzzle(puzzle) && (!has_occured(current_attempt, puzzle) || current_attempt.empty()))
        {
            current_attempt.push_back(puzzle);
            int solution = solve_dfs(puzzle, best_attempt, current_attempt, steps + 1, shortest_solution);
            if (solution < shortest_solution)
                shortest_solution = solution;
            current_attempt.pop_back(); // backtrack: remove this move so siblings start from the same path
        }
    }

    return shortest_solution;
}

/*
 * Depth first search
 */

int depth_first(const vector<vector<char>> &field, vector<Puzzle> &solution_path, int depth_limit)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is the minimal number of steps needed to solve the puzzle represented by `field` in which case `solution_path`
        will contain the solution path, or `BAD_FORMAT` if `field` does not represent a valid puzzle, or `NO_SOLUTION` if the puzzle has no solutions
    */
    // TODO: Implement this function.
    // Remember to first validate and convert `field` into your own Puzzle data structure before starting your search.
    // You are encouraged to implement and use a recursive helper function to perform the actual depth first search, which given at least the initial Puzzle state and a depth limit produces a solution path.
    // That way you are free to choose your own parameters and their types.
    Puzzle puzzle;
    vector<Puzzle> best_attempt;
    vector<Puzzle> current_attempt;
    int shortest_solution = numeric_limits<int>::max();

    if (load_puzzle(field, puzzle) == BAD_FORMAT)
        return BAD_FORMAT;

    int steps = solve_dfs(puzzle, best_attempt, current_attempt, 0, shortest_solution);

    solution_path.push_back(puzzle);
    for (int i = 0; i < static_cast<int>(best_attempt.size()); i++)
        solution_path.push_back(best_attempt.at(i));

    if ((depth_limit != -1 && steps > depth_limit) || steps == numeric_limits<int>::max())
        return NO_SOLUTION;
    else
        return steps;
}

/*
 * Main
 */

#ifndef TESTING
int main()
{ // Precondition:
    assert(true);
    /*  Postcondition: the user chosen puzzle file has been read and a solution path printed to `cout` if one exists
     */
    string filename, algorithm;
    int depth_limit, steps;
    vector<Puzzle> solution_path;
    Puzzle puzzle;

    cout << "Enter file to open: ";
    getline(cin, filename);

    ifstream puzzle_file(filename);

    if (!open_puzzle(filename, puzzle))
    {
        return 1;
    }
    else if (is_solved(puzzle))
    {
        cout << "This puzzle is already solved!" << endl;
        return 0;
    }

    vector<vector<char>> field = read_field(puzzle_file);

    cout << "Enter algorithm (dfs/bfs): ";
    getline(cin, algorithm);

    if (algorithm == "dfs")
    {
        cout << "Enter depth limit (" << NO_DEPTH_LIMIT << " = no limit): ";
        cin >> depth_limit;

        steps = depth_first(field, solution_path, depth_limit);
    }
    else if (algorithm == "bfs")
    {
        steps = breadth_first(field, solution_path);
    }
    else
    {
        cout << "Unknown algorithm" << endl;
        return 2;
    }

    if (steps == BAD_FORMAT)
    {
        cout << "Puzzle configuration is not valid" << endl;
    }
    else if (steps == NO_SOLUTION)
    {
        cout << "No solution found" << endl;
    }
    else
    {
        for (int i = 0; i < static_cast<int>(size(solution_path)); i++)
        {
            cout << solution_path.at(i) << endl;
        }

        cout << "Found solution in " << steps << " step(s)" << endl;
    }

    return 0;
}
#endif