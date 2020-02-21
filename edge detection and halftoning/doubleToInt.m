function G = doubleToInt(matrix, row, col, channel)
    for i = 1 : row
        for j = 1 : col
            for k = 1 : channel
                G(i, j, k) = uint8(matrix(i, j, k));
            end
        end
    end
end