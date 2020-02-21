function G = rgbToGray(matrix, row, col)
    for i = 1 : row
        for j = 1 : col
            G(i, j) = matrix(i, j, 1) * 0.2989 + matrix(i, j, 2) * 0.5870 + matrix(i, j, 3) * 0.1140;
        end
    end
end