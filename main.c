/* 
	Copyright © 2013 Reagan Lopez
	[This program is licensed under the "MIT License"]
*/

/*****************************************************************/
/* main.c: 		Program to solve the 8-Queens problem. Prints the
/*              successful solutions in the chessboard format
/*              in an output file.
/* Author: Reagan Lopez
/* Date: 06/29/2013
/*****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N = 8; //chessboard dimension.
const char* OUTPUTFILE = "outputfile.txt"; //output file name.
const char* OUTPUTFILE_BRUTEFORCE = "outputfile_bruteforce.txt"; //output file name for bruteforce.
int chessboard[8][8];
int iter_brute = 0; //brute force total iterations
int iter_efficient = 0; //efficient algorithm total iterations
int sol_brute = 0; //brute force total solutions
int sol_efficient = 0; //efficient algorithm total iterations

typedef struct
{
    int x, y;
} pos;


/*****************************************************************/
/* Function to determine the successful positions of the queen.
/* It is based on the algorithm specified by Niklaus Wirth using
/* 3 boolean arrays to mark the positions on the chessboard that
/* have already been visited.
/*****************************************************************/
void nqueens(int n)
{
    int cnt1, cnt2 = -1, cnt3 = -1, col = 0, array[100][3] = {0};
    int *startpos;
    pos P1, P2, P3;
    FILE *fp;
    fp = fopen(OUTPUTFILE, "w");
    pos *head1 = (pos *)malloc(n * n * sizeof(pos)); //allocate struct of N*N positions.
    startpos = (int *)malloc(n * sizeof(int)); //allocate stack of n integers.

	//startpos the algorithm by placing the queen in varying positions of the first row.
	//Create an array to track the position of the queen in the first row.
    for(cnt1 = n - 1; cnt1 >= 0; cnt1--)
    {
		iter_efficient++;
        P1.x = 0;
        P1.y = cnt1;
        head1[++cnt2] = P1;
     };

    while(cnt2 >= 0)
    {
		iter_efficient++;
        P1 = head1[cnt2--];//pop each position of the queen in the first row.
        while(cnt3 >= 0 && P1.x <= cnt3)
        {
			iter_efficient++;
            P2.x = cnt3;
            P2.y = startpos[cnt3--];
            array[P2.y][0] = 0;
            array[P2.x + P2.y][1] = 0;
            array[P2.x - P2.y + n][2] = 0;
        }
        startpos[++cnt3] = P1.y;
        array[P1.y][0] = 1;
        array[P1.x + P1.y][1] = 1;
        array[P1.x - P1.y + n][2] = 1;

        if(cnt3 == n - 1)
        {
			sol_efficient++;
			fprintf(fp, "\n Successful position: %d.\n", sol_efficient);
			fprintf(fp, "  + A B C D E F G H +\n");
			for(cnt1 = 0; cnt1 <= cnt3; cnt1++)
			{
				fprintf(fp, "%d | ", cnt1 + 1);
				for(col = 0; col < n; col++)
				{
					if (col == startpos[cnt1])
						fprintf(fp, "Q ");
					else
						fprintf(fp, ". ");;
				}
				fprintf(fp, "|\n");
			}
			fprintf(fp, "  + A B C D E F G H +\n");
			P2.x = cnt3;
			P2.y = startpos[cnt3--];
			array[P2.y][0] = 0;
			array[P2.x + P2.y][1] = 0;
			array[P2.x - P2.y + n][2] = 0;

		}
		else
		{
			for(cnt1 = n - 1; cnt1 >= 0; cnt1--)
			{
				iter_efficient++;
				if(array[cnt1][0] == 0 && array[P1.x + 1 + cnt1][1] == 0 && array[n + P1.x + 1 - cnt1][2] == 0)
				{
					P3.x = P1.x + 1;
					P3.y = cnt1;
					head1[++cnt2] = P3;
				};
			}
        }
    }
    printf("\nEfficient Algorithm solutions: %d, and iterations: %d", sol_efficient, iter_efficient);
    fprintf(fp, "\nEfficient Algorithm solutions: %d, and iterations: %d", sol_efficient, iter_efficient);
    fclose(fp);
    printf("\nSuccessful positions are printed in the file %s.\n", OUTPUTFILE);
}

void print_chessboard()
{
	int i, j;
	printf("\n\n");
	for (i = 0; i < 8; i++)
	{
		printf("\n");
		for (j = 0; j < 8; j++)
			printf("%d ", chessboard[i][j]);
	}

}

/*****************************************************************/
/* Function to mark the dangerous positions in the brute force
/* algorithm.
/*****************************************************************/
void mark_danger(int x, int y)
{
	int i, j;

	for (i = x - 1, j = y - 1; (i >=0 && j >= 0); i--, j--)
	{
		iter_brute++;
		if(chessboard[i][j] == 0)
			chessboard[i][j] = x+1;
	}
	for (i = x + 1, j = y + 1; (i < 8 && j < 8); i++, j++)
	{
		iter_brute++;
		if(chessboard[i][j] == 0)
			chessboard[i][j] = x+1;
	}
	for (i = x - 1, j = y + 1; (i >=0 && j < 8); i--, j++)
	{
		iter_brute++;
		if(chessboard[i][j] == 0)
			chessboard[i][j] = x+1;
	}
	for (i = x + 1, j = y - 1; (i < 8 && j >= 0); i++, j--)
	{
		iter_brute++;
		if(chessboard[i][j] == 0)
			chessboard[i][j] = x+1;
	}
	for (i = 0; i < 8; i++)
	{
		iter_brute++;
		if(chessboard[i][y] == 0)
			chessboard[i][y] = x+1;
	}
}


/*****************************************************************/
/* Function to clear the dangerous positions in the brute force
/* algorithm.
/*****************************************************************/
void clear_danger(int x, int y)
{

	int i, j;
	//printf("\nclear danger for %d,%d",x,y);
	for (i = x - 1, j = y - 1; (i >=0 && j >= 0); i--, j--)
	{
		iter_brute++;
		if(chessboard[i][j] == x+1)
			chessboard[i][j] = 0;
	}
	for (i = x + 1, j = y + 1; (i < 8 && j < 8); i++, j++)
	{
		iter_brute++;
		if(chessboard[i][j] == x+1)
			chessboard[i][j] = 0;
	}
	for (i = x - 1, j = y + 1; (i >=0 && j < 8); i--, j++)
	{
		iter_brute++;
		if(chessboard[i][j] == x+1)
			chessboard[i][j] = 0;
	}
	for (i = x + 1, j = y - 1; (i < 8 && j >= 0); i++, j--)
	{
		iter_brute++;
		if(chessboard[i][j] == x+1)
			chessboard[i][j] = 0;
	}
	for (i = 0; i < 8; i++)
	{
		iter_brute++;
		if(chessboard[i][y] == x+1)
			chessboard[i][y] = 0;
	}
}


/*****************************************************************/
/* Function to determine the successful positions of 8 queens
/* using brute force.
/*****************************************************************/
void queens_bruteforce()
{
    int a, b, c, d, e, f, g, h;
    int flag_a=0, flag_b=0, flag_c=0, flag_d=0, flag_e=0, flag_f=0, flag_g=0, flag_h=0;
    int i, j, k;
    for (i = 0; i < 8; i++)
    	for (j = 0; j < 8; j++)
    		chessboard[i][j] = 0;

    FILE *fp;
    fp = fopen(OUTPUTFILE_BRUTEFORCE, "w");
    for (a = 0; a < 8; a++)
	{
		iter_brute++;
		if (a > 0 )
		{
			clear_danger(0, a - 1);

		}
		if (a == 0)
		{
			clear_danger(0, 7);
		}
		if (chessboard[0][a] == 0)
		{
			mark_danger(0, a);

		}
		else
			continue;
    	for (b = 0; b < 8; b++)
    	{
			iter_brute++;
			if (b > 0 )
			{
				clear_danger(1, b - 1);
			}
			if (b == 0)
			{
				clear_danger(1, 7);
			}
			if (chessboard[1][b] == 0)
			{
				mark_danger(1, b);
			}
			else
			{
				if(b == 7)
					clear_danger(0,7);
				continue;
			}
    		for (c = 0; c < 8; c++)
			{
				iter_brute++;
				if (c > 0 )
				{
					clear_danger(2, c - 1);
				}
				if (c == 0)
				{
					clear_danger(2, 7);
				}
				if (chessboard[2][c] == 0)
				{
					mark_danger(2, c);
				}
				else
				{
					if(c == 7)
						clear_danger(1,7);
					continue;
				}
    			for (d = 0; d < 8; d++)
				{
					iter_brute++;
					if (d > 0 )
					{
						clear_danger(3, d - 1);
					}
					if (d == 0)
					{
						clear_danger(3, 7);
					}
					if (chessboard[3][d] == 0)
					{
						mark_danger(3, d);
					}
					else
					{
						if(d == 7)
							clear_danger(2,7);
						continue;
					}
    				for (e = 0; e < 8; e++)
					{
						iter_brute++;
						if (e > 0 )
						{
							clear_danger(4, e - 1);
						}
						if (e == 0)
						{
							clear_danger(4, 7);
						}
						if (chessboard[4][e] == 0)
						{
							mark_danger(4, e);
						}
						else
						{
							if(e == 7)
								clear_danger(3,7);
							continue;
						}
    					for (f = 0; f < 8; f++)
						{
							iter_brute++;
							if (f > 0 )
							{
								clear_danger(5, f - 1);
							}
							if (f == 0)
							{
								clear_danger(5, 7);
							}
							if (chessboard[5][f] == 0)
							{
								mark_danger(5, f);
							}
							else
							{
								if(f == 7)
									clear_danger(4,7);
								continue;
							}
    						for (g = 0; g < 8; g++)
							{
								iter_brute++;

								if (g > 0)
								{
									clear_danger(6, g - 1);
								}
								if (g == 0)
								{
									clear_danger(6, 7);
								}
								if (chessboard[6][g] == 0)
								{
									mark_danger(6, g);
								}
								else
								{
									if(g == 7)
										clear_danger(5,7);
									continue;
								}
    							for (h = 0; h < 8; h++)
								{
									iter_brute++;
									if (chessboard[7][h] == 0)
									{
										sol_brute++;
										fprintf(fp, "\n Successful position: %d.\n", sol_brute);
										fprintf(fp, "  + A B C D E F G H +\n");
										fprintf(fp, "1 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == a)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "2 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == b)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "3 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == c)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "4 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == d)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "5 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == e)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "6 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == f)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "7 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == g)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "8 | ");
										for(k = 0; k < 8; k++)
										{
											if (k == h)
												fprintf(fp, "Q ");
											else
												fprintf(fp, ". ");;
										}
										fprintf(fp, "|\n");
										fprintf(fp, "  + A B C D E F G H +\n");
									}
									else
									{
										if(h == 7)
											clear_danger(6,7);
										continue;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	printf("\nBrute Force solutions: %d, and iterations: %d", sol_brute, iter_brute);
    fprintf(fp, "\nBrute Force solutions: %d, and iterations: %d", sol_brute, iter_brute);
    fclose(fp);
    printf("\nSuccessful positions are printed in the file %s.\n", OUTPUTFILE_BRUTEFORCE);

}

/*****************************************************************/
/* Main function.
/*****************************************************************/
int main()
{
	queens_bruteforce();
    nqueens(N);
    printf("\nPress any key to continue...");
    getchar();
    return(0);
}



