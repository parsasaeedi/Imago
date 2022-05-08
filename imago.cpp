#include <iostream>
#include <cmath>
#include <cstdlib>

#include "cs221util/PNG.h"
#include "cs221util/HSLAPixel.h"
#include "imago.h"

using namespace cs221util;

/**
 * Returns an image with an adjusted luminance.
 * @return The adjusted image.
 */
PNG adjustLuminance(PNG image, int adjustBy) {
  if (!adjustBy) return image;
  double factor = 1 + adjustBy/100.0;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel->l = min(max(pixel->l*factor, 0.0), 1.0);
    }
  }
  return image;
}

/**
 * Returns an image with an adjusted saturation.
 * @return The adjusted image.
 */
PNG adjustSaturation(PNG image, int adjustBy) {
  if (!adjustBy) return image;
  double factor = 1 + adjustBy/100.0;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel->s = min(max(pixel->s*factor, 0.0), 1.0);
    }
  }
  return image;
}

/**
 * Returns an image with an adjusted hue.
 * @return The adjusted image.
 */
PNG adjustHue(PNG image, int adjustBy) {
  if (!adjustBy) return image;
  double factor = 1 + adjustBy/100.0;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      pixel->h = fmod((pixel->h*factor), 255);
    }
  }
  return image;
}

/**
 * Returns an image with a spotlight centered at (`centerX`, `centerY`).
 *
 * A spotlight adjusts the luminance of a pixel based on the distance the pixel
 * is away from the center by decreasing the luminance by 0.5% per 1 pixel euclidean
 * distance away from the center.
 *
 * For example, a pixel 3 pixels above and 4 pixels to the right of the center
 * is a total of `sqrt((3 * 3) + (4 * 4)) = sqrt(25) = 5` pixels away and
 * its luminance is decreased by 2.5% (0.975x its original value).  At a
 * distance over 200 pixels away, the luminance will always 0.
 *
 * The modified PNG is then returned.
 *
 * @param image A PNG object which holds the image data to be modified.
 * @param vignetteStrength The strenght of the vignette.
 *
 * @return The image with a spotlight.
 */
PNG addVignette(PNG image, int vignetteStrength) {
  if (!vignetteStrength) return image;
  double factor = vignetteStrength / 75000.0;
  int centerX = image.width() / 2;
  int centerY = image.height() / 2;

  for (unsigned int x = 0; x < image.width(); x++) {
    for (unsigned int y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      double distance = sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY));
      pixel->l = min(max(pixel->l - distance*factor*pixel->l, 0.0), 1.0);
    }
  }

  return image;
}


/**
 * Returns an image with an adjusted luminance.
 * @return The adjusted image.
 */
PNG adjustHighlights(PNG image, int adjustBy) {
  if (!adjustBy) return image;
  double factor = 1 + adjustBy/1000.0;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      if (pixel->l > 0.50) {
        pixel->l = min(max(pixel->l*factor, 0.0), 1.0);
      }
    }
  }
  return image;
}

/**
 * Returns an image with an adjusted luminance.
 * @return The adjusted image.
 */
PNG adjustShadows(PNG image, int adjustBy) {
  if (!adjustBy) return image;
  double factor = 1 + adjustBy/1000.0;
  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);
      if (pixel->l < 0.50) {
        pixel->l = min(max(pixel->l*factor, 0.0), 1.0);
      }
    }
  }
  return image;
}

PNG adjustAll(PNG image, int luminance, int saturation, int hue, int highlights, int shadows, int vignette) {
  if (!luminance && !saturation && !hue && !highlights && !shadows && !vignette) return image;
  double lumFactor = 1 + luminance/100.0;
  double satFactor = 1 + saturation/100.0;
  double hueFactor = 1 + hue/100.0;
  double highFactor = 1 + highlights/1000.0;
  double shadFactor = 1 + shadows/1000.0;
  double vignFactor = vignette/75000.0;

  int centerX;
  int centerY;
  double distance;

  for (unsigned x = 0; x < image.width(); x++) {
    for (unsigned y = 0; y < image.height(); y++) {
      HSLAPixel *pixel = image.getPixel(x, y);

      if (lumFactor) pixel->l = min(max(pixel->l*lumFactor, 0.0), 1.0);
      if (satFactor) pixel->s = min(max(pixel->s*satFactor, 0.0), 1.0);
      if (hueFactor) pixel->h = fmod((pixel->h*hueFactor), 255);
      if (highFactor && pixel->l > 0.50) pixel->l = min(max(pixel->l*highFactor, 0.0), 1.0);
      if (shadFactor && pixel->l < 0.50) pixel->l = min(max(pixel->l*shadFactor, 0.0), 1.0);
      if (vignFactor) {
        centerX = image.width() / 2;
        centerY = image.height() / 2;
        distance = sqrt((x-centerX)*(x-centerX)+(y-centerY)*(y-centerY));
        pixel->l = min(max(pixel->l - distance*vignFactor*pixel->l, 0.0), 1.0);
      }
    }
  }
  return image;
}


void adjustColumn(PNG* image, int column, int luminance, int saturation, int hue, int highlights, int shadows, int vignette) {
  if (!luminance && !saturation && !hue && !highlights && !shadows && !vignette) return;
  double lumFactor = 1 + luminance/100.0;
  double satFactor = 1 + saturation/100.0;
  double hueFactor = 1 + hue/100.0;
  double highFactor = 1 + highlights/1000.0;
  double shadFactor = 1 + shadows/1000.0;
  double vignFactor = vignette/75000.0;

  int centerX;
  int centerY;
  double distance;
  int width = image->width();
  int height = image->height();

  for (unsigned y = 0; y < height; y++) {
    HSLAPixel *pixel = image->getPixel(column, y);

    if (lumFactor) pixel->l = min(max(pixel->l*lumFactor, 0.0), 1.0);
    if (satFactor) pixel->s = min(max(pixel->s*satFactor, 0.0), 1.0);
    if (hueFactor) pixel->h = fmod((pixel->h*hueFactor), 255);
    if (highFactor && pixel->l > 0.50) pixel->l = min(max(pixel->l*highFactor, 0.0), 1.0);
    if (shadFactor && pixel->l < 0.50) pixel->l = min(max(pixel->l*shadFactor, 0.0), 1.0);
    if (vignFactor) {
      centerX = image->width() / 2;
      centerY = image->height() / 2;
      distance = sqrt((column-centerX)*(column-centerX)+(y-centerY)*(y-centerY));
      pixel->l = min(max(pixel->l - distance*vignFactor*pixel->l, 0.0), 1.0);
    }
  }
}