function G = fixedDithering(matrix, row, col, ts)
    for i = 1 : row
        for j = 1 : col
            if matrix(i, j) > ts
                G(i, j) = 255;
            else
                G(i, j) = 0;
            end
        end
    end
end