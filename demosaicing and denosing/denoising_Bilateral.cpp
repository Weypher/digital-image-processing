// This sample code reads in image data from a RAW image file and
// writes it into another file

// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
//			RAW format. You will need to make corresponding changes to
//			accommodate images of different sizes and/or types

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

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

    if (argc < 8) {
        cout << "to calculate PSNR please add original image.";
    }

    // Allocate image data array
    unsigned char Imagedata[height][width][BytesPerPixel];
    unsigned char ImageOri[height][width][BytesPerPixel];
    unsigned char ImageRes[height][width][BytesOutPut];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), height * width * BytesPerPixel, file);
    fclose(file);

    fclose(file);
    if (!(file=fopen(argv[7],"rb"))) {
        cout << "Cannot open file: " << argv[7] <<endl;
        exit(1);
    }
    fread(ImageOri, sizeof(unsigned char), height * width * BytesPerPixel, file);
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


    //denoising by gass weight function
    double sigmaC = 10;
    double sigmaS = 10;
    for (int i = 2; i < height + 2; i++) {
        for (int j = 2; j < width + 2; j++) {
            double sumWeight = 0;
            double numerator = 0;
            for (int n = -2; n <= 2; n++) {
                for (int m = -2; m <= 2; m++) {
                    double currWeight = exp(-1 * (m * m + n * n) / (2 * sigmaC * sigmaC)
                                            - pow(fixedBoundPic[i + n][j + m][0] - fixedBoundPic[i][j][0], 2) / (2 * sigmaS * sigmaS));
                    sumWeight += currWeight;
                    numerator += currWeight * fixedBoundPic[i + m][j + n][0];
                }
            }
            ImageRes[i - 2][j - 2][0] = (unsigned char)(numerator / sumWeight);
        }
    }

    double MSE = 0;
    double MAX = 255;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            MSE += pow(ImageOri[i][j][0] - ImageRes[i][j][0], 2);
        }
    }
    MSE /= (height * width);

    double PSNR = 10 * log10(MAX * MAX / MSE);

    cout << "Bilateral weight filter : " << PSNR << endl;

    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
    fwrite(ImageRes, sizeof(unsigned char), height * width * BytesOutPut, file);
    fclose(file);

    return 0;
}

