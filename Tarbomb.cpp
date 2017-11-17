/* CSCI261B Assignment7: Tarbomb Class
 *
 * Description: Definition file for Tarbomb Class. Handles ncurses input/output.
 * Uses timing from chrono to only accept input for a limited time. Evaluates
 * user input with simple if statement.
 *
 * Author: Joseph McKinsey
 *
 */

// <chrono> better steady timer in c++11
#include <string>
#include <chrono>
#include <ncurses.h>

#include "Tarbomb.h"

using namespace std;

// Initialize variables. Easier editing in the future from main.cpp
Tarbomb::Tarbomb() {
    shell = " $ ";
    failMessage = "YOU EXPLODED!";
    successMessage = "YOU GOT IT! YOU WON... YOUR LIFE!";
    timeLimit = 10;
}

// Associated setter
void Tarbomb::setShellString(string shellInput) {
    shell = shellInput;
    return;
}

// Associated setter
void Tarbomb::setFailMessage(string fail) {
    failMessage = fail;
    return;
}

// Associated setter
void Tarbomb::setSuccessMessage(string success) {
    successMessage = success;
    return;
}

// Associated setter
void Tarbomb::setTimeLimit(double timeInput) {
    timeLimit = timeInput;
}

// Has introduction for the bomb. Timeout on the first display is indefinite.
// Second screen has limited time of 5 seconds. Third has the same. Note that
// timeout(5000) will carry over to all parts of program.
void Tarbomb::introduction() {
    // Prevents echoing and buffering.
    noecho();
    cbreak();
    // Set timeout. Clear. Print. Refresh. Get character. Standard for ncurses IO
    timeout(-1);
    clear();
    printw("Welcome!\n");
    printw("In this room, there is a magic item: a bomb!\n");
    printw("Do not fear! You can defuse it with the right bash commands.");
    refresh();
    getch();
    
    timeout(4000);
    
    clear();
    printw("Here is your filesystem: \n");
    printw("./\n");
    printw("../\n");
    printw("test.tar.gz\n");
    refresh();
    getch();
    
    timeout(8000);
    // attron and attroff turn on and off attributes for text in between.
    clear();
    printw("You must type in the valid basic extraction (no verbose) tar command in ");
    attron(A_BOLD);
    attron(A_STANDOUT);
    printw("ten");
    attroff(A_BOLD);
    attroff(A_STANDOUT);
    printw(" seconds. You get one try. No googling. Backspace is permitted.");
    getch();
}

// Tests input for valid tar commands. May change in the future to allow for more
// variety of inputs, ie "tar    -x -z  -v -f test.tar.gz".
bool Tarbomb::checkInput(string input) {
    return (input == "tar -xzf test.tar.gz" ||
        input == "tar -xfz test.tar.gz" ||
        input == "tar -zxf test.tar.gz" ||
        input == "tar -zfx test.tar.gz" ||
        input == "tar -fxz test.tar.gz" ||
        input == "tar -fzx test.tar.gz" ||
        input == "tar xzf test.tar.gz" ||
        input == "tar xfz test.tar.gz" ||
        input == "tar zxf test.tar.gz" ||
        input == "tar zfx test.tar.gz" ||
        input == "tar fxz test.tar.gz" ||
        input == "tar fzx test.tar.gz");
}

// Active bomb. Look for user input. Run end screen.
void Tarbomb::activate() {
    // Allows writing and input at the same time.
    nodelay(stdscr, true);
    // Getch blocks loop for 10 milliseconds. Returns ERR if no input. Cannot
    // handle fast input shorter than 10 milliseconds.
    timeout(10);
    //Initialize chrono time point. chrono under namespace std.
    chrono::time_point<chrono::steady_clock> start;
    chrono::time_point<chrono::steady_clock> end;
    start = chrono::steady_clock::now();
    end = chrono::steady_clock::now();
    // Declare temporary char storage. Duration in double and string, and string
    // input.
    char tempInputChar;
    string input;
    double durationSeconds = 0;
    string durationString; 
    
    // while loop will print timer and then accept and evalute user input, and
    // recalculate durationSeconds.
    while (durationSeconds <= timeLimit + .001) {
        // durationString truncated timeLimit to 3 decimal points instead of the
        // standard 6.
        clear();
        durationString = to_string(timeLimit - durationSeconds);
        mvprintw(1, 1, durationString.substr(0, durationString.length() - 3).c_str());
        mvprintw(2, 1, (shell + input).c_str());
        refresh();
        
        // Check character for newline, error, or backspace (127 in ascii).
        tempInputChar = getch();
        if (tempInputChar == '\n') {
            break;
        }
        else if(tempInputChar == 127) {
            if (input.length() > 0) {
                input.pop_back();
            }
        }
        else if(tempInputChar != ERR) {
            input.push_back(tempInputChar);
        }
        refresh();
        
        // Reevaluate seconds passed. No input should increase it by 10 milliseconds.
        end = chrono::steady_clock::now();
        durationSeconds = chrono::duration_cast<chrono::milliseconds> (end - start).count() / (double) 1000;
    }
    // No timeout. nodelay no longer necessary.
    timeout(-1);
    nodelay(stdscr, false);
    
    // If durationSeconds passed 10 seconds, this will set it to 10. Makes it so
    // the durationString will be 0 instead of negative.
    if (durationSeconds >= timeLimit) {
        durationSeconds = timeLimit;
    }
    durationString = to_string(timeLimit - durationSeconds);
    
    clear();
    mvprintw(1, 1, durationString.substr(0, durationString.length() - 3).c_str());
    mvprintw(2, 1, (shell + input).c_str());
    move(3, 1);
    refresh();
    
    endGameMessage(input);
}

// Print end screen
void Tarbomb::endGameMessage(string input) {
    attron(A_BOLD);
    if (checkInput(input)) {
        mvprintw(5, 5, successMessage.c_str());
    }
    else {
        mvprintw(5, 5, failMessage.c_str());
    }
    attroff(A_BOLD);
}
