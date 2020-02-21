function G = mag(sobelX, sobelY, row, col)
    max = 0;
    for i = 1 : row
        for j = 1 : col
            G(i, j) = sqrt(sobelX(i, j) * sobelX(i, j) + sobelY(i, j) * sobelY(i, j));
            if G(i, j) > max
                max = G(i, j)
            end
        end
    end
    for i = 1 : row
        for j = 1 : col
            G(i, j) = G(i, j) / max * 255;
        end
    end
end