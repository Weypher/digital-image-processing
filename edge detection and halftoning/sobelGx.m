function G = sobelGx(matrix, row, col)

    max = 0;
    for i = 1 : row
        for j = 1 : col
            n = 1 + i;
            m = 1 + j;
            G(i, j) = 0 - matrix(n - 1, m - 1) + matrix(n - 1, m + 1)...
                       - 2 * matrix(n, m - 1) + 2 * matrix(n, m + 1)...
                       - matrix(n + 1, m - 1) + matrix(n + 1, m + 1);
            if G(i, j) < 0
                G(i, j) = - G(i, j);
            end
            if G(i, j) > max
                max = G(i, j);
            end
        end
    end
    
    for i = 1 : row
        for j = 1 : col
            G(i, j) = G(i, j) / max * 255;
        end
    end
end