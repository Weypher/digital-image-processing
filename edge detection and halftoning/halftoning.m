%EE569 Homework Assignment #2
%Date: 02/15/2020
%Name: Wenbo Ye
%Email:  wenboye@usc.edu
%uscid: 3963437994
row = 500;
col = 750;
oriPic = readraw('./EE569_Spring_2020_HW2_Materials/Problem2/LightHouse.raw', row, col, 1);
intPic = doubleToInt(oriPic, row, col, 1);

%%Fixed thresholding
fixDitherPic = fixedDithering(intPic, row, col, 128);
% figure();
% imshow(fixDitherPic);
filename_save = "./result/fixedDithering_res.raw";
count = writeraw(fixDitherPic, filename_save);

%%Random thresholding
ranDitherPic = RandomDithering(intPic, row, col);
% figure();
% imshow(ranDitherPic);
filename_save = "./result/randomDithering_res.raw";
count = writeraw(ranDitherPic, filename_save);

%%Dithering Matrix
ditheringMatrixPic2 = ditheringMatrix(intPic, row, col, 2);
ditheringMatrixPic8 = ditheringMatrix(intPic, row, col, 8);
ditheringMatrixPic32 = ditheringMatrix(intPic, row, col, 32);
% figure();
% imshow(ditheringMatrixPic2);
% figure();
% imshow(ditheringMatrixPic8);
% figure();
% imshow(ditheringMatrixPic32);
filename_save = "./result/ditheringMatrixPic2.raw";
count = writeraw(ditheringMatrixPic2, filename_save);
filename_save = "./result/ditheringMatrixPic8.raw";
count = writeraw(ditheringMatrixPic8, filename_save);
filename_save = "./result/ditheringMatrixPic32.raw";
count = writeraw(ditheringMatrixPic32, filename_save);

%%Error Diffusion
Floyd = [0,0,7;3,5,1]/16;
JJN=[0,0,0,7,5;3,5,7,5,3;1,3,5,3,1]/48;
Stucki=[0,0,0,8,4;2,4,8,4,2;1,2,4,2,1]/42;
errorDiffusion1 = errorDiffusion(intPic, row, col, Floyd, 3);
errorDiffusion2 = errorDiffusion(intPic, row, col, JJN, 5);
errorDiffusion3 = errorDiffusion(intPic, row, col, Stucki, 5);
figure();
imshow(errorDiffusion1);
figure();
imshow(errorDiffusion2);
figure();
imshow(errorDiffusion3);
filename_save = "./result/errorDiffusionFloyd.raw";
count = writeraw(errorDiffusion1, filename_save);
filename_save = "./result/errorDiffusionJJN.raw";
count = writeraw(errorDiffusion2, filename_save);
filename_save = "./result/errorDiffusionStucki.raw";
count = writeraw(errorDiffusion3, filename_save);

%%Color Half-toning with Error Diffusion
%Separable Error Diffusion
roseRow = 480;
roseCol = 640;
rosergb = readraw('./EE569_Spring_2020_HW2_Materials/Problem2/Rose.raw', roseRow, roseCol, 3);
intRoseRgb = doubleToInt(rosergb, roseRow, roseCol, 3);
rose_cmy = rgb2cmy(intRoseRgb, roseRow, roseCol, 3);
[I1, I2, I3] = rgbSeperate(intRoseRgb, roseRow, roseCol);
errorDiffusionI1 = errorDiffusion(I1, roseRow, roseCol, Floyd, 3);
errorDiffusionI2 = errorDiffusion(I2, roseRow, roseCol, Floyd, 3);
errorDiffusionI3 = errorDiffusion(I3, roseRow, roseCol, Floyd, 3);
rose_cmy_diffusion = mergeRGB(errorDiffusionI1, errorDiffusionI2, errorDiffusionI3, roseRow, roseCol);
figure();
imshow(uint8(rose_cmy_diffusion));
rose_rgb_ed = rgb2cmy(rose_cmy_diffusion, roseRow, roseCol, 3);
rose_res_ed = uint8(rose_rgb_ed)
figure();
imshow(rose_res_ed);
filename_save = "./result/rose_error_diffusion.raw";
count = writerawRGB(rose_res_ed, filename_save);

%MBVQ
rose_MBVQ = MBVQ(intRoseRgb, roseRow, roseCol, Floyd, 3);
[test1, test2, test3] = rgbSeperate(rose_MBVQ, roseRow, roseCol);
figure();
imshow(rose_MBVQ);
filename_save = "./result/rose_MBVQ.raw";
count = writerawRGB(rose_MBVQ, filename_save);