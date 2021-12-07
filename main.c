#include <stdio.h>

int checkSanity(char arr[9][9]){
  int i, j;
  for(i = 0;  i < 9; i++)
    for(j = 0; j < 9; j++)
      if((arr[i][j] < 1) || (arr[i][j] > 9)) {
        return 0;
      }
  return 1;
}

int checkLine(char arr[9][9], int line){
  int result = 0;
  int i;
  for(i = 0; i<9; i++){
    result |= 1 << arr[i][line];
    //printf("line %d: %X\n", line, result);
  }
  return result == 0x3FE;
}

int checkColumn(char arr[9][9], int column){
  int result = 0;
  int i;
  for(i = 0; i<9; i++){
    result |= 1 << arr[column][i];
    //printf("column %d: %X\n", column, result);
  }
  return result == 0x3FE;
}

int checkBlock(char arr[9][9], int block){
  int iinit = (block % 3) * 3;
  int iend  = iinit + 3;
  int jinit = (block / 3) * 3; 
  int jend  = jinit + 3;
  int i,j;
  int result = 0;
  for (i = iinit; i < iend; i++)
    for (j = jinit; j < jend; j++){
      result |= 1 << arr[i][j];
      //printf("block %d (%d,%d): %X\n", block, i, j, result);
    }
  return result == 0x3FE; 
}

int checkSudoku(char arr[9][9]){
  int i;

  if (!checkSanity(arr)){
    //printf("Sanity failed\n");
    return 0;
  }

  for (i=0; i<9; i++){
    if (!checkLine(arr, i)){ 
      //printf("Line %d failed\n", i);
      return 0;
    }
    if (!checkColumn(arr, i)){
      //printf("Column %d failed\n", i);
      return 0;
    }
    if (!checkBlock(arr, i)){
      //printf("Block %d failed\n", i);
      return 0;
    }
  }

  return 1;

}


int main(void) {
  char arr[9][9] = { 
    {5, 3, 4, 6, 7, 8, 9, 1, 2},
    {6, 7, 2, 1, 9, 5, 3, 4, 8},
    {1, 9, 8, 3, 4, 2, 5, 6, 7},
    {8, 5, 9, 7, 6, 1, 4, 2, 3},
    {4, 2, 6, 8, 5, 3, 7, 9, 1},
    {7, 1, 3, 9, 2, 4, 8, 5, 6},
    {9, 6, 1, 5, 3, 7, 2, 8, 4},
    {2, 8, 7, 4, 1, 9, 6, 3, 5},
    {3, 4, 5, 2, 8, 6, 1, 7, 9}
  };

  printf("%d\n", checkSudoku(arr));

  return 0;
}