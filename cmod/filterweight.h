#include <opencv2/opencv.hpp>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace cv;
using namespace std;

FILE *fp;

double ****Filter(int f_row, int f_col, int size, int channel)
{
    double ****b;
    b= new double ***[size];
    for(int i=0; i<size; i++)
    {
        b[i]=new double **[channel];
        for(int j=0; j<channel; j++)
        {
            b[i][j]=new double *[f_row];
            for(int k=0; k<f_row; k++)
            {
                b[i][j][k]=new double [f_col];
            }
        }
    }
     
    if(channel==1) { fp = fopen("Conv1WeightOrigin.txt","r"); }
    else { fp = fopen("Conv2WeightOrigin.txt","r"); }
    if(fp==NULL)
    {
        cout<<"error"<<endl;
        //return 0;
    }

    double q;
    int i=0,j=0,k=0,l=0;

    while(fscanf(fp,"%lf, ",&q)!=EOF)
    {
        b[i][j][k][l]=q;
        if(j>=channel-1 && k>=f_row-1 && l>=f_col-1) {i++; j=0; k=0; l=0;}
        else if(k>=f_row-1 && l>=f_col-1) {j++; k=0; l=0;}
        else if(l>=f_col-1) {k++; l=0;}
        else { l++; }
    }
/*
    for(int f = 0; f<20 ; f++){
       for(int g = 0 ; g< 1 ;  g++){
           for(int j = 0; j < 5 ; j++){
               for(int k = 0 ; k < 5 ; k++){
                   //printf("%lf  ",b[f][g][j][k]);
               }
               //cout<<endl;
           }
           //cout<<endl;
       }
       //cout<<endl;
   }
*/
    fclose(fp);

    return b;
}