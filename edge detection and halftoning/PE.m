function [pre, recall, F, Fm] = PE(image, file)
%UNTITLED 此处显示有关此函数的摘要
%   此处显示详细说明
    pre = zeros(1, 5);
    recall = zeros(1, 5);
    F = zeros(1, 5);
    Fmax = zeros(1, 99);
    for i = 1 : 5
        [~,cntR,sumR,cntP,sumP,~] = edgesEvalImg(image, file, i);
        P = cntP./sumP;
        R = cntR./sumR;
        pre(i) = mean(P);
        recall(i) = mean(R);
        F(i) = 2 * (pre(i) * recall(i))/(pre(i) + recall(i));
        for j = 1 : 99
            temp = 2 * (P(j) * R(j))/(P(j) + R(j));
            Fmax(j) = max(Fmax(j), temp);
        end
    end
    Fm = max(Fmax);
end

