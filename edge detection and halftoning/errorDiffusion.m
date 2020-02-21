function b = errorDiffusion(I, row, col, DM, size)
    direction = 1;
    j = 0;
    Image = double(I);
    ts = 127;
    DMSize = (size + 1) / 2;
    b = zeros(row, col);
    for i = 1 : row
        j = j + direction;
        while (j > 0 && j <= col)
            if Image(i, j) < ts
%                 error = G(i, j);
%                 G(i, j) = 0;
                b(i, j) = 0;
            else
%                 error = G(i, j) - 255;
%                 G(i, j) = 255;
                b(i, j) = 255;
            end
            error = Image(i, j) - b(i, j);
            for n = 0 : DMSize - 1
                for m = -(DMSize - 1) : (DMSize - 1)
                    if (DM(n + 1, DMSize + m) ~= 0) && ((m + j) >= 1) && ((j + m) <= col) && ((i + n) <= row)
                        Image(i + n, j + m) = Image(i + n, j + m) + error * DM(n+1, m+DMSize);
                    end
                end
            end
            j = j + direction;
        end
        direction = -direction;
    end
                
end