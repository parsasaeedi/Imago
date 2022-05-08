#include "HSLAPixel.h"

namespace cs221util {
    HSLAPixel::HSLAPixel() {
        h = 0.0;
        s = 0.0;
        l = 1.0;
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double sat, double lum) {
        h = hue;
        s = sat;
        l = lum;
        a = 1.0;
    }
    HSLAPixel::HSLAPixel(double hue, double sat, double lum, double alp) {
        h = hue;
        s = sat;
        l = lum;
        a = alp;
    }
}