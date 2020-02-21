function G = threshold(matrix, row, col, percent)
    ts = percent / 100 * 255;
    for i = 1 : row
        for j = 1 : col
            if matrix(i, j) > ts
                G(i, j) = 0;
            else
                G(i, j) = 255;
            end
        end
    end
end