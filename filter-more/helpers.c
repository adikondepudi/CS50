#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            avg = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3;
            if ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)%3 == 0){
                image[i][j].rgbtRed = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtBlue = avg;
            }
            else if((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue + 1)%3 == 0){
                avg++;
                image[i][j].rgbtRed = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtBlue = avg;
            }
            else{
                image[i][j].rgbtRed = avg;
                image[i][j].rgbtGreen = avg;
                image[i][j].rgbtBlue = avg;
            }
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tempRed = 0;
    int tempGreen = 0;
    int tempBlue = 0;
        for(int i = 0; i < height; i++){
            for (int j = 0; j < width/2; j++){
                tempRed = image[i][width-1-j].rgbtRed;
                tempGreen = image[i][width-1-j].rgbtGreen;
                tempBlue = image[i][width-1-j].rgbtBlue;
                image[i][width-1-j].rgbtRed = image[i][j].rgbtRed;
                image[i][width-1-j].rgbtGreen = image[i][j].rgbtGreen;
                image[i][width-1-j].rgbtBlue = image[i][j].rgbtBlue;
                image[i][j].rgbtRed = tempRed;
                image[i][j].rgbtGreen = tempGreen;
                image[i][j].rgbtBlue = tempBlue;
            }
        }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE di[height][width];
    int num = 0;
    int sumR = 0;
    int sumG = 0;
    int sumB = 0;
    double sumRd;
    double sumGd;
    double sumBd;
    //first double for loop to traverse image array
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //second double for loop to traverse cells around specified cell
            num = 0;
            sumR = 0;
            sumG = 0;
            sumB = 0;
            sumRd = 0;
            sumGd = 0;
            sumBd = 0;
            for(int x = i - 1; x < i + 2; x++){ //[i][j] is cell. [x][y] are surrounding cells.
                for(int y = j - 1; y < j + 2; y++){
                    if((x < 0) || (x >= height) || (y < 0) || (y >= width)){
                        continue;
                    }
                    num++;
                    sumR+=image[x][y].rgbtRed;
                    sumG+=image[x][y].rgbtGreen;
                    sumB+=image[x][y].rgbtBlue;
                }
            }
            sumRd = (double) sumR/num;
            sumR = (int) round(sumRd);
            sumGd = (double) sumG/num;
            sumG = (int) round(sumGd);
            sumBd = (double) sumB/num;
            sumB = (int) round(sumBd);
            //taking proper values and assigning them properly
            di[i][j].rgbtRed = sumR;
            di[i][j].rgbtGreen = sumG;
            di[i][j].rgbtBlue = sumB;
        }
    }
    for(int a = 0; a < height; a++){
        for(int b = 0; b < width; b++){
            image[a][b] = di[a][b];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE di[height][width];
    int gxr = 0;
    int gxg = 0;
    int gxb = 0;
    int gyr = 0;
    int gyg = 0;
    int gyb = 0;
    // int sumR = 0;
    // int sumG = 0;
    // int sumB = 0;
    int num = 0;
    //first double for loop to traverse image array
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            //second double for loop to traverse cells around specified cell
            gxr = 0;
            gxg = 0;
            gxb = 0;
            gyr = 0;
            gyg = 0;
            gyb = 0;
            // sumR = 0;
            // sumG = 0;
            // sumB = 0;
            num = 0;
            //gx loops
            for(int x = i - 1; x < i + 2; x++){ //[i][j] is cell. [x][y] are surrounding cells.
                for(int y = j - 1; y < j + 2; y++){
                    if((x < 0) || (x >= height) || (y < 0) || (y >= width)){
                        num++;
                        continue;
                    }
                    else if(num == 0){
                        num++;
                        gxr+= -1*image[x][y].rgbtRed;
                        gxg+= -1*image[x][y].rgbtGreen;
                        gxb+= -1*image[x][y].rgbtBlue;
                    }
                    else if(num == 1){
                        num++;
                        continue;
                    }
                    else if(num == 2){
                        num++;
                        gxr+= 1*image[x][y].rgbtRed;
                        gxg+= 1*image[x][y].rgbtGreen;
                        gxb+= 1*image[x][y].rgbtBlue;
                    }
                    else if(num == 3){
                        num++;
                        gxr+= -2*image[x][y].rgbtRed;
                        gxg+= -2*image[x][y].rgbtGreen;
                        gxb+= -2*image[x][y].rgbtBlue;
                    }
                    else if(num == 4){
                        num++;
                        continue;
                    }
                    else if(num == 5){
                        num++;
                        gxr+= 2*image[x][y].rgbtRed;
                        gxg+= 2*image[x][y].rgbtGreen;
                        gxb+= 2*image[x][y].rgbtBlue;
                    }
                    else if(num == 6){
                        num++;
                        gxr+= -1*image[x][y].rgbtRed;
                        gxg+= -1*image[x][y].rgbtGreen;
                        gxb+= -1*image[x][y].rgbtBlue;
                    }
                    else if(num == 7){
                        num++;
                        continue;
                    }
                    else if(num == 8){
                        num++;
                        gxr+= 1*image[x][y].rgbtRed;
                        gxg+= 1*image[x][y].rgbtGreen;
                        gxb+= 1*image[x][y].rgbtBlue;
                    }
                }
            }
            num = 0;
            //gy loops
            for(int x = i - 1; x < i + 2; x++){ //[i][j] is cell. [x][y] are surrounding cells.
                for(int y = j - 1; y < j + 2; y++){
                    if((x < 0) || (x >= height) || (y < 0) || (y >= width)){
                        num++;
                        continue;
                    }
                    else if(num == 0){
                        num++;
                        gyr+= -1*image[x][y].rgbtRed;
                        gyg+= -1*image[x][y].rgbtGreen;
                        gyb+= -1*image[x][y].rgbtBlue;
                    }
                    else if(num == 1){
                        num++;
                        gyr+= -2*image[x][y].rgbtRed;
                        gyg+= -2*image[x][y].rgbtGreen;
                        gyb+= -2*image[x][y].rgbtBlue;
                    }
                    else if(num == 2){
                        num++;
                        gyr+= -1*image[x][y].rgbtRed;
                        gyg+= -1*image[x][y].rgbtGreen;
                        gyb+= -1*image[x][y].rgbtBlue;
                    }
                    else if(num == 3){
                        num++;
                        continue;
                    }
                    else if(num == 4){
                        num++;
                        continue;
                    }
                    else if(num == 5){
                        num++;
                        continue;
                    }
                    else if(num == 6){
                        num++;
                        gyr+= 1*image[x][y].rgbtRed;
                        gyg+= 1*image[x][y].rgbtGreen;
                        gyb+= 1*image[x][y].rgbtBlue;
                    }
                    else if(num == 7){
                        num++;
                        gyr+= 2*image[x][y].rgbtRed;
                        gyg+= 2*image[x][y].rgbtGreen;
                        gyb+= 2*image[x][y].rgbtBlue;
                    }
                    else if(num == 8){
                        num++;
                        gyr+= 1*image[x][y].rgbtRed;
                        gyg+= 1*image[x][y].rgbtGreen;
                        gyb+= 1*image[x][y].rgbtBlue;
                    }
                }
            }
            //taking proper values and assigning them properly
            if(sqrt((gxr*gxr)+(gyr*gyr)) > 255){
                di[i][j].rgbtRed = 255;
            }
            else{
                di[i][j].rgbtRed = round(sqrt((gxr*gxr)+(gyr*gyr)));
            }
            if(sqrt((gxg*gxg)+(gyg*gyg)) > 255){
                di[i][j].rgbtGreen = 255;
            }
            else{
                di[i][j].rgbtGreen = round(sqrt((gxg*gxg)+(gyg*gyg)));
            }
            if(sqrt((gxb*gxb)+(gyb*gyb)) > 255){
                di[i][j].rgbtBlue = 255;
            }
            else{
                di[i][j].rgbtBlue = round(sqrt((gxb*gxb)+(gyb*gyb)));
            }
            // di[i][j].rgbtRed = sqrt((gxr*gxr)+(gyr*gyr));
            // di[i][j].rgbtGreen = sqrt((gxg*gxg)+(gyg*gyg));
            // di[i][j].rgbtBlue = sqrt((gxb*gxb)+(gyb*gyb));
        }
    }
    for(int a = 0; a < height; a++){
        for(int b = 0; b < width; b++){
            image[a][b] = di[a][b];
        }
    }
    return;


    //go through each cell
        //compute gx and gy value of each sell using second set of nested for loops
        //do the calculations with gx and gy
        //if value >255 then set value as 255
}
