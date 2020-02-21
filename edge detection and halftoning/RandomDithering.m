function G = RandomDithering(matrix, row, col)
    for i = 1 : row
        for j = 1 : col
            rand = randi([0 255]);
            if matrix(i, j) > rand
                G(i, j) = 255;
            else
                G(i, j) = 0;
            end
        end
    end
end