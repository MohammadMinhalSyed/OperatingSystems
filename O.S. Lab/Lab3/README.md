# Operating Systems Lab 3

## Sudoku Solution Validator

### General Information

* Sudoku is a logic based, combinational number-placement puzzle game.
* It is meant to be played by 1 player.
* The objective is the fill a 9x9 grid with numbers from 1-9 so that each column, row and each of the nine 3x3 grids in the 9x9 grid hold values all values from 1 to 9. This means a single integer may not appear twice in the same row, column or 3x3 sub-grid. This also means a completed sudoku puzzle will be a 'Latin square'
* To begin the game the puzzle is partially completed for the player to have a starting point where they are able to find a few correct spots based on the already filled spaces.
* The game is completed when the player has filled in all of the empty spaces in the 9x9 grid. They then need to find out if they are correct. There are many ways for the player to find out if they are correct, such as solution manuals or solution validators.
* In this lab, we were instructed to create a sudoku solution validator.

### Lab Information

The lab consisted of designing a multithreaded application that determines whether the solution to a given Sudoku puzzle (puzzle.txt) is valid.
In order to do this we had to create some threads:
* Created a thread to check that each column follows the Sudoku rules and on contains the digits 1 through 9
* Created a thread to check that each row follows the Sudoku rules and on contains the digits 1 through 9
* Created a thread to check that each of the 3x3 subgrids in the 9x9 Sudoku grid follows the Sudoku rules and on contains the digits 1 through 9


## How to Use Sudoku Solution Validator

* The Sudoku Solution Validator is made in a file named "main.c"
* Your puzzle has to be a a 9x9 grid (with 81 single digits and with 9 rows and 9 digits on each row, with a space inbetween digits) in a txt file named "puzzle.txt"
* Ensure that both the "main.c" and "puzzle.txt" files are in the same directory
* A Makefile is also created, therefore all you need to type in the terminal is "make" and the function will compile and present an executable named ____________
* then in the terminal type "./____________" and the Sudoku Solution Validator will run on the puzzle.txt
* If puzzle.txt contains non digit characters or characters not from 0-9 then a message saying "Invalid Characters in puzzle" will show.
* If puzzle.txt does not contain 9 columns or 9 rows, then error messages saying "Not Enough rows in puzzle" or "Not Enough columns in puzzle" will show.
* If puzzle.txt contains 9 rows, 9 columns and has digits from 1 through 9 occupying every space in the puzzle then the Sudoku Solution Validator will say "invaild" if the puzzle is incorrect and will say "valid" if the puzzle is correct.


## Contents of puzzle.txt

* The file puzzle.txt contains a completed Sudoku puzzle for the main.c to validate.
* This is the completed game :  
5 3 4  6 7 8  9 1 2  
6 7 2  1 9 5  3 4 8  
1 9 8  3 4 2  5 6 7  
8 5 9  7 6 1  4 2 3  
4 2 6  8 5 3  7 9 1  
7 1 3  9 2 4  8 5 6  
9 6 1  5 3 7  2 8 4  
2 8 7  4 1 9  6 3 5  
3 4 5  2 8 6  1 7 9  

