function G = rgb2cmy(I, row, col, channel)
    for i = 1 : row
        for j = 1 : col
            for k = 1 : channel
                G(i, j ,k) = 255 - I(i, j, k);
            end
        end
    end
end