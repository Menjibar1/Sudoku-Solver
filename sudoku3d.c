#include <stdio.h>
#include <stdlib.h>

// Declare printSudoku function
void printSudoku(int***);
// Declare solveSudoku function
int solveSudoku(int***);

//Helper functions
	int i = 0;
	
	for (i = 0; i < 21; i++) {
		printf("-");
	}
	printf("\n");
}

int check(int*** arr, int value, int row, int column, int block){
	int Srowblock = (block/3)*3;
	int Scolumnblock = block;
	
	int i = 0, j = 0;
	
	if(block > 2 && block < 6)
		Scolumnblock -=3;
	else if(block > 5)
		Scolumnblock -=6;
	
	
	for(i = 0; i < 3; i++){
		for(j = 0; j < 3; j++){
			if(*(*(*(arr+Srowblock+i)+row)+j) == value)//checking row
				return 0;
			if(*(*(*(arr+Scolumnblock+(3*i))+j)+column) == value)//checking column
				return 0;
			if(*(*(*(arr+block)+i)+j) == value) //checking block
				return 0;
		}		
	}
	return 1;
	
}

int SudokuTime(int*** arr, int row, int column, int block){
	int a;
	if(block < 9){
		if(*(*(*(arr+block)+row)+column) != 0){
			if((column + 1) < 3)
				return SudokuTime(arr, row, column+1, block);
			
			else if(block%3 != 2)
				return SudokuTime(arr, row, column-2, block+1);
			
			else if((row + 1) < 3)
				return SudokuTime(arr, row+1, column-2, block-2);
			
			else if((block%3) == 2)
				return SudokuTime(arr, row-2, column-2, block+1);
			else
				return 1;
		}
		else{
			for(a =1; a <= 9; a++){
				if(check(arr, a, row, column, block) == 1){
					*(*(*(arr+block)+row)+column) = a;
					if((column + 1) < 3){
						if(SudokuTime(arr, row, column+1, block) != 0)
							return 1;						
						else
							*(*(*(arr+block)+row)+column) = 0;						
					}
					else if((block%3) !=2){
						if(SudokuTime(arr, row, column-2, block+1) != 0)
							return 1;						
						else
							*(*(*(arr+block)+row)+column) = 0;						
					}
					else if((row+1) < 3){
						if(SudokuTime(arr, row+1, column-2, block-2) != 0)
							return 1;
						else
							*(*(*(arr+block)+row)+column) = 0;
					}
					else if((block%3) == 2){
						if(SudokuTime(arr, row-2, column-2, block+1) != 0)
							return 1;
						else
							*(*(*(arr+block)+row)+column) = 0;
					}
					else
						return 1;
				}
			}
		}	
		return 0;
		
	}
	else return 1;
}
	
/*
The main program reads a text file containing the block values of the Sudoku grid.
It then saves each 3x3 block into a 2D array.
*/
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    int ***blocks = (int***)malloc(9 * sizeof(int**));

    // Open file for reading
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open File!\n");
        return 0;
    }

	// Read 9x9 blocks into 2D arrays
    for(i=0; i<9; i++)
    {
        *(blocks+i) = (int**)malloc(3 * sizeof(int*));
        printf("Reading numbers in block %d... \n", i+1);
        for(j=0; j<3; j++)
        {
            *(*(blocks+i)+j) = (int*)malloc(3 * sizeof(int));

                fscanf(fptr, "%d %d %d", *(*(blocks+i)+j), *(*(blocks+i)+j)+1, *(*(blocks+i)+j)+2);
                printf("%d %d %d\n", *(*(*(blocks+i)+j)), *(*(*(blocks+i)+j)+1), *(*(*(blocks+i)+j)+2));
        }
    }
	
	// Print out original Sudoku grid
    printf("Printing Sudoku before being solved:\n");
    printSudoku(blocks);

	// Call solveSudoku and print out result
    printf("\nSolving Sudoku...\n\n");
    if(solveSudoku(blocks)){
        printf("Sudoku solved!\n");
        printSudoku(blocks);
    }
    else
        printf("This Sudoku cannot be solved!\n");

    return 0;
}


void printSudoku(int*** arr){
	int a = 0, b =0, z = 0, counter = 0;
	for (z = 0; z < 3; z++){
		for(a = 0; a < 3; a++){
			for (b = 0; b < 3; b++){
				printf("%d %d %d", *(*(*(arr+b+(3*z))+a)), *(*(*(arr+b + (3*z))+a)+1), *(*(*(arr+b+(3*z))+a)+2));
				printf(" |");
				counter++;
				if(counter%3 == 0){
					printf("\n");
				}
			}
		}
	if(z != 2)
		dashLines();	
	}
	
}



int solveSudoku(int*** blocks){
	// This is the function to solve the Sudoku (blocks).

	return SudokuTime(blocks, 0, 0, 0);
}
