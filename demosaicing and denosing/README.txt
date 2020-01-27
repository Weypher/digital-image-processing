# EE569 Homework Assignment #1
# Date: 01/28/2020
# Name: Wenbo Ye
# Email:  wenboye@usc.edu
#
# Compiled on Clion
#
# Define compiler and linker in Makefile
# Coding in C++11

# 1. Usage for compiling, linking and runing

# Compile, link and default run:

make

# Clean compiling files:

make clean


# 2. File list and explanation
Bilinear.cpp: problem-1a-bilinear demosaicing
mhc.cpp: problem-1b-MHC demosaicing
Histogram1.cpp: porblem-1c-histogram manipulation-methodA
Histogram2.cpp: porblem-1c-histogram manipulation-methodB
denosing_Uni.cpp: problem-2a-uniform weight function
denosing_Gas.cpp: problem-2a-gaussian weight function
denosing_Bilateral.cpp: problem-2b-bilateral filtering
Nlm.cpp: problem-2c-NLM-filtering // source:https://github.com/Maud1023/Digital_Image_Processing/blob/master/hw1/code/nl_mean.cpp
BM3D: problem-2d-BM3D //source: https://github.com/jiazhi412/Digital-image-processing/tree/master/Homework1/EE569_hw1_5715388761_Li/Other%20MATLAB%20code/Shot%20noise_BM3D

# 3. How to run the specific file:
Step1: make sure the "image" file has original images and "result" file is empty
Step2: compile the .cpp code by using the command "make"
Step3: use command "make bilinear" to run the first problem code
Step4: use command "make Mac" to run the second problem code
.
.
.
StepN: use command "make (program name)" to run the code.

Results of PSNR are all produced on command board and images are in the "result" file.


BM3D: 
Step1: add "BM3D" path into library.
step2: use MATLAB to run the main.m



