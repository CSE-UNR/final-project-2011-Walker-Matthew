//Header comments!
//Name: batship.c
//Purpose: To allow a user to play a single player version of the board game Battleship.
//Author: Matthew Walker

#include <stdio.h>

#define FILE_BOARD "easy.txt"
#define SIZE 10

void displayBoard(char[][SIZE]);
int loadShipBoard(char[][SIZE]);

void colrowCheck(char attackCol, int attackRow, char* colPTR, int* rowPTR);
void colrowConverter(char attackCol, int attackRow, int* colConPTR, int* rowConPTR);

void hitMiss(char attackCol, int attackRow, char[][SIZE], char[][SIZE]);
void sunkShip(char[][SIZE], int* shipPTR, _Bool* APTR, _Bool* BPTR, _Bool* CPTR, _Bool* DPTR, _Bool* EPTR, _Bool* FPTR, _Bool* GPTR, _Bool* HPTR, _Bool* IPTR, _Bool* JPTR);

_Bool winCheck(int COUNT, int SHIPS);

void boardReset(char[][SIZE]);

int main(){
	char GAME;
	
	char attackCol;
	int attackRow;
	
	int colConvert;
	int rowConvert;
	
	char boardComputer[SIZE][SIZE];
	char boardPlayer[SIZE][SIZE];
	
	int COUNT;
	
	printf("Would you like to play a game of Batship? (Y/N) ");
	scanf(" %c", &GAME);
	do{
		boardReset(boardPlayer);
		int SHIPS = 10;
		_Bool winGame = 0;
		int TURN = 0;
		int POINTS = 101;
		_Bool A = 0, B = 0, C = 0, D = 0, E = 0, F = 0, G = 0, H = 0, I = 0, J = 0;
		
		COUNT = loadShipBoard(boardComputer);
		printf("\n\n*****LET'S PLAY BATSHIP!*****\n\n");
		displayBoard(boardPlayer);
	while(winGame != 1){
			printf("\n        FIRE AWAY!\n(enter a spot in the grid like A1) ");
			scanf(" %c%d", &attackCol, &attackRow);
	
			colrowCheck(attackCol, attackRow, &attackCol, &attackRow); 
			colrowConverter(attackCol, attackRow, &colConvert, &rowConvert);
		
			hitMiss(colConvert, rowConvert, boardPlayer, boardComputer);
			sunkShip(boardPlayer, &SHIPS, &A, &B, &C, &D, &E, &F, &G, &H, &I, &J);
			
			displayBoard(boardPlayer);
			
			winGame = winCheck(COUNT, SHIPS);
		
			TURN +=1;
			POINTS -=1;
		
		}
		printf("\nYOU WON! It took you %d turns and you earned %d points\n", TURN, POINTS);
		printf("\nWould you like to play again? (Y/N) ");
		scanf(" %c", &GAME);
	}
	while(GAME != 'N');
	printf("\nGoodbye!\n");
	return 0;
}

void displayBoard(char BOARD[][SIZE]){
	printf("    A B C D E F G H I J\n");
	for(int row = 0; row < SIZE; row++){
		printf("%2d  ", row + 1);
		for(int col = 0; col < SIZE; col++){
			if(BOARD[row][col] != 'X' && BOARD[row][col] != 'O'){
					BOARD[row][col] = ' ';
			}
			printf("%1c ", BOARD[row][col]);
		}
		printf("\n");
	}
}

void colrowCheck(char attackCol, int attackRow, char* colPTR, int* rowPTR){
	if(attackCol < 'A' || attackCol > 'J'){
		while(attackCol < 'A' || attackCol > 'J'){
			printf("Invalid column letter. Try again!\n");
			printf("Enter a letter as seen on the grid(A, B, C, D, E, F, G, H, I, J) ");
			scanf(" %c", &attackCol);
		}
	}
	if(attackRow < 1 || attackRow > 10){
		while(attackRow < 1 || attackRow > 10){
			printf("Invalid row number. Try again!\n");
			printf("Enter a number as seen on the grid(1, 2, 3, 4, 5, 6, 7, 8, 9, 10) ");
			scanf("%d", &attackRow);
		}
	}
	*colPTR = attackCol;
	*rowPTR = attackRow;
}

void colrowConverter(char attackCol, int attackRow, int* colConPTR, int* rowConPTR){
	*colConPTR = attackCol - 'A';
	*rowConPTR = attackRow - 1;
}

int loadShipBoard(char BOARDCOM[][SIZE]){
	int COUNT = 0;
	char TEMP;
	FILE* shipBoard;
	shipBoard = fopen(FILE_BOARD, "r");
	if(shipBoard != NULL){
		for(int I = 0; I < SIZE; I++){
			for(int J = 0; J < SIZE; J++){
				fscanf(shipBoard, "%c", &BOARDCOM[I][J]);
					if(BOARDCOM[I][J] == 'S'){
						COUNT += 1;		
					}
			}
			fscanf(shipBoard, "%c", &TEMP);
		}
		fclose(shipBoard);
	}
	else{
		printf("ERROR: File does not exist\n");
	}
	return COUNT;
}

void hitMiss(char colConvert, int rowConvert, char BOARDU[][SIZE], char BOARDCOM[][SIZE]){
	if(BOARDCOM[rowConvert][colConvert] == 'S'){
		BOARDU[rowConvert][colConvert] = 'X';
		printf("\n           HIT!\n\n");
	}
	else{
		BOARDU[rowConvert][colConvert] = 'O';
		printf("\n           miss.\n\n");
	}
}

void sunkShip(char boardCheck[][SIZE], int* shipPTR, _Bool* APTR, _Bool* BPTR, _Bool* CPTR, _Bool* DPTR, _Bool* EPTR, _Bool* FPTR, _Bool* GPTR, _Bool* HPTR, _Bool* IPTR, _Bool* JPTR){
	if(boardCheck[0][0] == 'X' && boardCheck[0][1] == 'X' && *APTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*APTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[0][3] == 'X' && boardCheck[1][3] == 'X' && boardCheck[2][3] == 'X' && *BPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*BPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[0][6] == 'X' && boardCheck[0][7] == 'X' && boardCheck[0][8] == 'X' && boardCheck[0][9] == 'X' && *CPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*CPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[2][0] == 'X' && boardCheck[3][0] == 'X' && boardCheck[4][0] == 'X' && boardCheck[5][0] == 'X' && *DPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*DPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[2][5] == 'X' && boardCheck[2][6] == 'X' && boardCheck[2][7] == 'X' && *EPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*EPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[2][9] == 'X' && boardCheck[3][9] == 'X' && *FPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*FPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[5][5] == 'X' && boardCheck[6][5] == 'X' && *GPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*GPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[5][9] == 'X' && boardCheck[6][9] == 'X' && boardCheck[7][9] == 'X' && *HPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*HPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[7][0] == 'X' && boardCheck[7][1] == 'X' && *IPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*IPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
	if(boardCheck[9][4] == 'X' && boardCheck[9][5] == 'X' && boardCheck[9][6] == 'X' && boardCheck[9][7] == 'X' && boardCheck[9][8] == 'X' && boardCheck[9][9] == 'X'      && *JPTR != 1){
		printf("          SUNK!\n");
		*shipPTR -= 1;
		*JPTR = 1;
		printf("  There are %d ships left.\n\n", *shipPTR);
	}
}

_Bool winCheck(int COUNT, int SHIPS){
	_Bool winGame = 0;
	if(SHIPS == 0){
		winGame = 1;
	}
	return winGame;
}

void boardReset(char BOARD[][SIZE]){
	for(int row = 0; row < SIZE; row++){
		for(int col = 0; col < SIZE; col++){
			BOARD[row][col] = ' ';
		}
		printf("\n");
	}
}
