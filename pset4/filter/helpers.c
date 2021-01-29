#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float gray=0;
            gray+=image[i][j].rgbtRed;
            gray+=image[i][j].rgbtGreen;
            gray+=image[i][j].rgbtBlue;
            gray=(int)(gray/3+0.5);

            image[i][j].rgbtRed=gray;
            image[i][j].rgbtGreen=gray;
            image[i][j].rgbtBlue=gray;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int width_=width/2;
    for(int i=0; i<height;i++){
        for(int j=0;j<width_;j++){
            RGBTRIPLE temp_=image[i][j];
            image[i][j]=image[i][width-j-1];
            image[i][width-j-1]=temp_;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_[height][width];
    int h_=height-1;
    int w_=width-1;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            float nrgb[3]={0,0,0};
            int ise[2]={-1,1};
            int jse[2]={-1,1};
            ise[0]=(i==0)?0:-1;
            ise[1]=(i==h_)?0:1;
            jse[0]=(j==0)?0:-1;
            jse[1]=(j==w_)?0:1;
            int c_=0;
            for(int ai=ise[0];ai<=ise[1];ai++){
                for(int aj=jse[0];aj<=jse[1];aj++){
                    nrgb[0]+=image[i+ai][j+aj].rgbtRed;
                    nrgb[1]+=image[i+ai][j+aj].rgbtGreen;
                    nrgb[2]+=image[i+ai][j+aj].rgbtBlue;
                    c_++;
                }
            }
            image_[i][j].rgbtRed=(int)(nrgb[0]/c_+0.5);
            image_[i][j].rgbtGreen=(int)(nrgb[1]/c_+0.5);
            image_[i][j].rgbtBlue=(int)(nrgb[2]/c_+0.5);
        }
    }
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            image[i][j].rgbtRed = image_[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_[i][j].rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    double imagergb[height][width][3];
    imagergb[0][0][0]=0;
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            imagergb[i][j][0]=image[i][j].rgbtRed;
            imagergb[i][j][1]=image[i][j].rgbtGreen;
            imagergb[i][j][2]=image[i][j].rgbtBlue;
        }
    }
    int h_=height-1;
    int w_=width-1;
    int ijadd[3]   = {-1, 0, 1};
    int frame[3][3]={{-1,-2,-1},{0,0,0},{1,2,1}};
    for(int i=0;i<height;i++){
        for(int j=0;j<width;j++){
            double gx[3]={0,0,0};
            double gy[3]={0,0,0};
            int nrgb[3];
            for(int rgbi=0;rgbi<3;rgbi++){
                for(int ii=(i>0)?0:1;ii<((i<h_)?3:2);ii++){
                    for(int jj=(j>0)?0:1;jj<((j<w_)?3:2);jj++){
                        gx[rgbi]+=imagergb[i+ijadd[ii]][j+ijadd[jj]][rgbi]*frame[ii][jj];
                        gy[rgbi]+=imagergb[i+ijadd[ii]][j+ijadd[jj]][rgbi]*frame[jj][ii];
                    }
                }
                
                gx[rgbi]*=gx[rgbi];
                gy[rgbi]*=gy[rgbi];
                nrgb[rgbi]=(int)(pow(gx[rgbi]+gy[rgbi],0.5)+0.5);
            }
            image[i][j].rgbtRed  =nrgb[0]>255?255:nrgb[0];
            image[i][j].rgbtGreen=nrgb[1]>255?255:nrgb[1];
            image[i][j].rgbtBlue =nrgb[2]>255?255:nrgb[2];
        }
    }
    return;
}
