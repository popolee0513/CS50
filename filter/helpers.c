#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
 for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            int a=image[i][j].rgbtRed;
            int b=image[i][j].rgbtGreen;
            int c=image[i][j].rgbtBlue;
            int avg = round ((a+b+c)/3.0);

            image[i][j].rgbtRed=avg;
            image[i][j].rgbtGreen=avg;
            image[i][j].rgbtBlue=avg;
        }
     }
    return;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0;i<height;i++){
        int ans=0;
        if (width%2==0){
            ans=width/2;
        }
        else{
            ans=(width+1)/2;
        }
        for (int j=0;j<ans;j++){
            int a=image[i][j].rgbtRed;
            int b=image[i][j].rgbtGreen;
            int c=image[i][j].rgbtBlue;
            int d=image[i][width-j-1].rgbtRed;
            int e=image[i][width-j-1].rgbtGreen;
            int f=image[i][width-j-1].rgbtBlue;
            image[i][j].rgbtRed =d;
            image[i][j].rgbtGreen=e;
            image[i][j].rgbtBlue=f;
            image[i][width-j-1].rgbtRed=a;
            image[i][width-j-1].rgbtGreen=b;
            image[i][width-j-1].rgbtBlue=c;
        }
        }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    int temp[height*width*3];
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            int a=0;
            int b=0;
            int c=0;
            float counter=0.0;
            if (i-1>=0){
                a+=image[i-1][j].rgbtRed;
                b+=image[i-1][j].rgbtGreen;
                c+=image[i-1][j].rgbtBlue;
                counter+=1.0;
            }
            if (i+1<height){
                a+=image[i+1][j].rgbtRed;
                b+=image[i+1][j].rgbtGreen;
                c+=image[i+1][j].rgbtBlue;
                counter+=1.0;
            }
            if  (j-1>=0){
                a+=image[i][j-1].rgbtRed;
                b+=image[i][j-1].rgbtGreen;
                c+=image[i][j-1].rgbtBlue;
                counter+=1.0;
            }
            if  (j+1<width){
                a+=image[i][j+1].rgbtRed;
                b+=image[i][j+1].rgbtGreen;
                c+=image[i][j+1].rgbtBlue;
                counter+=1.0;
            }
            if  (j+1<width && i-1>=0){
                a+=image[i-1][j+1].rgbtRed;
                b+=image[i-1][j+1].rgbtGreen;
                c+=image[i-1][j+1].rgbtBlue;
                counter+=1.0;
            }
            if  (j+1<width && i+1<height){
                a+=image[i+1][j+1].rgbtRed;
                b+=image[i+1][j+1].rgbtGreen;
                c+=image[i+1][j+1].rgbtBlue;
                counter+=1.0;
            }
            if  (j-1>=0 && i-1>=0){
                a+=image[i-1][j-1].rgbtRed;
                b+=image[i-1][j-1].rgbtGreen;
                c+=image[i-1][j-1].rgbtBlue;
                counter+=1.0;
            }
            if  (j-1>=0 && i+1<height){
                a+=image[i+1][j-1].rgbtRed;
                b+=image[i+1][j-1].rgbtGreen;
                c+=image[i+1][j-1].rgbtBlue;
                counter+=1.0;
            }
             a+=image[i][j].rgbtRed;
             b+=image[i][j].rgbtGreen;
             c+=image[i][j].rgbtBlue;
             counter+=1;
             int avg1 = round (a/ counter);
             int avg2 = round (b/ counter);
             int avg3 = round (c/ counter);
            temp[j*3+0+i*width*3]=avg1;
            temp[j*3+1+i*width*3]=avg2;
            temp[j*3+2+i*width*3]=avg3;
        }
    }
    for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){
            //printf("%i %i %i\n",temp[j*3+0+i*12],temp[j*3+1+i*12],temp[j*3+2+i*12]);
            image[i][j].rgbtRed=temp[j*3+0+i*width*3];
            image[i][j].rgbtGreen=temp[j*3+1+i*width*3];
            image[i][j].rgbtBlue=temp[j*3+2+i*width*3];
        }
    }
    return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

long temp_x[height*width*3];
long temp_y[height*width*3];
int gx[]={-1,0,1,-2,0,2,-1,0,1};
int gy[]={-1,-2,-1,0,0,0,1,2,1};
for (int i=0 ;i<height; i++){
        for (int j=0 ;j<width ;j++){
            int index=0;
            int add_x_1=0;
            int add_y_1=0;
            int add_x_2=0;
            int add_y_2=0;
            int add_x_3=0;
            int add_y_3=0;
            int cur_1=0;
            int cur_2=0;
            int cur_3=0;
            for  (int k=i-1; k<i+2 ; k++)  {
                 for (int f=j-1; f<j+2 ; f++)  {

                     if (0<=k && k<height &&  0<=f  && f<width){
                         cur_1=image[k][f].rgbtRed;
                         cur_2=image[k][f].rgbtGreen;
                         cur_3=image[k][f].rgbtBlue;
                     }
                     else{
                         cur_1=0;
                         cur_2=0;
                         cur_3=0;
                     }
                  add_x_1+=cur_1*gx[index];
                  add_y_1+=cur_1*gy[index];
                  add_x_2+=cur_2*gx[index];
                  add_y_2+=cur_2*gy[index];
                  add_x_3+=cur_3*gx[index];
                  add_y_3+=cur_3*gy[index];
                  index+=1 ;
                }
            }
           temp_x[j*3+0+i*width*3]=add_x_1;
           temp_x[j*3+1+i*width*3]=add_x_2;
           temp_x[j*3+2+i*width*3]=add_x_3;
           temp_y[j*3+0+i*width*3]=add_y_1;
           temp_y[j*3+1+i*width*3]=add_y_2;
           temp_y[j*3+2+i*width*3]=add_y_3;
        }
    }
for (int i=0;i<height;i++){
        for (int j=0;j<width;j++){

            long a1 = round(sqrt(temp_x[j*3+0+i*width*3]*temp_x[j*3+0+i*width*3]+temp_y[j*3+0+i*width*3]*temp_y[j*3+0+i*width*3]));
            long a2 = round(sqrt(temp_x[j*3+1+i*width*3]*temp_x[j*3+1+i*width*3]+temp_y[j*3+1+i*width*3]*temp_y[j*3+1+i*width*3]));
            long a3 = round(sqrt(temp_x[j*3+2+i*width*3]*temp_x[j*3+2+i*width*3]+temp_y[j*3+2+i*width*3]*temp_y[j*3+2+i*width*3]));
            if (a1>255){
                a1=255;
            }
             if (a2>255){
                a2=255;
            }
             if (a3>255){
                a3=255;
            }
            image[i][j].rgbtRed= a1 ;
            image[i][j].rgbtGreen=a2;
            image[i][j].rgbtBlue= a3;
        }
    }
    return;
}
