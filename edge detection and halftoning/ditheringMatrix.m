function G = ditheringMatrix(matrix, row, col, N)
    mul = log2(N);
    
    I = [1 2; 3 0];
    if mul > 1
       for i = 1 : mul - 1
          I = [(4*I+1) (4*I+2); (4*I+3) 4*I];
       end
    end
    T = (I + 0.5) * (255/(N ^ 2));

    for i = 1 : row
        for j = 1 : col
            if matrix(i, j) > T(mod(i, N)+1, mod(j, N)+1)
                G(i, j) = 255;
            else
                G(i, j) = 0;
            end
        end
    end
end