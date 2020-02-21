function count = writerawRGB(G, filename)
    G_shape=size(G);
    if length(G_shape)>2
        G=permute(G,[3,2,1]);
    else
        G=G';
    end
    fid = fopen(filename,'wb');
    if (fid == -1)
		error('can not open output image filem press CTRL-C to exit \n');
		pause;
    end
    count = fwrite(fid,G, 'uchar');
	fclose(fid);
end %function