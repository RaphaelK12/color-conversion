#include <iostream>
#include <algorithm>  
using namespace std;

class RGB {
    public:
        float R = 0;
        float G = 0;
        float B = 0;
        void print(){
            cout << "RGB: (" << R << " , " << G << " , " << B << ")" << endl; 
        }
};

struct CMY {
    float C = 0;
    float M = 0;
    float Y = 0;
    void print(){
        cout << "CMY: (" << C << " , " << M << " , " << Y << ")" << endl; 
    }
};

struct HSL{
    float H = 0; // angle in degrees
    float S = 0;
    float L = 0;
    void print(){
        cout << "HSL: (" << H << " , " << S << " , " << L << ")" << endl; 
    }
};