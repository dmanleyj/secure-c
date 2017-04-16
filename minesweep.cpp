// minesweep.cpp

#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include <time.h>

using namespace std;
/////////////////
// Functions
void Reveal(int, int);              // Reveals a square's contents with given coordinates 
void MakeMinePositions();           // randomly spread out 10 mine positions
void AddToSquare();                 // increases the number of contacts for a square by 1 safely
void MakeTable();                   // creates the game table
void OpenSquare();                  // opens a square, tests for mine calls Reveal
void PlayGame();                    // the main routine
void DrawTable(char);               // draws the table for the player
//
////////////////
// variables
char tblPlayer[10][10];             // the game table visible to the player
char tblMinePos[10][10];            // table with the positions of the mines and the number of each square
char strCmd;                        // the input strCmd, it can be 'o' or f'
int cntFlag=0;                      // number of flags the player has posted
int cntMinesFlagged=0;              // number of flags that the player has correctly posted
bool bLoseEndGame=false;            // flag indicating game over
time_t tmStart = time(0);           // start time for game
time_t tmGame;                      // current time

/////
void AddToSquare(int i,int j) {
// if this is a valid square (check because it is being called looking for surrounding squares and the mine could be on the border)
// then increment how many contacts it has with the square with the mine.

    if(i>=0 && i<10 && j>=0 && j<10 && tblMinePos[i][j] != 'X') {
        tblMinePos[i][j]++; // initial char '0' will become next char
    }
}
/////
//
void MakeMinePositions() {
// build 10 x 10 array of mine position data that will be Revealed when users provide an OpenSquare call.

    int counter=0;
    srand(time(NULL));

// fill array with '0' chars
    for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            tblMinePos[i][j]='0'; // initial char will be incremented to indicate number of contacts, or will be an 'X' if a mine
        }
    }    
    
    int i=0;
    int j=0;
// randomly select 10 i,j coordinates to assign an X until 10 are provided.        
    while(counter<10) {
        int i=rand()%10;
        int j=rand()%10;
        if(tblMinePos[i][j]=='0'){  // spread 'em out.  Only assign to '0' table entries.
            tblMinePos[i][j]='X';
            // increment the number of contact points surrounding squares have
            AddToSquare(i-1,j);
            AddToSquare(i+1,j);
            AddToSquare(i,j-1);
            AddToSquare(i,j+1);
            AddToSquare(i-1,j-1);
            AddToSquare(i-1,j+1);
            AddToSquare(i+1,j-1);
            AddToSquare(i+1,j+1);
            counter++;
        }
    }
}
/////
/////
void MakeTable() {
// create a 10 x 10 table with default value '*' for displaying to the player

    for(int i=0;i<10;i++) {
        for(int j=0;j<10;j++) {
            tblPlayer[i][j]='*';
        }
    }
}
//
/////
void DrawTable(char arr[10][10]) {
// set width for 3 characters, outputting Column header, the row number, separators and the values in the array passed as parm

    cout<<"    X ---";
    for(int i=0;i<10;i++) {
        cout<<setw(3)<<"---";
    }
    cout<<"-->"<<endl;
    cout<<"     ";
    for(int i=0;i<10;i++) {
        cout<<setw(3)<<i;
    }
    cout<<endl<<"Y   ";
    for(int i=0;i<32;i++) {
        cout<<"_";
    }
    cout<<endl;

    for(int i=0;i<10;i++){
        cout<<"|"<<setw(3)<<i<<"|";
        for(int j=0;j<10;j++) {
            cout<<setw(3)<<arr[i][j];
        }
        cout<<endl;
    }
    cout<<"|"<<endl<<"v"<<endl;
}
//
/////
void OpenSquare() {
// When user enters the 'o' command, the next read is for the coordinates for i and j.
// Check the mine positions to determine if there is a mine located there.
// If there is a mine, show all the mine positions by setting all the tblPlayer[i][j] to X where table mine positions[i][j] are X, and flag the game as ended.

    int i,j;
    i=0;
    j=0;
    // Let's only accept integers from 0 to 9 from input
    do {
        cin >> j >> i;
        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore();
            cout << "Please only provide numbers from 0 to 9 for X and Y. Try again, starting with a value for X." << endl;
        }
        if ((i < 0) || (i > 9)) {
            cin.clear();
            cin.ignore();
            cout << "Please only provide numbers from 0 to 9 for X. Try again, starting with a value for X." << endl;
        }
        if ((j < 0) || (j > 9)) {
            cin.clear();
            cin.ignore();
            cout << "Please only provide numbers from 0 to 9 for Y. Try again, starting with a value for X." << endl;
        }
    }
    while (i<0 || i>9 || j<0 || j>9);
    
    if(tblMinePos[i][j]=='X') {
        // you lose
        tblPlayer[i][j]='X'; // display that mine
        bLoseEndGame=true;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if(tblMinePos[i][j]=='X') // display all of the others too
                    tblPlayer[i][j]='X';
    }
    else {
        Reveal(i,j); // update table to display this square, and any other surrounding squares if it is 0
    }
}
//
/////
void AddOrRemoveFlag()
{
    int i,j;
    i=0;
    j=0;
    // Let's only accept integers from 0 to 9 from input
    do {
        cin >> j >> i;
        if (cin.fail()) { 
            cin.clear(); 
            cin.ignore();
            cout << "Please only provide numbers from 0 to 9 for X and Y.  Try again, starting with a value for X." << endl;
        }
        if ((i < 0) || (i > 9)) {
            cin.clear();
            cin.ignore();
            cout << "Please only provide numbers from 0 to 9 for X. Try again, starting with a value for X." << endl;
        }
        if ((j < 0) || (j > 9)) {
            cin.clear();
            cin.ignore();
            cout << "Please only provide numbers from 0 to 9 for Y. Try again, starting with a value for X." << endl;
        }

    }
    while (i<0 || i>9 || j<0 || j>9);
    
    if (tblPlayer[i][j]=='*') {
        tblPlayer[i][j]='F';
        cntFlag++;
        if(tblMinePos[i][j]=='X') { // if this flag was accurately placed, increment the mines flagged counter, if the mines flagged counter == 10, game won.
            cntMinesFlagged++;
        }
    }
    else if (tblPlayer[i][j]=='F')  { // removing a flag
        tblPlayer[i][j]='*';
        cntFlag--;
        if(tblMinePos[i][j]=='X') { // decrement the mines flagged counter
            cntMinesFlagged--;
        }
    }

}
//
/////
void input_strCmd() {
    cin>>strCmd;
    switch (strCmd){
    case 'o' : OpenSquare(); break;
    case 'f' : AddOrRemoveFlag(); break;
    default  : cout << "Enter o or f (ctl-C to Quit)\n" ; input_strCmd();
    }
}
//
/////
void Reveal(int i,int j)
{
    if (tblPlayer[i][j]=='*' && tblMinePos[i][j]!='X' && i>=0 && i<10 && j>=0 && j<10)  { // for valid coordinates that do not have an X in mine positions, move mine position to table for display
        tblPlayer[i][j]=tblMinePos[i][j];
        if(tblMinePos[i][j]=='0') { // if the position is a 0, then show surrounding square values (recursively)
            Reveal(i,j-1);
            Reveal(i,j+1);
            Reveal(i-1,j-1);
            Reveal(i+1,j-1);
            Reveal(i+1,j+1);
            Reveal(i-1,j+1);
            Reveal(i-1,j);
            Reveal(i+1,j);
        }
    }
}
//
/////
bool CheckWinEndPlayGame()
{
    bool bWin, bAllFound;
    bWin=0;
    // check to see if the all the mines have been correctly flagged;
    if(cntFlag == 10 && cntMinesFlagged == 10) {
        bWin = 1;
    }
    // check to see if all the squares are being displayed except the mines.
    bAllFound=1;
    for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if (tblPlayer[i][j] == '*') {
                    if (tblMinePos[i][j] != 'X') { //not all were found
                        bAllFound = 0;
                        break;
                    }
                }; // initial char will be incremented to indicate number of contacts, or will be an 'X' if a mine
    if (bWin == 0) {
        bWin=bAllFound;
    }
    
    return bWin;
}
//
/////
void PlayGame() {
    MakeTable();            // Make a 10 x 10 array for display to the player
    MakeMinePositions();    // Make a 10 x 10 array of random positions for mines

    while( !bLoseEndGame && !CheckWinEndPlayGame())
    {
        tmGame=time(0);
        DrawTable(tblPlayer);
        cout<<endl<<"Flags:"<<cntFlag<<endl;
        cout<<"Time:"<<tmGame-tmStart<<endl<<endl;
        input_strCmd();
    }

    if(bLoseEndGame){
        DrawTable(tblPlayer);
        cout<<endl<<"KA BOOM!!\nGAME OVER\n"<<endl;
    }

    if(CheckWinEndPlayGame()){
        // Reveal all the mines before displaying the board one last time
         for(int i=0;i<10;i++)
                for(int j=0;j<10;j++)
                    if(tblMinePos[i][j]=='X') // display all of the others too
                        tblPlayer[i][j]='X';
        DrawTable(tblPlayer);
        cout<<"Time to complete:"<<tmGame-tmStart<<endl;
        cout<<endl<<"YOU WIN!\n"<<endl;
    }
}

int main() {
    cout
    <<"There are 10 mines in the mine field.  You must clear all spaces, or flag all of spaces that contain mines to win."
    <<endl<<"Enter 'o' <Enter>, then enter values of X <Enter> and Y <Enter> to open the square at X, Y."
    <<endl<<"Enter 'f' ,then enter values of X <Enter> and Y <Enter> to place "
    <<"or remove flag on square at X, Y."
    <<endl<< "X is the column, and Y is the row."
    <<endl<<endl;
    
    PlayGame();
    
    return 0;
}