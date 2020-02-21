function G = mergeRGB(I1, I2, I3, row, col)
    for i = 1 : row
        for j = 1 : col
            G(i, j, 1) = I1(i, j);
            G(i, j, 2) = I2(i, j);
            G(i, j, 3) = I3(i, j);
        end 
    end
end
