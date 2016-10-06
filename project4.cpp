/***********************************************************************
* Program:
*    Project 4, Sudoku  
*    Brother Comeau, CS124
* Author:
*    Ben Wright
* Summary: 
*    In this program it prompts the user for a file containing a sudoku
*    board. In it the user will solve a sudoku board. He/she may choose
*    to save it and finish it later. All the rules that apply to sudoku
*    also apply to this program. In it checks every error.
*
*    Estimated:  10.0 hrs   
*    Actual:     11.0 hrs
*      The hardest part of this program was to have it check to see which
*      values are the possible ones which would fit into the square. This
*      was the hardest project that I have ever worked on. I did not do
*      it in a group with other people. The only help I had was with
*      tutors.
************************************************************************/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>
#include <vector>

using namespace std;

struct Sudoku
{
	int board[9][9];
	char column0;
	int column1;
	int row;
};

void getFilename(string & filename);
void readFile(string & filename, int board[][9]);
void computeValues(int board[][9], int row, char column0, int column1);
void getCoordinates(int board[][9], int &row, char &column0, int &column1);
void possibleValues(int board[][9], int row, int row_lhs, int row_rhs, bool possible[]);
void possibleValues(int board[][9]);
void changeSquare(int board[][9]);
void getInstructions();
void display(int board[][9]);
void quitGame(int board[][9]);
void interact(int board[][9]);
int main(void);

/**********************************************************************
* Function main will call all the remaining functions and display them
* on the screen.
***********************************************************************/
int main(void)
{
	string filename;
	int board[9][9];

	getFilename(filename);
	readFile(filename, board);
	getInstructions();
	display(board);
	interact(board);
	return 0;
}



/**************************************************************
* Function get filename prompts the user for the name of a file.
**************************************************************/
void getFilename(string & filename)
{
	cout << "Where is your board located? ";
	cin >> filename;
	cin.ignore();
}

/**********************************************************************
* Function readFile will open the file the user prompt it. It will
* then read the file and after it has been read then it will close
* out.
***********************************************************************/
void readFile(string & filename, int board[][9])
{
	ifstream fin;
	fin.open(filename.c_str());
	if (fin.is_open())
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				fin >> board[i][j];
		fin.close();
	}
	else
		cout << "Error opening file\n";
}

/**********************************************************************
* Function interact is the heart function of the whole program. It will
* ask the user which option they would like to choose.
***********************************************************************/
void interact(int board[][9])
{
	char option;

	do
	{
		cout << "> ";
		cin >> option;
		switch (option)
		{
		case '?':
			getInstructions();
			cout << endl;
			break;
		case 'D':
			display(board);
			break;
		case 'E':
			changeSquare(board);
			break;
		case 'S':
			possibleValues(board);
			break;
		case 'Q':
			quitGame(board);
			break;
		default:
			cout << "Invalid command\n";
			break;
		}
		cin.clear();
	} while (option != 'Q');
}

/**********************************************************************
* Function getInstructions displays options list that people might
* chose if they decide to pay the game stop edition,
***********************************************************************/
void getInstructions()
{
	cout << "Options:\n"
		<< setw(5) << "? " << " Show these instructions\n"
		<< setw(5) << "D " << " Display the board\n"
		<< setw(5) << "E " << " Edit one square\n"
		<< setw(5) << "S " << " Show the possible values for a square\n"
		<< setw(5) << "Q " << " Save and Quit\n" << endl;
}

/**********************************************************************
* Function display will display the board and its spacing will be
* handled.
***********************************************************************/
void display(int board[][9])
{
	string column = "   A B C D E F G H I";
	cout << column << endl;
	for (int i = 0; i < 9; ++i)
	{
		cout << i + 1 << setw(3);
		for (int j = 0; j < 9; ++j)
		{
			if (board[i][j] == 0)
				cout << ' ';
			else
				cout << board[i][j];
			if (j == 8)
				cout << endl;
			if (j % 3 != 2)
				cout << " ";
			if (j == 2 || j == 5)
				cout << "|";
		}
		if (i == 2 || i == 5)
			cout << "   -----+-----+-----" << endl;
	}
	cout << endl;
}




/**********************************************************************
* Function quit game will prompt the user to save the board they have
* edited to a new file.
***********************************************************************/
void quitGame(int board[][9])
{

	cout << "What file would you like to write your board to: ";
	char filename[256];
	cin >> filename;

	ofstream fout;
	fout.open(filename);
	if (fout.is_open())
	{
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				fout << board[i][j] << ' ';
			}
			fout << "\n";
		}
		fout.close();
	}
	else
		cout << "Error opening file\n";
	cout << "Board written successfully\n";
}


/**********************************************************************
 * Function computeValues checks to make sure the value given in
 * the square is the correct values that a gamer would want to change to.
 ***********************************************************************/
void computeValues(int board[][9], int row, char column0, int column1)
{
   int value;
   cout << "What is the value at \'" << column0 << row + 1 << "\': ";
   cin >> value;
   if (value < 1 || value > 9)
   {
      cout << "ERROR: Value \'" << value << "\' in square \'" << column0
           << row + 1 << "\' is invalid\n";
      return;
   }

   /*traversing through the board*/
   for (int x  = 0; x < 9; ++x)
   {
      if (value == board[x][column1])
      {
         cout << "ERROR: Value \'" << value << "\' in square \'" << column0
              << row + 1 << "\' is invalid\n";
         return;
      }
   }

   for (int x = 0; x < 9; ++x)
   {
      if (value == board[row][x])
      {
         cout << "ERROR: Value \'" << value << "\' in square \'" << column0
              << row + 1 << "\' is invalid\n";         
         return;
      }
   }
   board[row][column1] = value;
}
   
/**********************************************************************
 * Function getCoordinates prompts the user for the column and row of
 * the square. Then it makes sure that whatever is in their then has
 * to be a valid amount in the edited square.
 ***********************************************************************/
void getCoordinates(int board[][9], int &row, char &column0, int &column1)
{

   cout << "What are the coordinates of the square: ";
   cin >> column0 >> row;

   if (column0 >= 'A' && column0 <= 'Z') 
      toupper(column0);

   column1 = toupper(column0) - 'A';
   row--;

   if (islower(column0))
      cout << "ERROR: Square \'" << column0 << row + 1 << "\' is invalid\n";
   
   if (column0 < 'A' && column0 > 'I')
      cout << "ERROR: Square \'" << column0 << row + 1 << "\' is invalid\n";
   
   if (row < 1 && row > 9)
      cout << "ERROR: Square \'" << column0 << row + 1 << "\' is invalid\n";
     
   if (board[row][column1] != 0)
      cout << "ERROR: Square \'" << column0 << row + 1 << "\' is filled\n" << endl;
}

void possibleValues(int board[][9], int row, int row_lhs, int row_rhs, bool possible[])
{
   if (row > row_lhs && row < row_rhs)
      for (int i = row_lhs; i < row_rhs; ++i)
         for(int j = row_lhs; j < row_rhs; ++j)
            if(board[i][j])
               possible[board[i][j]] = false;
}


/**********************************************************************
 * Function possibleValues goes through the board array and checks
 * if it equals whatever the value was. It will then display all of 
 * possible values.
 ***********************************************************************/
void possibleValues(int board[][9])
{
   int row;
   int column1;
   char column0;
   bool possible[10] =
      {false, true, true, true, true, true, true, true, true, true};

   getCoordinates(board, row, column0, column1);
   cout << "The possible values for \'" << column0 << row + 1 << "\' are: ";

   for (int x = 0; x < 9; ++x)
   {
      if (board[row][x])
         possible[board[row][x]] = false;
   }
   for (int x = 0; x < 9; ++x)
   {
      if (board[x][column1])
         possible[board[x][column1]] = false;
   }

   if (column0 >= 'A' && column0 <= 'C')
   {
      possibleValues(board, row, 0, 3, possible);
      possibleValues(board, row, 3, 6, possible);
      possibleValues(board, row, 6, 9, possible);
   }

   if (column0 >= 'D' && column0 <= 'F')
   {
      possibleValues(board, row, 0, 3, possible);
      possibleValues(board, row, 3, 6, possible);
      possibleValues(board, row, 6, 9, possible);
   }

   if (column0 >= 'G' && column0 <= 'I')
   {
      possibleValues(board, row, 0, 3, possible);
      possibleValues(board, row, 3, 6, possible);
      possibleValues(board, row, 6, 9, possible);
   }

   int count = 0;
   
   for (int x = 0; x < 9; ++x)
   {
      if (possible[x])
      {
         count += possible[x];
         if (count == 1)       
            cout << x;
         if (count > 1)
            cout << ", " << x;
      }   
   }
   cout << endl;
   puts("");
}

/**********************************************************************
 * Function change square call the get coordinates function and then
*  sends them to the computeValues for additional checking.  	 
 ***********************************************************************/
void changeSquare(int board[][9])
{
   int row;
   char column0;
   int column1;
   getCoordinates(board, row, column0, column1);
   if (board[row][column1] == 0)
   {
      computeValues(board, row, column0, column1);
      cout << endl;
      return;
   }
}



