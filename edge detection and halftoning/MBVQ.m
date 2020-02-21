function Y = MBVQ(I, row, col, DM, size)
    I = double(I);
    direction = 1;
    j = 0;
    Y = double(I);
    error = zeros(row, col, size);
    DMSize = (size + 1) / 2;
    for i = 1 : row
        j = j + direction
        while (j > 0 && j <= col)
            R = I(i, j, 1);
            G = I(i, j, 2);
            B = I(i, j, 3);
            mode = MBVQ_selectMod(R, G, B);
            nearestVertex = getNearestVertex(mode, (R+error(i, j, 1)) / 255, (G+error(i, j, 2)) / 255, (B+error(i, j, 3)) / 255);
            vertex = MBVQ_vertex(nearestVertex);
            curError = [R + error(i,j,1) - vertex(1), G + error(i,j,2) - vertex(2), B + error(i,j,3) - vertex(3)];
            Y(i, j, 1) = vertex(1);
            Y(i, j, 2) = vertex(2);
            Y(i, j, 3) = vertex(3);
            x = 1;
            y = DMSize;
            for n = 0 : DMSize - 1
                for m = -(DMSize - 1) : (DMSize - 1)
                    if (DM(x + n, y + m) ~= 0) && ((m + j) >= 1) && ((j + m) <= col) && ((i + n) <= row)
                        error(i + n, j + m, 1) = error(i + n, j + m, 1) + curError(1) * DM(x + n, y + m * direction);
                        error(i + n, j + m, 2) = error(i + n, j + m, 2) + curError(2) * DM(x + n, y + m * direction);
                        error(i + n, j + m, 3) = error(i + n, j + m, 3) + curError(3) * DM(x + n, y + m * direction);
                    end
                end
            end
            j = j + direction;
        end
        direction = -direction;
    end
                
end