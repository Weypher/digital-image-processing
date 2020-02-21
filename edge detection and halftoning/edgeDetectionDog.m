%EE569 Homework Assignment #2
%Date: 02/15/2020
%Name: Wenbo Ye
%Email:  wenboye@usc.edu
%uscid: 3963437994
col = 481;
row = 321;

oriRGB = readraw('./EE569_Spring_2020_HW2_Materials/Problem1/Dogs.raw', row, col, 3);

gray = rgbToGray(oriRGB, row, col);
fixedBound = edgeFix(gray, row, col);
sobelX = sobelGx(fixedBound, row, col);
sobelY = sobelGy(fixedBound, row, col);

magn = mag(sobelX, sobelY, row, col);
ts = threshold(magn, row, col, 30);


x = uint8(sobelX);
y = uint8(sobelY);
res = uint8(ts);


intGray = uint8(gray);
BW = edge(intGray, 'canny', [0.16 0.4]);


figure();
imshow(x);
filename_save = "./result/dog_sobelX.raw";
count = writeraw(x, filename_save);

figure();
imshow(y);
filename_save = "./result/dog_sobelY.raw";
count = writeraw(y, filename_save);

figure();
imshow(res);
filename_save = "./result/dog_res.raw";
count = writeraw(res, filename_save);

figure();
imshow(BW);
filename_save = "./result/dog_canny.raw";
count = writeraw(BW, filename_save);

k = edge(intGray, 'canny', [0.2 0.4]);
figure();
imshow(k);
