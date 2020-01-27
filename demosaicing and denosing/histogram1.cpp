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
//    //create an pic of fixed bound
//    unsigned char fixedBoundPic[height + 4][width + 4][BytesPerPixel];
//    for (int i = 2; i < height + 2; i++) {
//        for (int j = 2; j < width + 2 ; j++) {
//            for (int k = 0; k < BytesPerPixel; k++) {
//                fixedBoundPic[i][j][k] = Imagedata[i - 2][j - 2][k];
//            }
//        }
//    }
//
//    for (int i = 0; i < width; i++) {
//        for (int j = 0; j < BytesPerPixel; j++) {
//            fixedBoundPic[0][i + 2][j] = fixedBoundPic[3][i + 2][j];
//            fixedBoundPic[1][i + 2][j] = fixedBoundPic[2][i + 2][j];
//            fixedBoundPic[height + 3][i + 2][j] = fixedBoundPic[height][i + 2][j];
//            fixedBoundPic[height + 2][i + 2][j] = fixedBoundPic[height + 1][i + 2][j];
//        }
//    }
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < BytesPerPixel; j++) {
//            fixedBoundPic[i][0][j] = fixedBoundPic[i][3][j];
//            fixedBoundPic[i][1][j] = fixedBoundPic[i][2][j];
//            fixedBoundPic[i][width + 3][j] = fixedBoundPic[i][width][j];
//            fixedBoundPic[i][width + 2][j] = fixedBoundPic[i][width + 1][j];
//        }
//    }

    //create the 2-d array to record the frequency of RGB gray level;
    int** pixelToFreq =  new int*[256];
    for (int i = 0; i < 256; i++) {
        pixelToFreq[i] = new int[3];
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 3; j++) {
            pixelToFreq[i][j] = 0;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                pixelToFreq[(int)Imagedata[i][j][k]][k]++;
            }
        }
    }

    //get the normalized possibility of every gray level;
    float** pixelToFreqProB =  new float*[256];
    for (int i = 0; i < 256; i++) {
        pixelToFreqProB[i] = new float[3];
    }

    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 3; j++) {
            pixelToFreqProB[i][j] = (float)pixelToFreq[i][j] / (height * width);
        }
    }

    //get the cumulative prob
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 3; j++) {
            pixelToFreqProB[i][j] += pixelToFreqProB[i - 1][j];
        }
    }

    //get the related gray level of pixel
    int** enhancedPixelToFreq =  new int*[256];
    for (int i = 0; i < 256; i++) {
        enhancedPixelToFreq[i] = new int[3];
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 3; j++) {
            enhancedPixelToFreq[i][j] = (int)(pixelToFreqProB[i][j] * 255);
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j =0; j < width; j++) {
            for (int k = 0; k < BytesOutPut; k++) {
                int origGray = (int)Imagedata[i][j][k];

                ImageRes[i][j][k] = (unsigned char)enhancedPixelToFreq[origGray][k];
//                cout << origGray << " " << (int)ImageRes[i][j][k] << endl;
            }
        }
    }


    //test  for print out
//    for (int i = 0; i < 256; i++) {
//        cout << pixelToFreq[i][0] << " " << pixelToFreq[i][1] << " " << pixelToFreq[i][2] << " "
//             << pixelToFreqProB[i][0] << " " << pixelToFreqProB[i][1] << " " << pixelToFreqProB[i][2] << " "
//             << enhancedPixelToFreq[i][0] << " " << enhancedPixelToFreq[i][1] << " " << enhancedPixelToFreq[i][2] << endl;
//    }


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[2],"wb"))) {
        cout << "Cannot open file: " << argv[2] << endl;
        exit(1);
    }
//    fwrite(fixedBoundPic, sizeof(unsigned char), height * width * BytesOutPut, file);
//    fclose(file);
    fwrite(ImageRes, sizeof(unsigned char), height * width * BytesOutPut, file);
    fclose(file);


    int intenseToFreq[256];
//    //R
//    for(int i = 0; i < 256; i++){
//        intenseToFreq[i] = 0;
//    }
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            intenseToFreq[(int)Imagedata[i][j][0]]++;
//        }
//    }
//    FILE *fp = NULL ;
//    fp = fopen("/Users/wenboye/CLionProjects/test/ori_red.csv","w") ;
//    for (int i=0 ; i<256 ;i++)
//        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
//    fclose(fp);

    //G
//    for(int i = 0; i < 256; i++){
//        intenseToFreq[i] = 0;
//    }
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            intenseToFreq[(int)Imagedata[i][j][1]]++;
//        }
//    }
//    FILE *fp = NULL ;
//    fp = fopen("/Users/wenboye/CLionProjects/test/ori_green.csv","w") ;
//    for (int i=0 ; i<256 ;i++)
//        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
//    fclose(fp);

//    //B
//    for(int i = 0; i < 256; i++){
//        intenseToFreq[i] = 0;
//    }
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            intenseToFreq[(int)Imagedata[i][j][2]]++;
//        }
//    }
//    FILE *fp = NULL ;
//    fp = fopen("/Users/wenboye/CLionProjects/test/ori_blue.csv","w") ;
//    for (int i=0 ; i<256 ;i++)
//        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
//    fclose(fp);

//    //R result
    for(int i = 0; i < 256; i++){
        intenseToFreq[i] = 0;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            intenseToFreq[(int)ImageRes[i][j][0]]++;
        }
    }
    FILE *fp = NULL ;
    fp = fopen("/Users/wenboye/CLionProjects/test/res_red_1.csv","w") ;
    for (int i=0 ; i<256 ;i++)
        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
    fclose(fp);

//    //G result
//    for(int i = 0; i < 256; i++){
//        intenseToFreq[i] = 0;
//    }
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            intenseToFreq[(int)ImageRes[i][j][1]]++;
//        }
//    }
//    FILE *fp = NULL ;
//    fp = fopen("/Users/wenboye/CLionProjects/test/res_green_1.csv","w") ;
//    for (int i=0 ; i<256 ;i++)
//        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
//    fclose(fp);

//    //B result
//    for(int i = 0; i < 256; i++){
//        intenseToFreq[i] = 0;
//    }
//    for(int i = 0; i < height; i++){
//        for(int j = 0; j < width; j++){
//            intenseToFreq[(int)ImageRes[i][j][2]]++;
//        }
//    }
//    FILE *fp = NULL ;
//    fp = fopen("/Users/wenboye/CLionProjects/test/res_blue_1.csv","w") ;
//    for (int i=0 ; i<256 ;i++)
//        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
//    fclose(fp);



    return 0;
}

