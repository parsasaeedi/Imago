#ifndef LAB_INTRO_H
#define LAB_INTRO_H

#include "cs221util/PNG.h"
using namespace cs221util;

// PNG edit(PNG image, int exposure, int highlights, int shadows, )

PNG adjustLuminance(PNG image, int adjustBy);
PNG adjustSaturation(PNG image, int adjustBy);
PNG adjustHue(PNG image, int adjustBy);
PNG adjustHighlights(PNG image, int adjustBy);
PNG adjustShadows(PNG image, int adjustBy);
PNG addVignette(PNG image, int vignetteStrength);
PNG adjustAll(PNG image, int luminance, int saturation, int hue, int highlights, int shadows, int vignette);
void adjustColumn(PNG* image, int column, int luminance, int saturation, int hue, int highlights, int shadows, int vignette);

#endif
