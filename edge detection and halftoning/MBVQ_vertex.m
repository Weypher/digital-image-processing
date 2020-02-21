function G = MBVQ_vertex(name)
    if (strcmp(name, 'white'))
        G = [255,255,255];
    elseif (strcmp(name, 'yellow'))
        G = [255,255,0];
    elseif (strcmp(name, 'magenta'))
        G = [255, 0, 255];
    elseif (strcmp(name, 'cyan'))
        G = [0, 255, 255];
    elseif (strcmp(name, 'red'))
        G = [255, 0, 0];
    elseif (strcmp(name, 'green'))
        G = [0, 255, 0];
    elseif (strcmp(name, 'blue'))
        G = [0, 0, 255];
    elseif (strcmp(name, 'black'))
        G = [0, 0, 0];
%     else
%         G = [0, 0, 0];  
    end
end