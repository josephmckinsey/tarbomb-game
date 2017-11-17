/* CSCI261B Assignment 7: Magic Item: The Tar Bomb
*
* Description: User must type a valid tar command to stop the bomb in 10
* seconds. No googling. Program must be compiled with -lncurses option in g++ or
* with makefile provided.
*
* Author: Joseph McKinsey
*
*/

#include <string>
#include <ncurses.h>
#include "Tarbomb.h"

using namespace std;

int main() {
    char tempInputChar;
    // Initialize ncurses screen.
    initscr();
    // Declare, initialize, and activate bomb.
    Tarbomb bomb;
    bomb.introduction();
    bomb.activate();
    
    // User must press q to quit. timeout(-1) just in case bomb edited it.
    mvprintw(10, 1, "Press q to quit.");
    timeout(-1);
    refresh();
    
    while(true) {
        tempInputChar = getch();
        if (tolower(tempInputChar) == 'q') {
            break;
        }
    }
    // Ends ncurses.
    endwin();
    return 0;
}
