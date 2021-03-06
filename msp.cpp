#include <stdio.h>
#include <stdlib.h>

#define M 5
#define N 5
#define MINE -1

int SIDE = 5;
int MINES;

int B[M][N];
int T[M][N];

void makeMove(int* x, int* y)
{
    // Take the input move 
    printf("Enter your move, (row, column) -> ");
    scanf("%d %d", x, y);
    return;
}

void init() {
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
      			B[i][j] = 0;
      			T[i][j] = 0;
    		}
	int random = rand() % (4 - 0 + 1);
	int x = random ;
  	int y = random ;
  	B[x][y] = MINE;
  	int x1 = random % (4);
  	int y1 = random  / (4);
  	B[x1][y1] = MINE;
}

void count_mines(){
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (B[i][j] != MINE){
				int cnt = 0;
				if(i - 1 >= 0 && j - 1 >= 0 && B[i-1][j-1] == MINE)
                    			cnt = cnt + 1;
				if(i - 1 >= 0 && B[i-1][j] == MINE)
				    cnt = cnt + 1;
				if(i - 1 >= 0 && j + 1 < N && B[i-1][j+1] == MINE)
				    cnt = cnt + 1;
				if(j - 1 >= 0 && B[i][j-1] == MINE)
				    cnt = cnt + 1;
				if(j + 1 < N && B[i][j+1] == MINE )
				    cnt = cnt + 1;
				if(i + 1 < M && j - 1 >= 0 && B[i+1][j-1]==MINE)
				    cnt = cnt + 1;
				if(i + 1 < M && B[i+1][j] == MINE)
				    cnt = cnt + 1;
				if(i + 1 < M && j + 1 < N && B[i+1][j+1] == MINE)
				    cnt = cnt + 1; 
				B[i][j] = cnt;
			}
		}
	}
	
}

void printMap1(){

       printf("  ");
    for (int j=0; j<N;j++)
        printf(" %d",j%10);
        printf("\n");
        
        
		
    for (int i=0; i< M; i++) {
        printf("%d  ", i%10);
        for (int j=0;j<N;j++)
        if(T[i][j] == 1){
            if (B[i][j] == MINE)
            printf("x ");
            else if (B[i][j]==0){
               printf(". ");
               }else 
               printf("%d ",B[i][j]);
            } 
            	else printf("# ");
            	printf ("\n");
    }
}

void printBoard(int myBoard[][5])
{
	//int i, j;
	printf("   ");

	for (int i = 0; i < 5; i++)
	{
		printf("%d ", i);
	};
	printf("\n");

	for (int i = 0; i < 5; i++)
	{
		printf("%d  ", i);

		for (int j = 0; j < 5; j++) 
		{	
			if (myBoard[i][j] == -1)
			{
				printf("* ");
			} else
			printf("%d ", myBoard[i][j]);
		}
		printf("\n");
	}
	return;
}

void open_pos(int row, int col) {
	int i, j;
	T[row][col] = 1; // ????nh d???u ?? ??ang x??t ???? ???????c m???
	if (B[row][col] == 0) { // N???u ?? ??ang x??t tr???ng v?? c?? m???t ????? b???ng 0
		// X??t c??c ?? xung quanh
		for (i = -1; i < 2; i++) {
		    for (j = -1; j < 2; j++) {
				if (i!=0 || j!=0) {
					// Ki???m tra ??i???u ki???n c??c ??
					if (row + i >= 0 && row + i < 5 && col + j >=0 && col + j < 5) { 
						if (!T[row + i][col + j])
							open_pos(row + i, col + j);					}
				}
			}
		}
	}
}


int count_remain() {
	int cnt = 0;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (T[i][j] == 0)
				cnt++;
	return cnt;
}


int main(int argc, char const *argv[])
{
	int r, c;
	int k = 2;
	bool gameOver = false;
	init();
	count_mines();
	printMap1();

	while (gameOver == false) {
		/*Ch???n ?? c???n m???*/
		makeMove(&r, &c);

		open_pos(r, c);
			/*Ki???m tra tr??ng m??n*/
			if (B[r][c] == MINE){
				printBoard(B);
				printf("You lose!\n");
				gameOver = true;
			}
			else{
				printMap1();
				if (count_remain() == k) {
			        	printf("You are the winner!\n");
					/*k???t th??c*/
					gameOver = true;
		    		};

			}
		}
	
	return 0;
}
