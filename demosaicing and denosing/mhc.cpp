// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel, BytesOutPut;
    int height, width;

    // Check for proper syntax
    if (argc < 3){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 4){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[3]);
    }

    // Check if image has specific width
    if (argc < 5) {
        width = 256;
    } else {
        width = atoi(argv[4]);
    }

    // Check if image has specific height
    if (argc < 6) {
        height = 256;
    } else {
        height = atoi(argv[5]);
    }

    // Check if image has specific width
    if (argc < 7) {
        BytesOutPut = 1;
    } else {
        BytesOutPut = atoi(argv[6]);
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];
    unsigned char ImageRes[height][width][BytesOutPut];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);

    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
    //create an pic of fixed bound
    unsigned char fixedBoundPic[height + 4][width + 4][BytesPerPixel];
    for (int i = 2; i < height + 2; i++) {
        for (int j = 2; j < width + 2 ; j++) {
            fixedBoundPic[i][j][0] = Imagedata[i - 2][j - 2][0];
        }
    }

    for (int i = 0; i < width; i++) {
        fixedBoundPic[0][i + 2][0] = fixedBoundPic[3][i + 2][0];
        fixedBoundPic[1][i + 2][0] = fixedBoundPic[2][i + 2][0];
        fixedBoundPic[height + 3][i + 2][0] = fixedBoundPic[height][i + 2][0];
        fixedBoundPic[height + 2][i + 2][0] = fixedBoundPic[height + 1][i + 2][0];
    }
    for (int i = 0; i < height; i++) {
        fixedBoundPic[i][0][0] = fixedBoundPic[i][3][0];
        fixedBoundPic[i][1][0] = fixedBoundPic[i][2][0];
        fixedBoundPic[i][width + 3][0] = fixedBoundPic[i][width][0];
        fixedBoundPic[i][width + 2][0] = fixedBoundPic[i][width + 1][0];
    }

    double temp;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //case 1: at green center1
            int n = i + 2;
            int m = j + 2;
            if (i % 2 == 0 && j % 2 == 0) {


//                double beta = 5 / 8;
//                double offset = (double)fixedBoundPic[n][m][0] - (double)(0.125 * ((double)fixedBoundPic[n - 2][m - 2][0] +
//                        (double)fixedBoundPic[n - 2][m][0] + (double)fixedBoundPic[n - 2][m + 2][0] +
//                        (double)fixedBoundPic[n][m - 2][0] + (double)fixedBoundPic[n][m + 2][0] +
//                        (double)fixedBoundPic[n + 2][m - 2][0] + (double)fixedBoundPic[n + 2][m][0] +
//                        (double)fixedBoundPic[n + 2][m + 2][0]));
//                //red
//                ImageRes[i][j][0] = (unsigned char) (
//                        ((double) fixedBoundPic[n][m - 1][0] + (double) fixedBoundPic[n][m + 1][0]) / 2 + beta * offset);
//                //green
//                ImageRes[i][j][1] = fixedBoundPic[n][m][0];
//                //blue
//                ImageRes[i][j][2] = (unsigned char) (
//                        ((double) fixedBoundPic[n - 1][m][0] + (double) fixedBoundPic[n + 1][m][0]) / 2 + beta * offset);

                //red
                temp = (-2*((double)fixedBoundPic[n][m-2][0]+ (double)fixedBoundPic[n-1][m-1][0]+(double)fixedBoundPic[n+1][m-1][0]+(double)fixedBoundPic[n-1][m+1][0]+(double)fixedBoundPic[n+1][m+1][0]+fixedBoundPic[n][m+2][0])
                                     + (double)(fixedBoundPic[n-2][m][0]+(double)fixedBoundPic[n+2][m][0] + 8*((double)fixedBoundPic[n][m-1][0]+(double)fixedBoundPic[n][m+1][0]) + 10 * (double)fixedBoundPic[n][m][0]))/16;
                ImageRes[i][j][0] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

                //green
                ImageRes[i][j][1] = fixedBoundPic[n][m][0];
                //blue
                temp = (-2*((double)fixedBoundPic[n-2][m][0]+ (double)fixedBoundPic[n-1][m-1][0]+(double)fixedBoundPic[n+1][m-1][0]+(double)fixedBoundPic[n-1][m+1][0]
                        +(double)fixedBoundPic[n+1][m+1][0]+(double)fixedBoundPic[n+2][m][0]) + ((double)fixedBoundPic[n][m-2][0]+(double)fixedBoundPic[n][m+2][0]
                                + 8*((double)fixedBoundPic[n-1][m][0]+(double)fixedBoundPic[n+1][m][0]) + 10 * (double)fixedBoundPic[n][m][0]))/16;
                ImageRes[i][j][2] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);


            } else if (i % 2 == 1 && j % 2 == 1) {//case 2 : at green center2
//                double beta = 5 / 8;
//                double offset = (double)fixedBoundPic[n][m][0] - (double)(0.125 * ((double)fixedBoundPic[n - 2][m - 2][0] +
//                                                                                   (double)fixedBoundPic[n - 2][m][0] + (double)fixedBoundPic[n - 2][m + 2][0] +
//                                                                                   (double)fixedBoundPic[n][m - 2][0] + (double)fixedBoundPic[n][m + 2][0] +
//                                                                                   (double)fixedBoundPic[n + 2][m - 2][0] + (double)fixedBoundPic[n + 2][m][0] +
//                                                                                   (double)fixedBoundPic[n + 2][m + 2][0]));
//                //red
//                ImageRes[i][j][0] = (unsigned char) (
//                        ((double) fixedBoundPic[n - 1][m][0] + (double) fixedBoundPic[n + 1][m][0]) / 2 + beta * offset);
//                //green
//                ImageRes[i][j][1] = fixedBoundPic[n][m][0];
//                //blue
//                ImageRes[i][j][2] = (unsigned char) (
//                        ((double) fixedBoundPic[n][m - 1][0] + (double) fixedBoundPic[n][m + 1][0]) / 2 + beta * offset);

                //red
                temp = (-2*((double)fixedBoundPic[n-2][m][0]+ (double)fixedBoundPic[n-1][m-1][0]+(double)fixedBoundPic[n+1][m-1][0]
                        +(double)fixedBoundPic[n-1][m+1][0]+(double)fixedBoundPic[n+1][m+1][0]+(double)fixedBoundPic[n+2][m][0])
                                + ((double)fixedBoundPic[n][m-2][0]+(double)fixedBoundPic[n][m+2][0] + 8*((double)fixedBoundPic[n-1][m][0]
                                +(double)fixedBoundPic[n+1][m][0]) + 10 * (double)fixedBoundPic[n][m][0]))/16;
                ImageRes[i][j][0] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

                //green
                ImageRes[i][j][1] = fixedBoundPic[n][m][0];
                //blue
                temp = (-2*((double)fixedBoundPic[n][m-2][0]+ (double)fixedBoundPic[n-1][m-1][0]+(double)fixedBoundPic[n+1][m-1][0]+(double)fixedBoundPic[n-1][m+1][0]+(double)fixedBoundPic[n+1][m+1][0]+fixedBoundPic[n][m+2][0])
                        + (double)(fixedBoundPic[n-2][m][0]+(double)fixedBoundPic[n+2][m][0] + 8*((double)fixedBoundPic[n][m-1][0]+(double)fixedBoundPic[n][m+1][0]) + 10 * (double)fixedBoundPic[n][m][0]))/16;
                ImageRes[i][j][2] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

            } else if (i % 2 == 1 && j % 2 == 0) {//case 3 : at blue center
//                double gama = 3 / 4;
//                double offset = (double)fixedBoundPic[n][m][0] - (double)(0.125 * ((double)fixedBoundPic[n - 2][m - 2][0] +
//                                                                                   (double)fixedBoundPic[n - 2][m][0] + (double)fixedBoundPic[n - 2][m + 2][0] +
//                                                                                   (double)fixedBoundPic[n][m - 2][0] + (double)fixedBoundPic[n][m + 2][0] +
//                                                                                   (double)fixedBoundPic[n + 2][m - 2][0] + (double)fixedBoundPic[n + 2][m][0] +
//                                                                                   (double)fixedBoundPic[n + 2][m + 2][0]));
//                //red
//                ImageRes[i][j][0] = (unsigned char) (0.25 * ((double) fixedBoundPic[n - 1][m - 1][0] +
//                                                             (double) fixedBoundPic[n + 1][m + 1][0] +
//                                                             (double) fixedBoundPic[n + 1][m - 1][0] +
//                                                             (double) fixedBoundPic[n - 1][m + 1][0]) + gama * offset);
//                //green
//                ImageRes[i][j][1] = (unsigned char) (0.25 * ((double) fixedBoundPic[n - 1][m][0] +
//                                                             (double) fixedBoundPic[n + 1][m][0] +
//                                                             (double) fixedBoundPic[n][m + 1][0] +
//                                                             (double) fixedBoundPic[n][m - 1][0]) + gama * offset);
//                //blue
//                ImageRes[i][j][2] = fixedBoundPic[n][m][0];

                //red
                temp = (12*(double)fixedBoundPic[n][m][0] + 4*((double)fixedBoundPic[n-1][m-1][0]+(double)fixedBoundPic[n-1][m+1][0]
                        +(double)fixedBoundPic[n+1][m-1][0]+(double)fixedBoundPic[n+1][m+1][0])
                                - 3*((double)fixedBoundPic[n][m-2][0]+(double)fixedBoundPic[n][m+2][0]+(double)fixedBoundPic[n-2][m][0]
                                +(double)fixedBoundPic[n+2][m][0]))/16;
                ImageRes[i][j][0] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

                //green
                temp = (2*((double)fixedBoundPic[n][m-1][0]+(double)fixedBoundPic[n][m+1][0]+(double)fixedBoundPic[n-1][m][0]
                        +(double)fixedBoundPic[n+1][m][0]) + 4*(double)fixedBoundPic[n][m][0] - ((double)fixedBoundPic[n][m-2][0]
                                +(double)fixedBoundPic[n][m+2][0]+(double)fixedBoundPic[n-2][m][0]+(double)fixedBoundPic[n+2][m][0]))/8;
                ImageRes[i][j][1] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

                //blue
                ImageRes[i][j][2] = fixedBoundPic[n][m][0];



            } else {//case 4 : at red center
//                double alpha = 1 / 2;
//                double offset = (double)fixedBoundPic[n][m][0] - (double)(0.125 * ((double)fixedBoundPic[n - 2][m][0] + (double)fixedBoundPic[n][m - 2][0] +
//                                                                                    (double)fixedBoundPic[n][m + 2][0] + (double)fixedBoundPic[n + 2][m][0]));
//                //red
//                ImageRes[i][j][0] = fixedBoundPic[n][m][0];
//                //green
//                ImageRes[i][j][1] = (unsigned char) (0.25 * ((double) fixedBoundPic[n - 1][m][0] +
//                                                             (double) fixedBoundPic[n + 1][m][0] +
//                                                             (double) fixedBoundPic[n][m + 1][0] +
//                                                             (double) fixedBoundPic[n][m - 1][0]) + alpha * offset);
//                //blue
//                ImageRes[i][j][2] = (unsigned char) (0.25 * ((double) fixedBoundPic[n - 1][m - 1][0] +
//                                                             (double) fixedBoundPic[n + 1][m + 1][0] +
//                                                             (double) fixedBoundPic[n + 1][m - 1][0] +
//                                                             (double) fixedBoundPic[n - 1][m + 1][0]) + alpha * offset);

                //red
                ImageRes[i][j][0] = fixedBoundPic[n][m][0];
                //green
                temp = (2*((double)fixedBoundPic[n][m-1][0]+(double)fixedBoundPic[n][m+1][0]+(double)fixedBoundPic[n-1][m][0]
                           +(double)fixedBoundPic[n+1][m][0]) + 4*(double)fixedBoundPic[n][m][0] - ((double)fixedBoundPic[n][m-2][0]
                                                                                                    +(double)fixedBoundPic[n][m+2][0]+(double)fixedBoundPic[n-2][m][0]+(double)fixedBoundPic[n+2][m][0]))/8;
                ImageRes[i][j][1] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

                //blue
                temp = (12*(double)fixedBoundPic[n][m][0] + 4*((double)fixedBoundPic[n-1][m-1][0]+(double)fixedBoundPic[n-1][m+1][0]
                                                               +(double)fixedBoundPic[n+1][m-1][0]+(double)fixedBoundPic[n+1][m+1][0])
                        - 3*((double)fixedBoundPic[n][m-2][0]+(double)fixedBoundPic[n][m+2][0]+(double)fixedBoundPic[n-2][m][0]
                             +(double)fixedBoundPic[n+2][m][0]))/16;
                ImageRes[i][j][2] = (unsigned char)(temp > 255 ? 255 : temp < 0 ? 0 : temp);

            }
        }
    }

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(ImageRes, sizeof(unsigned char), height * width * BytesOutPut, file);
    fclose(file);

    return 0;
}