//// This sample code reads in image data from a RAW image file and
//// writes it into another file
//
//// NOTE:	The code assumes that the image is of size 256 x 256 and is in the
////			RAW format. You will need to make corresponding changes to
////			accommodate images of different sizes and/or types

//reference url:https://github.com/Maud1023/Digital_Image_Processing/blob/master/hw1/code/nl_mean.cpp
//
//#include <stdio.h>
//#include <iostream>
//#include <stdlib.h>
//#include <math.h>
//
//using namespace std;
//
//int main(int argc, char *argv[])
//
//{
//    // Define file pointer and variables
//    FILE *file;
//    int BytesPerPixel, BytesOutPut;
//    int height, width;
//
//    // Check for proper syntax
//    if (argc < 3){
//        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
//        cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [Size = 256]" << endl;
//        return 0;
//    }
//
//    // Check if image is grayscale or color
//    if (argc < 4){
//        BytesPerPixel = 1; // default is grey image
//    }
//    else {
//        BytesPerPixel = atoi(argv[3]);
//    }
//
//    // Check if image has specific width
//    if (argc < 5) {
//        width = 256;
//    } else {
//        width = atoi(argv[4]);
//    }
//
//    // Check if image has specific height
//    if (argc < 6) {
//        height = 256;
//    } else {
//        height = atoi(argv[5]);
//    }
//
//    // Check if image has specific width
//    if (argc < 7) {
//        BytesOutPut = 1;
//    } else {
//        BytesOutPut = atoi(argv[6]);
//    }
//
//    // Allocate image data array
//    unsigned char Imagedata[height][width][BytesPerPixel];
//    unsigned char ImageRes[height][width][BytesOutPut];
//
//    // Read image (filename specified by first argument) into image data matrix
//    if (!(file=fopen(argv[1],"rb"))) {
//        cout << "Cannot open file: " << argv[1] <<endl;
//        exit(1);
//    }
//    fread(Imagedata, sizeof(unsigned char), height * width * BytesPerPixel, file);
//    fclose(file);
//
//    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////
//    //create an pic of fixed bound
//    unsigned char fixedBoundPic[height + 4][width + 4][BytesPerPixel];
//    for (int i = 2; i < height + 2; i++) {
//        for (int j = 2; j < width + 2 ; j++) {
//            fixedBoundPic[i][j][0] = Imagedata[i - 2][j - 2][0];
//        }
//    }
//
//    for (int i = 0; i < width; i++) {
//        fixedBoundPic[0][i + 2][0] = fixedBoundPic[3][i + 2][0];
//        fixedBoundPic[1][i + 2][0] = fixedBoundPic[2][i + 2][0];
//        fixedBoundPic[height + 3][i + 2][0] = fixedBoundPic[height][i + 2][0];
//        fixedBoundPic[height + 2][i + 2][0] = fixedBoundPic[height + 1][i + 2][0];
//    }
//    for (int i = 0; i < height; i++) {
//        fixedBoundPic[i][0][0] = fixedBoundPic[i][3][0];
//        fixedBoundPic[i][1][0] = fixedBoundPic[i][2][0];
//        fixedBoundPic[i][width + 3][0] = fixedBoundPic[i][width][0];
//        fixedBoundPic[i][width + 2][0] = fixedBoundPic[i][width + 1][0];
//    }
//
//
//    //denoising by gass weight function
//
//
//
//
//    // Write image data (filename specified by second argument) from image data matrix
//
//    if (!(file=fopen(argv[2],"wb"))) {
//        cout << "Cannot open file: " << argv[2] << endl;
//        exit(1);
//    }
//    fwrite(ImageRes, sizeof(unsigned char), height * width * BytesOutPut, file);
//    fclose(file);
//
//    return 0;
//}
//

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <cmath>

using namespace std;

int main(int argc, char *argv[])

{
    // Define file pointer and variables
    FILE *file;
    int BytesPerPixel;
    //int Size = 256;
    int Row;
    int Column;


    // Check for proper syntax
    if (argc < 4){
        cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
        cout << "program_name input_image.raw ori_image.raw output_image.raw [BytesPerPixel = 1] [Row = 256] [Column = 256]" << endl;
        //cout << "program_name 1.input_image.raw 2.ori_image.raw 3.output_image.raw 4.[BytesPerPixel = 1] 5.[Row = 256] 6.[Column = 256]" << endl;

        return 0;
    }

    // Check if image is grayscale or color
    if (argc < 5){
        BytesPerPixel = 1; // default is grey image
    }
    else {
        BytesPerPixel = atoi(argv[4]);
        // Check if size is specified
        if (argc >= 6){
//			Size = atoi(argv[4]);
            //BytesPerPixel = atoi(argv[3]);
            Row = atoi(argv[5]);
            Column = atoi(argv[6]);
        }
    }
    cout << "Row and Column: " << Row << " and" << Column <<endl;

    // Allocate image data array
    unsigned char Imagedata[Row][Column][BytesPerPixel];
    unsigned char Imagedata_ori[Row][Column][BytesPerPixel];

    // Read image (filename specified by first argument) into image data matrix
    if (!(file=fopen(argv[1],"rb"))) {
        cout << "Cannot open file: " << argv[1] <<endl;
        exit(1);
    }
    fread(Imagedata, sizeof(unsigned char), Row*Column*BytesPerPixel, file);
    fclose(file);
    cout << "Image read succeed!" <<endl;


    if (!(file=fopen(argv[2],"rb"))) {
        cout << "Cannot open file: " << argv[2] <<endl;
        exit(1);
    }
    fread(Imagedata_ori, sizeof(unsigned char), Row*Column*BytesPerPixel, file);
    fclose(file);

    cout << "BytesPerPixel: " << BytesPerPixel <<endl;
    ///////////////////////// INSERT YOUR PROCESSING CODE HERE /////////////////////////

    //1. Expand the image matrix.

    cout << "1. Expand the image matrix." <<endl;
    int N = 5; //Window size
    int i = 0;
    int j = 0;
    int l = 0;
    int k = 0;
    int ch = 0;



    unsigned char Imagedata_Expassion[Row + N - 1][Column + N - 1][BytesPerPixel];

    //fill inside

    for (k = 0; k < BytesPerPixel; k++){

        for (i = (N - 1)/2; i < Row + (N - 1)/2; i++){
            for (j = (N - 1)/2; j < Column + (N - 1)/2; j++){

                Imagedata_Expassion[i][j][k] = Imagedata[i - (N - 1)/2][j - (N - 1)/2][k];
            }
        }
    }
    cout << "Fill inside succeed!" <<endl;

    //fill the expended column.

    for (k = 0; k < BytesPerPixel; k++){

        for (i = (N - 1)/2; i < Row + (N - 1)/2; i++){
            for (j = 0; j < (N - 1)/2 ; j++){

                Imagedata_Expassion[i][j][k] = Imagedata_Expassion[i][N - 1 - j][k];

            }
            for (j = (N - 1)/2 + Column; j < N - 1 + Column; j++){

                Imagedata_Expassion[i][j][k] = Imagedata_Expassion[i][N - 3 + 2 * Column - j][k];
            }
        }
    }
    cout << "Fill the expended column succeed!" <<endl;
    //fill the expeneded row.

    for(k = 0; k < BytesPerPixel; k++){

        for (i = 0; i < (N - 1)/2 ; i++){
            for(j = 0; j < Column + N - 1; j++){

                Imagedata_Expassion[i][j][k] = Imagedata_Expassion[N - 1 -i][j][k];
            }
        }

        for (i = (N - 1)/2 + Row; i < N - 1 + Row; i++){
            for(j = 0; j < Column + N - 1; j++){

                Imagedata_Expassion[i][j][k] = Imagedata_Expassion[N - 3 + 2 * Row - i][j][k];
            }
        }
    }



    cout << "Fill the expended row succeed!" <<endl;



    //convolution by uniform filter
    cout << "2. convolution by non_local_mean filter" <<endl;

    unsigned char Imagedata_compute_non_local_mean[Row][Column][BytesPerPixel];
    float middle = 0.0;
    float h = 100;
    float w;
    float w_sum = 0.0;
    float temp = 0.0;
    int M1 = 2;
    int M2 = 2;
    int n1 = 0;
    int n2 = 0;
    float a = 1;


    for (ch = 0;ch < BytesPerPixel; ch++){
        for (i = (N - 1)/2; i < Row + (N - 1)/2; i++){
            for(j = (N - 1)/2; j < Column + (N - 1)/2; j++){

                float f_sum = 0.0;
                float I_f_sum = 0.0;
                for(k = max(i - M1,(N - 1)/2); k <= min(i + M1,Row + (N - 1)/2 - 1); k++){
                    for(l = max(j - M2,(N - 1)/2); l <= min(j + M2,Column + (N - 1)/2 - 1); l++){
                        float gaussian_distance = 0.0;
                        for (n1 = - (N - 1)/2; n1 <= (N - 1)/2; n1++){
                            for(n2 = - (N - 1)/2; n2 <= (N - 1)/2; n2++){

                                float gaussian_parameter = exp(- (n1*n1 + n2*n2)/(2*a*a)) / (sqrt(2 * M_PI) * a);
                                gaussian_distance += gaussian_parameter * pow(Imagedata_Expassion[i + n1][j + n2][ch] - Imagedata_Expassion[k + n1][l + n2][ch],2);

                            }
                        }

                        float f = exp( - gaussian_distance / (h*h));
                        f_sum += f;
                        I_f_sum += Imagedata_Expassion[k][l][ch] * f;

                    }
                }

                Imagedata_compute_non_local_mean[i - (N - 1)/2][j - (N - 1)/2][ch] = (int)I_f_sum / f_sum;

            }
        }
    }





    //3. Caculate PSNR

    // compute mse
    int temp1 = 0;
    double mse1 = 0;
    double psnr1 = 0;
    int temp2 = 0;
    double mse2 = 0;
    double psnr2 = 0;



    for(ch = 0; ch < BytesPerPixel; ch++){
        for(i = 0; i < Row; i++){
            for (j = 0; j < Column; j++){
                temp1 = (int)Imagedata[i][j][ch] - (int)Imagedata_ori[i][j][ch];
                mse1 = mse1 + (unsigned int)(temp1 * temp1);

                temp2 = (int)Imagedata_compute_non_local_mean[i][j][ch] - (int)Imagedata_ori[i][j][ch];
                mse2 = mse2 + (unsigned int)(temp2 * temp2);

            }
        }
    }

    mse1 = mse1 / (Row * Column * BytesPerPixel);
    mse2 = mse2 / (Row * Column * BytesPerPixel);

    psnr1 = 10 * log10(255.0 * 255.0 / mse1);
    psnr2 = 10 * log10(255.0 * 255.0 / mse2);


    cout << "psnr of noise image is :" << psnr1 <<endl;
    cout << "psnr of non_local_mean is :" << psnr2 <<endl;


    // //check the type of embedded noise by counting the frequency of 0-255
    // float frequency[256] = {0.0};

    // // count the frequency of intensities
    // int noise;
    // for (i = 0; i < Row; i++) {
    // 	for (j = 0;j < Column; j++) {
    // 		noise = Imagedata[i][j][0] - Imagedata_ori[i][j][0];

    // 		//cout<< noise << " ";
    // 		frequency[noise+100] += 1.0;
    // 	}
    // }

    // // functions for output array to be plot
    // FILE *data_f = fopen("noise_distribution.txt", "w");
    // if (data_f == NULL)
    // {
    // 	printf("Error opening file!\n");
    // 	exit(1);
    // }
    // for (i = 0;i < 256; i++) {
    // 	fprintf(data_f, "%f\n", frequency[i] / (Row * Column));
    // }
    // fclose(data_f);


    ////////////////////////// END CODE ////////////////////////////////////////////////


    // Write image data (filename specified by second argument) from image data matrix

    if (!(file=fopen(argv[3],"wb"))) {
        cout << "Cannot open file: " << argv[3] << endl;
        exit(1);
    }
    fwrite(Imagedata_compute_non_local_mean, sizeof(unsigned char), Row*Column*BytesPerPixel, file);
    fclose(file);

    return 0;
}
