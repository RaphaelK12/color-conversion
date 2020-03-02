#include "colors.h"

CMY RGBToCMY(RGB rgb){
    CMY cmy;
    // invert the colors
    cmy.C = 1.0f - (rgb.R);
    cmy.M = 1.0f - (rgb.G);
    cmy.Y = 1.0f - (rgb.B);
    return cmy;
}

RGB CMYtoRGB(CMY cmy){
    RGB rgb;
    // invert the colors
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
    RGB rgb;
    float temp1, temp2, tempr, tempg, tempb;
    
    float h = hsl.H / 360.0;  // scale hue to 0.0 - 1.0
    float s = hsl.S;  // saturation 
    float l = hsl.L;  // lightness

    // 0% means a shade of gray
    if(s == 0){
    	rgb.R = rgb.G = rgb.B = l;
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
            rgb.R = temp1 + (temp2 - temp1) * 6.0 * tempr;
        }else if (2.0 * tempr < 1.0){
            rgb.R = temp2;
        }else if (3.0 * tempr < 2.0){
            rgb.R = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempr) * 6.0;
        }else{
            rgb.R = temp1;
        }

        // Calculate green value       
        if (6.0 * tempg < 1.0){
            rgb.G =temp1 + (temp2 - temp1) * 6.0 * tempg;
        }else if (2.0 * tempg < 1.0){
            rgb.G =temp2;
        }else if (3.0 * tempg < 2.0){
            rgb.G =temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempg) * 6.0;
        }else{
            rgb.G =temp1; 
        }

        // Calculate blue value    
        if (6.0 * tempb < 1.0){
            rgb.B = temp1 + (temp2 - temp1) * 6.0 * tempb;
        }else if (2.0 * tempb < 1.0){
            rgb.B = temp2;
        }else if (3.0 * tempr < 2.0){
            rgb.B = temp1 + (temp2 - temp1) * ((2.0 / 3.0) - tempb) * 6.0;
        }else{
            rgb.G = temp1; 
        }
    }

    return rgb;
}

RGB transparency(RGB rgb1, float alpha, RGB rgb2){
    RGB return_rgb;

    return_rgb.R = (1 - alpha) * rgb2.R + alpha * rgb1.R;
    return_rgb.G = (1 - alpha) * rgb2.G + alpha * rgb1.G;
    return_rgb.B = (1 - alpha) * rgb2.B + alpha * rgb1.B;
    
    return return_rgb;
}

int main() {
    RGB redRGB = {0, 1, 1};
    CMY redCMY = RGBToCMY(redRGB);
    
    redRGB.print();
    cout << " = " ;
    redCMY.print(); 
    cout << endl;

    HSL redHSL = RGBtoHSL(redRGB);

    redRGB.print();
    cout << " = " ;
    redHSL.print();
    cout << endl;

    HSL lblueHSL = {180,0.75,0.5};
    RGB lblueRGB1 = HSLtoRGB(lblueHSL);

    lblueHSL.print();
    cout << " = " ;
    lblueRGB1.print();
    cout << endl;

    CMY lblueCMY = {1,0,0};
    RGB lblueRGB2 = CMYtoRGB(lblueCMY);

    lblueCMY.print();
    cout << " = " ;
    lblueRGB2.print();
    cout << endl;

    RGB rgb1 = {1,0,0};
    float alpha = 0.5;
    
    RGB rgb2 = {0,1,0};

    RGB rgbTransparent = transparency(rgb1, alpha, rgb2);

    cout << "RGB Transparent: ";
    rgbTransparent.print();
    cout << endl;
}