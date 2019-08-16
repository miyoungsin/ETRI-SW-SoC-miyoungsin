#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

double*** convolution(int rowsize, int colsize, double ***a, int s, int f_row, int f_col,  int p, double ****b,  int channel, int size)
{                  // conv1 = convolution(24,24,a,1,5,5,0,b, 1,20);

    double ***result;
    
    result = (double***)malloc(sizeof(double**)*size);
    for(int cha = 0 ; cha < size ; cha++){
        *(result + cha) = (double**)malloc(sizeof(double*)*rowsize);
        for(int row = 0; row<rowsize; row++){
            *(*(result +cha)+row) =(double*)malloc(sizeof(double)*colsize);
            }
    }

    for(int f=0; f<size; f++)
    {
        for(int g=0; g<channel; g++)
        {
            for(int h=0; h<rowsize; h++)
            {
                for(int i=0; i<colsize; i++)
                {
                    for(int j=0; j<f_row; j++)
                    {
                        for(int k=0;  k<f_col ; k++)
                        {
                             result[f][h][i] += b[f][g][j][k]*a[g][h+j*s][i+k*s];
                        }         
                    }       
                }
            }
        }
    }
    return result;
}