
#include <iostream>


using namespace std;

class TicTacToe
{
public:
    // TTT board, empty by default
    char board[3][3] =
    {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };

    // used for keeping track what's in each space, and what value each player has
    enum Entry
    {
        EMPTY = ' ',
        PLAYER_ONE = 'x',
        PLAYER_TWO = 'o'
    };

    // has the board been completely filled?
    bool isFull()
    {
        bool result = true;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == Entry::EMPTY)
                    result = false;
            }
        }

        return result;
    }

    // has someone won?
    bool isVictory(Entry e)
    {

        // first col
        if (board[0][0] == (char)e && board[0][1] == (char)e && board[0][2] == (char)e)
        {
            return true;
        }

        // second col
        else if (board[1][0] == (char)e && board[1][1] == (char)e && board[1][2] == (char)e)
        {
            return true;
        }

        // third col
        else if (board[2][0] == (char)e && board[2][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // first row
        else if (board[0][0] == (char)e && board[1][0] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        // second row
        else if (board[0][1] == (char)e && board[1][1] == (char)e && board[2][1] == (char)e)
        {
            return true;
        }

        // third row
        else if (board[0][2] == (char)e && board[1][2] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 1
        else if (board[0][0] == (char)e && board[1][1] == (char)e && board[2][2] == (char)e)
        {
            return true;
        }

        // diagonal 2
        else if (board[0][2] == (char)e && board[1][1] == (char)e && board[2][0] == (char)e)
        {
            return true;
        }

        return false;
    }

    // return size of the board; mostly just in case I wanted to make the board expandable
    int getSize()
    {
        return 3;
    }


    void dump()
    {
        cout << "----------------------------------------" << endl << endl;
        for (int i = 0; i < getSize(); i++)
        {
            for (int j = 0; j < getSize(); j++)
            {
                cout << " | " << board[i][j] << " | ";
            }

            cout << endl;
        }
        cout << "----------------------------------------" << endl << endl;
    }

};

static bool getHumanMove(int maxValue, TicTacToe::Entry human, TicTacToe& t)
{
    // check if player is able to move
    if (t.isVictory(t.PLAYER_ONE) || t.isVictory(t.PLAYER_TWO) || t.isFull())
        return true;

    int rowChoice = 0;
    int colChoice = 0;

    do {

        do {

            cout << "Enter column number (x) : 0 ... 2 : ";
            cin >> colChoice;
            cout << endl;

        } while (colChoice > maxValue || colChoice < 0);

        do {

            cout << "Enter row number (y) : 0 ... 2 : ";
            cin >> rowChoice;
            cout << endl;

        } while (rowChoice > maxValue || rowChoice < 0);


        if (t.board[rowChoice][colChoice] == t.EMPTY)
        {
            t.board[rowChoice][colChoice] = (char)human;

            return false;
        }

        else
        {
            cout << "Not a valid option! Please try again..." << endl;
        }


    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    // move complete
    return false;
}

static bool getComputerMove(TicTacToe::Entry computer, TicTacToe& t)
{
    // Check if the computer can win immediately and choose that move
    for (int i = 0; i < t.getSize(); i++) {
        for (int j = 0; j < t.getSize(); j++) {
            if (t.board[i][j] == t.EMPTY) {
                t.board[i][j] = (char)computer;
                if (t.isVictory(computer)) {
                    return false; // Computer wins
                }
                t.board[i][j] = t.EMPTY; // Undo the move
            }
        }
    }

    // Check if the human's next move would result in a victory and block it
    TicTacToe::Entry human = (computer == TicTacToe::PLAYER_ONE) ? TicTacToe::PLAYER_TWO : TicTacToe::PLAYER_ONE;
    for (int i = 0; i < t.getSize(); i++) {
        for (int j = 0; j < t.getSize(); j++) {
            if (t.board[i][j] == t.EMPTY) {
                t.board[i][j] = (char)human;
                if (t.isVictory(human)) {
                    t.board[i][j] = (char)computer;
                    return false; // Blocked the human's win
                }
                t.board[i][j] = t.EMPTY; // Undo the move
            }
        }
    }

    // Check if the center square is open, choose it
    if (t.board[1][1] == t.EMPTY)
    {
        t.board[1][1] = (char)computer;
        return false;
    }

    // Check if any of the corner squares are open, choose one of them
    const int corners[4][2] = { {0, 0}, {0, 2}, {2, 0}, {2, 2} };
    for (int i = 0; i < 4; i++) {
        int row = corners[i][0];
        int col = corners[i][1];
        if (t.board[row][col] == t.EMPTY) {
            t.board[row][col] = (char)computer;
            return false;
        }
    }

    // If none of the above conditions are met, choose any open square at random
    int rowChoice, colChoice;
    do {
        rowChoice = rand() % t.getSize();
        colChoice = rand() % t.getSize();
    } while (t.board[rowChoice][colChoice] != t.EMPTY);

    t.board[rowChoice][colChoice] = (char)computer;

    return false;
}
// ----------------------------
// main
// ----------------------------

int main()
{
    TicTacToe t;
    TicTacToe::Entry human = TicTacToe::PLAYER_ONE;
    TicTacToe::Entry computer = TicTacToe::PLAYER_TWO;
    bool gameOver = false;

    cout << "Welcome to Tic Tac Toe!" << endl;
    cout << "You are '" << static_cast<char>(human) << "', and the computer is '" << static_cast<char>(computer) << "'" << endl;

    while (!gameOver)
    {
        t.dump();

        if (human == TicTacToe::PLAYER_ONE)
        {
            gameOver = getHumanMove(t.getSize() - 1, human, t);
        }
        else
        {
            gameOver = getComputerMove(computer, t);
        }

        // Display the current player symbol
        cout << "Current player: '" << static_cast<char>(human) << "'" << endl;

        // Switch players
        if (human == TicTacToe::PLAYER_ONE)
        {
            human = TicTacToe::PLAYER_TWO;
        }
        else
        {
            human = TicTacToe::PLAYER_ONE;
        }

        if (t.isVictory(TicTacToe::PLAYER_ONE))
        {
            t.dump();
            cout << "Player X wins!" << endl;
            gameOver = true;
        }
        else if (t.isVictory(TicTacToe::PLAYER_TWO))
        {
            t.dump();
            cout << "Player O wins!" << endl;
            gameOver = true;
        }
        else if (t.isFull())
        {
            t.dump();
            cout << "It's a draw!" << endl;
            gameOver = true;
        }
    }

    return 0;
}