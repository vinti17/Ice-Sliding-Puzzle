#include <iostream>
#include <vector>
#include <fstream>
#include <cassert>

using namespace std;

const char ICE_CELL = '.';
const char ROCK_CELL = 'r';
const char FLAMINGO_CELL = 'f';
const char FLAMINGO_ON_RESCUE_CELL = 'F';
const char RESCUE_CELL = 'x';
const char UNKNOWN_CELL = '?';

enum Action
{
    MoveNorth,
    MoveEast,
    MoveSouth,
    MoveWest,
    Reset,
    Quit,
    Invalid
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
};

bool operator==(const Puzzle &lhs, const Puzzle &rhs)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if `lhs` and `rhs` have the same puzzle state
     */
    if (lhs.board.size() != rhs.board.size())
        return false;

    for (int i = 0; i < static_cast<int>(lhs.board.size()); i++)
        for (int j = 0; j < static_cast<int>(lhs.board[i].size()); j++)
            if (lhs.board[i][j] != rhs.board[i][j])
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
            char cell = puzzle.board[i][j];
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
            char cell = puzzle.board[i][j]; // we only check if 'f' exists on the board
            if (cell == FLAMINGO_CELL)
                return true;
        }
    return false;
}

ostream &operator<<(ostream &os, const Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: `puzzle` has been printed to `os`
     */
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
            os << puzzle.board[i][j];
        os << '\n';
    }
    return os;
}

bool load_puzzle(const vector<vector<char>> &field, Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if `field` denotes a valid puzzle, in which case `field` has been parsed into `puzzle`
     */
    int rows = field.size();
    int columns = field[0].size();
    int flamingo = 0;
    int rescue = 0;
    int flamingo_on_rescue = 0;

    if (rows == 0 || field[0].empty())
        return false;

    for (int i = 0; i < rows; i++)
    {
        if (static_cast<int>(field[i].size()) != columns) // we check that all rows have the same number of characters
            return false;

        for (int j = 0; j < columns; j++)
            if (field[i][j] == FLAMINGO_CELL)
                flamingo++;
            else if (field[i][j] == RESCUE_CELL)
                rescue++;
            else if (field[i][j] == FLAMINGO_ON_RESCUE_CELL)
                flamingo_on_rescue++;
    }

    if (flamingo + flamingo_on_rescue != 1 || (rescue == 0 && flamingo > 0)) // there must be only one flamingo and if there is 'f' there also must be a rescue cell for it
        return false;

    puzzle.board = field;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (field[i][j] == FLAMINGO_CELL || field[i][j] == FLAMINGO_ON_RESCUE_CELL)
            {
                puzzle.flamingo = {i, j}; // we get the position of the flamingo
                return true;
            }

    return false;
}

bool read_puzzle(istream &is, Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if a valid puzzle has been read from `is`, in which case it is stored in `puzzle`
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

    // Attempt to parse the 2d arrays of chars into a proper puzzle.
    return load_puzzle(field, puzzle);
}

bool open_puzzle(string file, Puzzle &puzzle)
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is true if a puzzle has been successfully read from filename `file` into `puzzle`
     */
    ifstream fs(file);

    if (!fs.is_open())
    {
        cout << "Failed to open file" << endl;
        return false;
    }
    else if (!read_puzzle(fs, puzzle))
    {
        cout << "Failed to read puzzle" << endl;
        return false;
    }

    cout << "Loaded the puzzle shown below:\n";
    cout << puzzle << endl;

    return true;
}

Action get_action()
{ // Precondition:
    assert(true);
    /*  Postcondition: return value is action chosen by user.
     */
    cout << "Pick an action: " << endl;
    cout << "'n': Move north" << endl;
    cout << "'e': Move east" << endl;
    cout << "'s': Move south" << endl;
    cout << "'w': Move west" << endl;
    cout << "'r': Reset" << endl;
    cout << "'q': Quit" << endl;
    cout << "> ";

    char c;
    cin >> c;

    switch (c)
    {
    case 'n':
        return MoveNorth;
    case 'e':
        return MoveEast;
    case 's':
        return MoveSouth;
    case 'w':
        return MoveWest;
    case 'r':
        return Reset;
    case 'q':
        return Quit;
    default:
        return Invalid;
    }
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

void process_move(Action action, Puzzle &puzzle, const Puzzle &initial_puzzle, int &steps, int &i, int &j)
{
    int rows = puzzle.board.size();
    int columns = puzzle.board[0].size();

    switch (action)
    {
    case MoveNorth:
        while (((i > 0 && puzzle.board[i - 1][j] != ROCK_CELL) || i == 0) && puzzle.board[i][j] != RESCUE_CELL) /*each move will stop the moment ig goes out of bounds (it slides of the board)
                                                                                                                or the following cell is a rock or it is on a rescue cell (which means that the game is over)*/
            i--;
        steps++;
        break;
    case MoveEast:
        while (((j < columns - 1 && puzzle.board[i][j + 1] != ROCK_CELL) || j == columns - 1) && puzzle.board[i][j] != RESCUE_CELL)
            j++;
        steps++;
        break;
    case MoveSouth:
        while (((i < rows - 1 && puzzle.board[i + 1][j] != ROCK_CELL) || i == rows - 1) && puzzle.board[i][j] != RESCUE_CELL)
            i++;
        steps++;
        break;
    case MoveWest:
        while (((j > 0 && puzzle.board[i][j - 1] != ROCK_CELL) || j == 0) && puzzle.board[i][j] != RESCUE_CELL)
            j--;
        steps++;
        break;
    case Reset:
        puzzle = initial_puzzle;
        steps = 0;
        break;
    case Invalid:
    case Quit: // dummy case to suppress compiler warning
        cout << "Invalid action" << endl;
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

#ifndef TESTING
int main()
{ // Precondition:
    assert(true);
    /*  Postcondition: the user chosen puzzle file has been read and played.
     */
    string file;
    Puzzle puzzle;

    cout << "Enter file to open: ";
    getline(cin, file);

    if (!open_puzzle(file, puzzle))
    {
        return 1;
    }
    else if (is_solved(puzzle))
    {
        cout << "This puzzle is already solved!" << endl;
        return 0;
    }

    Puzzle initial_puzzle = puzzle;
    int steps = 0;
    Action action;

    puzzle.flamingo = find_flamingo(initial_puzzle);
    int i = initial_puzzle.flamingo.row;
    int j = initial_puzzle.flamingo.col;

    while ((action = get_action()) != Quit)
    {
        process_move(action, puzzle, initial_puzzle, steps, i, j);

        cout << puzzle << endl;

        if (is_solved(puzzle))
        {
            cout << "Congratulations, you have completed the puzzle in " << steps << " steps!" << endl;
            return 0;
        }
        else if (!is_solvable(puzzle))
        {
            cout << "Oh no, the flamingo has drowned!" << endl;
            puzzle = initial_puzzle;
            puzzle.flamingo = find_flamingo(puzzle); // get the new position of the flamingo
            i = puzzle.flamingo.row;
            j = puzzle.flamingo.col;
            steps = 0;
            cout << puzzle << endl;
        }
    }

    return 0;
}
#endif
