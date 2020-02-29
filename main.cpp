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

    // calculate lightness
    hsl.L = 50 * (rgbMax + rgbMin);
    
    // calculate saturation 
    if(rgbMin == rgbMax){
        return hsl;
    }else if (hsl.L < 50){
        hsl.S = 100 * (rgbMax - rgbMin) / (rgbMax + rgbMin);
    }else{
        hsl.S = 100 * (rgbMax - rgbMin) / (2.0 - rgbMax - rgbMin);
    }
    
    // calculate hue
    if (rgbMax == rgb.R){
        hsl.H = 60 * (rgb.G - rgb.B) / (rgbMax - rgbMin);
    }
    if (rgbMax == rgb.G){
        hsl.H = 60 * (rgb.B - rgb.R) / (rgbMax - rgbMin) + 120;
    }
    if (rgbMax == rgb.B){
        hsl.H = 60 * (rgb.R - rgb.G) / (rgbMax - rgbMin) + 240;
    }
    if (hsl.H < 0){
        hsl.H = hsl.H + 360;
    }
    return hsl;
}

RGB HSLtoRGB(HSL hsl){
    float r, g, b, h, s, l;
    float temp1, temp2, tempr, tempg, tempb;
    
    //Scale each value to 0.0 - 1.0
    h = hsl.H / 360.0;  //Hue is represented as a range of 360 degrees
    s = hsl.S;  //Saturation 
    l = hsl.L;  //Lightness

    if(s == 0){
    	r = g = b = l;
    }else{
        if (l < 0.5){
            temp2 = l * (1.0 + s);
        }else{
            temp2 = (l + s) - (l * s);
        }

        temp1 = 2.0 * l - temp2;
        tempr = h + 1.0 / 3.0;
        if (tempr > 1.0){
            tempr-= 1.0;
        }
        tempg = h;
        tempb = h - 1.0 / 3.0;
        if (tempb < 0){
            tempb += 1.0; 
        }
        
        // Calculate red value:     
        if (6.0 * tempr < 1.0){
            r = temp1 + (temp2 - temp1) * 6.0 * tempr;
        }else if (2.0 * tempr < 1.0){
            r = temp2;
        }else if (3.0 * tempr < 2.0){
            r = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
        }else{
            r = temp1;
        }

        // Calculate green value       
        if (6.0 * tempg < 1.0){
            g = temp1 + (temp2 - temp1) * 6.0 * tempg;
        }else if (2.0 * tempg < 1.0){
            g = temp2;
        }else if (3.0 * tempg < 2.0){
            g = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
        }else{
            g = temp1; 
        }

        // Calculate blue value    
        if (6.0 * tempb < 1.0){
            b = temp1 + (temp2 - temp1) * 6.0 * tempb;
        }else if (2.0 * tempb < 1.0){
            b = temp2;
        }else if (3.0 * tempr < 2.0){
            b = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
        }else{
            g = temp1; 
        }
    }

    RGB rgb = {r,g,b};
    return rgb;;
}

int main() {
    RGB redRGB = {0, 1, 1};
    redRGB.print();

    CMY redCMY = RGBToCMY(redRGB);
    redCMY.print();

    HSL redHSL = RGBtoHSL(redRGB);
    redHSL.print();

    HSL lblueHSL = {180,0.75,0.5};
    CMY lblueCMY = {1,0,0};

    RGB lblueRGB1 = HSLtoRGB(lblueHSL);
    lblueRGB1.print();

    RGB lblueRGB2 = CMYtoRGB(lblueCMY);
    lblueRGB2.print();
}