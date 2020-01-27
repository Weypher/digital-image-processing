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

    //created the visited matrix
    bool visited[height][width][BytesPerPixel];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                visited[i][j][k] = false;
            }
        }
    }

    int tgt = 0;//start with the gray level 0;
    int count = 0;//count start with 0;
    int threshold = height * width / 256;
//    cout << threshold <<endl;
    int countFreq = 0;

//    for (int channel = 0; channel < 3; channel++) {
//        for (int grayLevel = 0; grayLevel < 256; grayLevel++) {
//            for (int i = 0; i < height; i++) {
//                for (int j = 0; j < width; j++) {
//                    if (!visited[i][j][channel] && (int)Imagedata[i][j][channel] == tgt && count < threshold) {
//                        ImageRes[i][j][channel] = (unsigned char)grayLevel;
//                        visited[i][j][channel] = true;
//                        count++;
//                        countFreq++;
//                    }
//                    if (countFreq == pixelToFreq[tgt][channel]) {
//                        countFreq = 0;
//                        tgt++;
//                    }
//                }
//            }
//            count = 0;
//        }
//        tgt = 0;
//        count = 0;
//        countFreq = 0;
//    }


    int grayLevel = 0;
    for (int channel = 0; channel < 3; channel++) {
        for (int tgt = 0; tgt < 256; tgt++) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (!visited[i][j][channel] && (int) Imagedata[i][j][channel] == tgt && count < threshold) {
                        ImageRes[i][j][channel] = (unsigned char) grayLevel;
                        visited[i][j][channel] = true;
                        count++;
                        countFreq++;
                    }
                    if (count == threshold) {
                        count = 0;
                        grayLevel++;
                    }
                }
            }
        }
        count = 0;
        countFreq = 0;
    }

    //test for after
    int** pixelToFreqAfter =  new int*[256];
    for (int i = 0; i < 256; i++) {
        pixelToFreqAfter[i] = new int[3];
    }
    for (int i = 0; i < 256; i++) {
        for (int j = 0; j < 3; j++) {
            pixelToFreqAfter[i][j] = 0;
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < 3; k++) {
                pixelToFreqAfter[(int)ImageRes[i][j][k]][k]++;
            }
        }
    }


    //test for print out
//    for (int i = 0; i < 256; i++) {
//        cout << pixelToFreq[i][0] << " " << pixelToFreq[i][1] << " " << pixelToFreq[i][2] << endl;
//    }
//    for (int i = 0; i < 256; i++) {
//        cout << pixelToFreqAfter[i][0] << " " << pixelToFreqAfter[i][1] << " " << pixelToFreqAfter[i][2] << endl;
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
    //R
    for(int i = 0; i < 256; i++){
        intenseToFreq[i] = 0;
    }
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            intenseToFreq[(int)ImageRes[i][j][0]]++;
        }
    }
    FILE *fp = NULL ;
//    fp = fopen("/Users/wenboye/CLionProjects/test/res_red_2.csv","w") ;
//    for (int i=0 ; i<256 ;i++)
//        fprintf(fp,"%d\n",intenseToFreq[i] ) ;
//    fclose(fp);

    return 0;
}

