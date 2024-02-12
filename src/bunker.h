#pragma once

#include "SDL3/SDL.h"
#include <vector>

std::vector<SDL_FRect> getBunkerRects(int x, int y, float size)
{
    // top
    std::vector<SDL_FRect> bunker;
    SDL_FRect rect;

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 16 + (j * 2); i++)
        {
            rect = {(x - size * j) + size * i, y + size * (j + 1), size, size};
            bunker.push_back(rect);
        }
    }

    // middle
    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i < 24; i++)
        {
            rect = {(x - size * 4) + size * i, y + size * (j + 6), size, size};
            bunker.push_back(rect);
        }
    }

    // bottom
    for (int i = 0; i < 24; i++)
    {
        if (i < 7 || i > 16)
        {
            rect = {(x - size * 4) + size * i, y + size * 11, size, size};
            bunker.push_back(rect);
        }
        if (i < 6 || i > 17)
        {
            rect = {(x - size * 4) + size * i, y + size * 12, size, size};
            bunker.push_back(rect);
        }
        if (i < 5 || i > 18)
        {
            rect = {(x - size * 4) + size * i, y + size * 13, size, size};
            bunker.push_back(rect);
        }
        if (i < 5 || i > 18)
        {
            rect = {(x - size * 4) + size * i, y + size * 14, size, size};
            bunker.push_back(rect);
        }
    }
    return bunker;
}

void fragments(std::vector<SDL_FRect>& bunker, std::vector<std::vector<SDL_FRect>>& frag)
{
    frag[0].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[0].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[0].push_back(bunker[14]); bunker.erase(bunker.begin() + 14); 
    frag[0].push_back(bunker[14]); bunker.erase(bunker.begin() + 14); 
    frag[0].push_back(bunker[14]); bunker.erase(bunker.begin() + 14); 
    frag[0].push_back(bunker[31]); bunker.erase(bunker.begin() + 31); 
    frag[0].push_back(bunker[30]); bunker.erase(bunker.begin() + 30); 
    frag[0].push_back(bunker[29]); bunker.erase(bunker.begin() + 29); 
    frag[0].push_back(bunker[47]); bunker.erase(bunker.begin() + 47); 
    frag[0].push_back(bunker[46]); bunker.erase(bunker.begin() + 46); 
    frag[0].push_back(bunker[67]); bunker.erase(bunker.begin() + 67); 
    frag[0].push_back(bunker[66]); bunker.erase(bunker.begin() + 66); 
    frag[1].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[1].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[1].push_back(bunker[28]); bunker.erase(bunker.begin() + 28); 
    frag[1].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[1].push_back(bunker[27]); bunker.erase(bunker.begin() + 27); 
    frag[1].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[1].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[1].push_back(bunker[11]); bunker.erase(bunker.begin() + 11); 
    frag[1].push_back(bunker[11]); bunker.erase(bunker.begin() + 11); 
    frag[1].push_back(bunker[23]); bunker.erase(bunker.begin() + 23); 
    frag[1].push_back(bunker[23]); bunker.erase(bunker.begin() + 23); 
    frag[1].push_back(bunker[40]); bunker.erase(bunker.begin() + 40); 
    frag[1].push_back(bunker[40]); bunker.erase(bunker.begin() + 40); 
    frag[2].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[2].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[2].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[2].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[2].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[2].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[2].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[2].push_back(bunker[16]); bunker.erase(bunker.begin() + 16); 
    frag[2].push_back(bunker[16]); bunker.erase(bunker.begin() + 16); 
    frag[2].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[2].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[2].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[3].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[3].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[3].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[3].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[3].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[3].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[3].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[3].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[3].push_back(bunker[10]); bunker.erase(bunker.begin() + 10); 
    frag[3].push_back(bunker[10]); bunker.erase(bunker.begin() + 10); 
    frag[3].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[4].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[4].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[4].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[4].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[4].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[4].push_back(bunker[22]); bunker.erase(bunker.begin() + 22); 
    frag[4].push_back(bunker[22]); bunker.erase(bunker.begin() + 22); 
    frag[4].push_back(bunker[22]); bunker.erase(bunker.begin() + 22); 
    frag[4].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[4].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[4].push_back(bunker[65]); bunker.erase(bunker.begin() + 65); 
    frag[5].push_back(bunker[64]); bunker.erase(bunker.begin() + 64); 
    frag[5].push_back(bunker[63]); bunker.erase(bunker.begin() + 63); 
    frag[5].push_back(bunker[62]); bunker.erase(bunker.begin() + 62); 
    frag[5].push_back(bunker[39]); bunker.erase(bunker.begin() + 39); 
    frag[5].push_back(bunker[38]); bunker.erase(bunker.begin() + 38); 
    frag[5].push_back(bunker[20]); bunker.erase(bunker.begin() + 20); 
    frag[5].push_back(bunker[19]); bunker.erase(bunker.begin() + 19); 
    frag[5].push_back(bunker[18]); bunker.erase(bunker.begin() + 18); 
    frag[5].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[5].push_back(bunker[16]); bunker.erase(bunker.begin() + 16); 
    frag[5].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[5].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[5].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[5].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[5].push_back(bunker[30]); bunker.erase(bunker.begin() + 30); 
    frag[5].push_back(bunker[29]); bunker.erase(bunker.begin() + 29); 
    frag[6].push_back(bunker[28]); bunker.erase(bunker.begin() + 28); 
    frag[6].push_back(bunker[27]); bunker.erase(bunker.begin() + 27); 
    frag[6].push_back(bunker[26]); bunker.erase(bunker.begin() + 26); 
    frag[6].push_back(bunker[25]); bunker.erase(bunker.begin() + 25); 
    frag[6].push_back(bunker[24]); bunker.erase(bunker.begin() + 24); 
    frag[6].push_back(bunker[11]); bunker.erase(bunker.begin() + 11); 
    frag[6].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[6].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[6].push_back(bunker[9]); bunker.erase(bunker.begin() + 9); 
    frag[6].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[7].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[7].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[7].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[7].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[7].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[7].push_back(bunker[13]); bunker.erase(bunker.begin() + 13); 
    frag[7].push_back(bunker[26]); bunker.erase(bunker.begin() + 26); 
    frag[7].push_back(bunker[26]); bunker.erase(bunker.begin() + 26); 
    frag[7].push_back(bunker[45]); bunker.erase(bunker.begin() + 45); 
    frag[7].push_back(bunker[26]); bunker.erase(bunker.begin() + 26); 
    frag[7].push_back(bunker[44]); bunker.erase(bunker.begin() + 44); 
    frag[7].push_back(bunker[67]); bunker.erase(bunker.begin() + 67); 
    frag[8].push_back(bunker[44]); bunker.erase(bunker.begin() + 44); 
    frag[8].push_back(bunker[66]); bunker.erase(bunker.begin() + 66); 
    frag[8].push_back(bunker[44]); bunker.erase(bunker.begin() + 44); 
    frag[8].push_back(bunker[27]); bunker.erase(bunker.begin() + 27); 
    frag[8].push_back(bunker[27]); bunker.erase(bunker.begin() + 27); 
    frag[8].push_back(bunker[27]); bunker.erase(bunker.begin() + 27); 
    frag[8].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[8].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[8].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[8].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[8].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[8].push_back(bunker[26]); bunker.erase(bunker.begin() + 26); 
    frag[9].push_back(bunker[40]); bunker.erase(bunker.begin() + 40); 
    frag[9].push_back(bunker[58]); bunker.erase(bunker.begin() + 58); 
    frag[9].push_back(bunker[58]); bunker.erase(bunker.begin() + 58); 
    frag[9].push_back(bunker[58]); bunker.erase(bunker.begin() + 58); 
    frag[9].push_back(bunker[81]); bunker.erase(bunker.begin() + 81); 
    frag[9].push_back(bunker[81]); bunker.erase(bunker.begin() + 81); 
    frag[9].push_back(bunker[58]); bunker.erase(bunker.begin() + 58); 
    frag[10].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[10].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[10].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[10].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[10].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[10].push_back(bunker[9]); bunker.erase(bunker.begin() + 9); 
    frag[10].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[10].push_back(bunker[19]); bunker.erase(bunker.begin() + 19); 
    frag[11].push_back(bunker[32]); bunker.erase(bunker.begin() + 32); 
    frag[11].push_back(bunker[19]); bunker.erase(bunker.begin() + 19); 
    frag[11].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[11].push_back(bunker[18]); bunker.erase(bunker.begin() + 18); 
    frag[11].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[11].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[11].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[11].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[11].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[11].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[11].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[11].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[11].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[11].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[12].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[12].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[12].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[12].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[12].push_back(bunker[20]); bunker.erase(bunker.begin() + 20); 
    frag[12].push_back(bunker[19]); bunker.erase(bunker.begin() + 19); 
    frag[12].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[12].push_back(bunker[17]); bunker.erase(bunker.begin() + 17); 
    frag[12].push_back(bunker[16]); bunker.erase(bunker.begin() + 16); 
    frag[12].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[13].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[13].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[13].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[13].push_back(bunker[12]); bunker.erase(bunker.begin() + 12); 
    frag[13].push_back(bunker[12]); bunker.erase(bunker.begin() + 12); 
    frag[13].push_back(bunker[12]); bunker.erase(bunker.begin() + 12); 
    frag[13].push_back(bunker[28]); bunker.erase(bunker.begin() + 28); 
    frag[13].push_back(bunker[28]); bunker.erase(bunker.begin() + 28); 
    frag[13].push_back(bunker[49]); bunker.erase(bunker.begin() + 49); 
    frag[14].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[14].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[14].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[14].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[14].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[14].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[14].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[14].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[14].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[15].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[15].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[15].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[15].push_back(bunker[25]); bunker.erase(bunker.begin() + 25); 
    frag[15].push_back(bunker[25]); bunker.erase(bunker.begin() + 25); 
    frag[15].push_back(bunker[45]); bunker.erase(bunker.begin() + 45); 
    frag[15].push_back(bunker[25]); bunker.erase(bunker.begin() + 25); 
    frag[15].push_back(bunker[44]); bunker.erase(bunker.begin() + 44); 
    frag[15].push_back(bunker[44]); bunker.erase(bunker.begin() + 44); 
    frag[15].push_back(bunker[44]); bunker.erase(bunker.begin() + 44); 
    frag[15].push_back(bunker[82]); bunker.erase(bunker.begin() + 82); 
    frag[15].push_back(bunker[85]); bunker.erase(bunker.begin() + 85); 
    frag[15].push_back(bunker[85]); bunker.erase(bunker.begin() + 85); 
    frag[16].push_back(bunker[82]); bunker.erase(bunker.begin() + 82); 
    frag[16].push_back(bunker[79]); bunker.erase(bunker.begin() + 79); 
    frag[16].push_back(bunker[75]); bunker.erase(bunker.begin() + 75); 
    frag[16].push_back(bunker[71]); bunker.erase(bunker.begin() + 71); 
    frag[16].push_back(bunker[70]); bunker.erase(bunker.begin() + 70); 
    frag[16].push_back(bunker[72]); bunker.erase(bunker.begin() + 72); 
    frag[16].push_back(bunker[43]); bunker.erase(bunker.begin() + 43); 
    frag[16].push_back(bunker[42]); bunker.erase(bunker.begin() + 42); 
    frag[16].push_back(bunker[24]); bunker.erase(bunker.begin() + 24); 
    frag[16].push_back(bunker[23]); bunker.erase(bunker.begin() + 23); 
    frag[16].push_back(bunker[22]); bunker.erase(bunker.begin() + 22); 
    frag[17].push_back(bunker[69]); bunker.erase(bunker.begin() + 69); 
    frag[17].push_back(bunker[69]); bunker.erase(bunker.begin() + 69); 
    frag[17].push_back(bunker[70]); bunker.erase(bunker.begin() + 70); 
    frag[17].push_back(bunker[70]); bunker.erase(bunker.begin() + 70); 
    frag[17].push_back(bunker[70]); bunker.erase(bunker.begin() + 70); 
    frag[17].push_back(bunker[70]); bunker.erase(bunker.begin() + 70); 
    frag[18].push_back(bunker[69]); bunker.erase(bunker.begin() + 69); 
    frag[18].push_back(bunker[68]); bunker.erase(bunker.begin() + 68); 
    frag[18].push_back(bunker[67]); bunker.erase(bunker.begin() + 67); 
    frag[18].push_back(bunker[65]); bunker.erase(bunker.begin() + 65); 
    frag[18].push_back(bunker[65]); bunker.erase(bunker.begin() + 65); 
    frag[18].push_back(bunker[64]); bunker.erase(bunker.begin() + 64); 
    frag[18].push_back(bunker[63]); bunker.erase(bunker.begin() + 63); 
    frag[19].push_back(bunker[62]); bunker.erase(bunker.begin() + 62); 
    frag[19].push_back(bunker[37]); bunker.erase(bunker.begin() + 37); 
    frag[19].push_back(bunker[37]); bunker.erase(bunker.begin() + 37); 
    frag[19].push_back(bunker[36]); bunker.erase(bunker.begin() + 36); 
    frag[19].push_back(bunker[21]); bunker.erase(bunker.begin() + 21); 
    frag[19].push_back(bunker[20]); bunker.erase(bunker.begin() + 20); 
    frag[19].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[19].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[19].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[20].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[20].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[20].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[20].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[20].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[20].push_back(bunker[12]); bunker.erase(bunker.begin() + 12); 
    frag[20].push_back(bunker[12]); bunker.erase(bunker.begin() + 12); 
    frag[20].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[20].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[20].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[21].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[21].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[21].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[21].push_back(bunker[11]); bunker.erase(bunker.begin() + 11); 
    frag[21].push_back(bunker[11]); bunker.erase(bunker.begin() + 11); 
    frag[22].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[22].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[22].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[22].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[22].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[22].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[22].push_back(bunker[9]); bunker.erase(bunker.begin() + 9); 
    frag[23].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[23].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[23].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[23].push_back(bunker[5]); bunker.erase(bunker.begin() + 5); 
    frag[24].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[24].push_back(bunker[26]); bunker.erase(bunker.begin() + 26); 
    frag[24].push_back(bunker[24]); bunker.erase(bunker.begin() + 24); 
    frag[24].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[24].push_back(bunker[2]); bunker.erase(bunker.begin() + 2); 
    frag[24].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[25].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[25].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[25].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[25].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[25].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[25].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[25].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[26].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[26].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[26].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[26].push_back(bunker[9]); bunker.erase(bunker.begin() + 9); 
    frag[26].push_back(bunker[8]); bunker.erase(bunker.begin() + 8); 
    frag[26].push_back(bunker[7]); bunker.erase(bunker.begin() + 7); 
    frag[26].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[26].push_back(bunker[4]); bunker.erase(bunker.begin() + 4); 
    frag[26].push_back(bunker[6]); bunker.erase(bunker.begin() + 6); 
    frag[27].push_back(bunker[3]); bunker.erase(bunker.begin() + 3); 
    frag[27].push_back(bunker[1]); bunker.erase(bunker.begin() + 1); 
    frag[27].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[27].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[27].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
    frag[27].push_back(bunker[0]); bunker.erase(bunker.begin() + 0); 
}