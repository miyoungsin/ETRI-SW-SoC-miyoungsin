#include <opencv2/opencv.hpp>
#include <iostream>
#include <time.h>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "maxpooling.h"
#include "filterweight.h"
#include "inputimage.h"
#include "convolution.h"
using namespace cv;
using namespace std;

double *Activation(double *con_num,int num)
{
	for (int i=0; i<num; i++)
    {
       if(con_num[i] <= 0) {con_num[i] = 0;}
    }
    return con_num;
}
double *Ip(double *con_num, int ip_num,int output, double *ip)
{
	double *result_num;
    result_num= (double*)malloc(sizeof(double)*output);

    int n=0;

    for(int i=0; i<output; i++)
    {   
        result_num[i]=0;        
    }

    for(int i=0; i<output; i++)
    {   
        for (int j=0; j<ip_num; j++)
        {
            result_num[i]+=con_num[j]*ip[n];
             printf("[%d]  %lf   ",j,con_num[j]); 
            n++;         
        }       
    }

       
    return result_num;
}

int main()
{
    Mat imaged;

    imaged = imread("1.png",IMREAD_GRAYSCALE);
    if(imaged.empty())
    {
        cout<<"not image"<<endl;
        return -1;
    }

    double ***a;
    double ****b;
    double ***conv1;
    double ***pool1;
    double ***c;
    double ****d;
    double ***conv2;
    double ***pool2;

    a = NEW(0,1,imaged, 1); // int p,int s, Mat image, int channel
    b =  Filter(5,5, 20, 1); // int f_row, int f_col, double ****&b, int size, int channel
    conv1 = convolution(24,24,a,1,5,5,0,b, 1,20); //conv1 20x24x24
    pool1 = MaxPooling(conv1, 12,12, 2,2, 2, 20);//pool1 20x12x12

    d = Filter(5,5,50,20);
    conv2 = convolution(8,8,pool1,1,5,5,0,d, 20,50);//conv2 50x8x8
    pool2 = MaxPooling(conv2, 4,4, 2,2, 2,50);//pool2 50x4x4

	double *con_num;
	int num=0;

    con_num= (double*)malloc(sizeof(double)*800);

	for(int i=0; i<50; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                con_num[num]=pool2[i][j][k];
                      
                 printf("%lf ",pool2[i][j][k]);      
    
				num++;
            }
        }
    }
    cout<<endl<<endl;
 

    double ip1[400000] = {0,};
    int n=0;

    FILE *f = fopen("Ip1WeightOrigin.txt","r");

    if(f==NULL){
        cout<<"error"<<endl;
        return 1;}
    
    double q;
    while(fscanf(f,"%lf, ",&q)!=EOF)
    {
        ip1[n]=q;
        n++;
    }
    fclose(f);

    double *re_num;
    double *re_relu;
    double *re_num2;

    re_num = Ip(con_num,800,500,ip1);//ip1 800->500  
    re_relu = Activation(re_num,500); //relu

    double ip2[5000] = {0,};
    n=0;

    f = fopen("Ip2WeightOrigin.txt","r");

    if(f==NULL){
        cout<<"error"<<endl;
        return 1;}
    
    while(fscanf(f,"%lf, ",&q)!=EOF)
    {
        ip2[n]=q;
        n++;
    }
    fclose(f);

    re_num2 = Ip(re_relu,500,10,ip2);//ip2 500->10

    cout<<endl<<endl;

    for(int i=0; i<10; i++)
    {
        printf("%d =  %lf \n",i,re_num2[i]);
    }
	return 0;
}