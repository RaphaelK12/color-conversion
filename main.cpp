#include "colors.h"

CMY RGBToCMY(RGB rgb)
{
    CMY cmy;
    cmy.C = 1.0f - (rgb.R);
    cmy.M = 1.0f - (rgb.G);
    cmy.Y = 1.0f - (rgb.B);
    return cmy;
}

RGB CMYtoRGB(CMY cmy){
    RGB rgb;
    rgb.R = 1.0f - (cmy.C);
    rgb.G = 1.0f - (cmy.M);
    rgb.B = 1.0f - (cmy.Y);
    return rgb;
}

HSL RGBtoHSL(RGB rgb){
    HSL hsl;
    // find the max and min values for R,G,B
    float rgbMax = max({rgb.R,rgb.G,rgb.B});
    float rgbMin = min({rgb.R,rgb.G,rgb.B});

    // calculate Lightness
    hsl.L = 50 * (rgbMax + rgbMin);
    
    if(rgbMin == rgbMax){
        return hsl;
    }else if (hsl.L < 50)
    {
        hsl.S = 100 * (rgbMax - rgbMin) / (rgbMax + rgbMin);
    }
    else
    {
        hsl.S = 100 * (rgbMax - rgbMin) / (2.0 - rgbMax - rgbMin);
    }

    if (rgbMax == rgb.R)
    {
        hsl.H = 60 * (rgb.G - rgb.B) / (rgbMax - rgbMin);
    }
    if (rgbMax == rgb.G)
    {
        hsl.H = 60 * (rgb.B - rgb.R) / (rgbMax - rgbMin) + 120;
    }
    if (rgbMax == rgb.B)
    {
        hsl.H = 60 * (rgb.R - rgb.G) / (rgbMax - rgbMin) + 240;
    }
    if (hsl.H < 0)
    {
        hsl.H = hsl.H + 360;
    }
    return hsl;
}

RGB HSLtoRGB(HSL hsl){
    RGB rgb;
    return rgb;
}


int main() {
    RGB rgb = {1, 0, 0};
    rgb.print();
    CMY cmy = RGBToCMY(rgb);
    cmy.print();
    HSL hsl = RGBtoHSL(rgb);
    hsl.print();
}