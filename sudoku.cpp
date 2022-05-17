#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

#define row 9
#define col 9

int  in_range(int board[][col])
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] <= 0 || board[i][j] > 9 ) {
               cout << "Error: This is not valid!" << endl;
               return (1);
            }
        }
    }
    return 0;
}

int  check_row(int board[][col])
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == board[i][j + 1]) {
               cout << "Error: This is not valid!" << endl;
               return (1);
            }
        }
    }
    return 0;
}

int  check_col(int board[][col])
{
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (board[i][j] == board[i+1][j]) {
               cout << "Error: This is not valid!" << endl;
               return (1);
            }
        }
    }
    return 0;
}

int  check_sum(int board[][col])
{
   int sum = 0;

   for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++)
          sum = sum + board[i][j];
   }
   return sum;
}

int check_subgrid(int board[][col], int x, int y, int num)
{ 
    if(x < 3) x = 0;
    else if(x < 6) x = 3;
    else x = 6;

    if(y < 3) y = 0;
    else if(y < 6) y = 3;
    else y = 6;

    for(int i = x; i < x+3; i++){
        for(int j = y; j < y+3; j++){
            if(board[i][j] == num)
                return 1;
        }
    }
    return 0;
}

void  check_validity(int board[][col])
{

   if (check_sum(board) > 405) {
       cout << "Error: This is not valid!" << endl;
        exit (0);
   }
   if (in_range(board) == 1)
         exit (0);
   if (check_col(board) == 1)
         exit (0);
   if (check_row(board) == 1)
         exit (0);

    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
         for(int k = 1; k <= 9; k++){      
         if (check_subgrid(board, i, j, k) == 0) {
               cout << "Error: Subgrid not good!" << endl;
               exit(0);
           }
         }
      }
   }
}

void    print_board(int board[][col])
{
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
         cout << board[i][j] << " ";
      }
      cout << endl;
   }

  cout << "----------------------" << endl;
  cout << "Sudoku is valid!" << endl;
}

int  csv_to_2d_array(char *av)
{
    if (av == NULL) {
        cout << "This argument is invalid!" << endl;
    }

   string file = av;
   ifstream inFile;
   inFile.open(file);
   string line = "";
   string temp = "";
   int j = 0;
   int k = 0;
   int board[row][col] = {0};

   if (inFile.is_open())
   {
      k = 0;
      while (getline(inFile, line))
      {
         if (line != "")
         {
            j = 0;
            line = line + ',';
            for (int i = 0; i < line.length(); i++)
            {
               if(line[i] != ',')
               {
                  temp += line[i];
               } else {
                  board[k][j] = stoi(temp);
                  temp = "";
                  j++;
               }
            }
         }
         k++;
      }
   } else  {
      cout << "Failed to open the file!" << endl;
      exit (0);
   }

   check_validity(board);
   print_board(board);
   return (0);
}

int main(int ac, char **av)
{
    if (ac > 2) {
        cout << "Number of arguments is invalid!" << endl;
        exit (0);
    }
    
   csv_to_2d_array(av[1]);
   return (0);
}
