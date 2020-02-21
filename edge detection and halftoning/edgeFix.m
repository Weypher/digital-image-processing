function G = edgeFix(matrix, row, col)
    for i = 1 : col
        G(1, i + 1) = matrix(1, i);
        G(2 + row, i + 1) = matrix(row, i);
    end
    for i = 2 : row + 1
        for j = 2 : col + 1
            G(i, j) = matrix(i - 1, j - 1);
        end
    end
    
    for i = 1 : row + 2
        G(i, 1) = G(i, 2);
        G(i, col + 2) = G(i, col + 1);
    end
end