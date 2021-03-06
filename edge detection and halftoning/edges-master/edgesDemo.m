% Demo for Structured Edge Detector (please see readme.txt first).

%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
model.opts.multiscale=0;          % for top accuracy set multiscale=1
model.opts.sharpen=2;             % for top speed set sharpen=0
model.opts.nTreesEval=4;          % for top speed set nTreesEval=1
model.opts.nThreads=4;            % max number threads for evaluation
model.opts.nms=1;                 % set to true to enable nms

%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, 'name','' ); end

%% detect edge and visualize results
I = imread('peppers.png');
I = imread('/Users/wenboye/Documents/ee569DIP/hw2/EE569_Spring_2020_HW2_Materials/Problem1/Gallery.jpg');
tic, E=edgesDetect(I,model); toc
figure(1); im(I);

image=1-E;
figure();
im(image);
T=0.88;
for i=1:321
    for j=1:481
        if image(i,j)< T
            img(i,j)=0;
        else
            img(i,j)=1;
        end
    end
end
figure();       
im(img);

figure(2); im(1-E);


% dog = load('/Users/wenboye/Documents/ee569DIP/hw2/EE569_Spring_2020_HW2_Materials/Problem1/Dogs_GT.mat');
% dog_gt = dog.groundTruth;
% 
% [thrs,cntR,sumR,cntP,sumP,V] = edgesEvalImg( E, '/Users/wenboye/Documents/ee569DIP/hw2/EE569_Spring_2020_HW2_Materials/Problem1/Dogs_GT.mat' );
