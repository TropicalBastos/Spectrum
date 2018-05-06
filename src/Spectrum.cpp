#include "Spectrum.h"
#include <fstream>
#include <math.h>

/** Lets create that specturm
 * @param width, height, output
 */
void Spectrum::createSpectrum(int width, int height, const char* output){
    Spectrum src;
    src.w = width; 
    src.h = height; 
    src.pixels = new Spectrum::Rgb[width * height]; 
    Spectrum::Rgb rgbBuf(0, 0, 1);
    float mapped = src.mapWidthToDepth();
    float spectrum = src.mapWidthToSpectrum();

    for(int i = 0;  i < (width * height);){
        for(int j = 0;  j < width; j++){
            float delta = Spectrum::normalize((spectrum * j), width, 0.0f, 0.0f, 1.0f);
            Spectrum::Rgb rgb(Spectrum::buildSpectrumPixel(rgbBuf, delta));
            src.pixels[i] = rgb;
            i++;
        }
    }

    printf("%s", output);

    std::ofstream ofs; 
    try { 
        ofs.open(output, std::ios::binary); // need to spec. binary mode for Windows users 
        if (ofs.fail()) throw("Can't open output file"); 
        ofs << "P6\n" << src.w << " " << src.h << "\n255\n"; 
        unsigned char r, g, b; 
        // loop over each pixel in the image, clamp and convert to byte format
        for (int i = 0; i < src.w * src.h; ++i) { 
            r = static_cast<unsigned char>(std::min(1.f, src.pixels[i].r) * 255); 
            g = static_cast<unsigned char>(std::min(1.f, src.pixels[i].g) * 255); 
            b = static_cast<unsigned char>(std::min(1.f, src.pixels[i].b) * 255); 
            ofs << r << g << b; 
        } 
        ofs.close(); 
    } 
    catch (const char *err) { 
        fprintf(stderr, "%s\n", err); 
        ofs.close(); 
    }
}

Spectrum::Rgb Spectrum::buildSpectrumPixel(Spectrum::Rgb& rgb, float delta){
    //printf("%.3f\n", rgb.r - delta);
    Spectrum::Rgb rgbNew(rgb.r + delta, rgb.g, rgb.b - delta);
    return rgbNew;
}

float Spectrum::mapWidthToDepth(){
    return float(1.f / this->w);
}

float Spectrum::mapWidthToSpectrum(){
    return float((255 + 255 + 255) / this->w);
}

float Spectrum::normalize (float value, float maxInRange, float minInRange, float minOutRange, float maxOutRange) {
    float x = value / (maxInRange - minInRange);
    float result = minOutRange + (maxOutRange - minOutRange) * x;
    return result;
}


/**
 * Gets a random color, referring to the QT implementation
 */ 
Spectrum::Rgb Spectrum::getRandomColor(){
    float r = rand() % 255, g = rand() % 255, b = rand() % 255;
    Spectrum::Rgb rgb(r, g, b);
    return rgb;
}