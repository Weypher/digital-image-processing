function [G1, G2, G3] = rgbSeperate(I, row, col)
    for i = 1 : row
        for j = 1 : col
            G1(i, j) = I(i, j, 1);
            G2(i, j) = I(i, j, 2);
            G3(i, j) = I(i, j, 3);
        end
    end
end