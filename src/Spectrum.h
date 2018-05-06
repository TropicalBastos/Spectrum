#include <cstdlib> 
#include <cstdio> 
 
class Spectrum 
{ 
public: 
    // Rgb structure, i.e. a pixel 
    struct Rgb 
    { 
        Rgb() : r(0), g(0), b(0) {} 
        Rgb(float c) : r(c), g(c), b(c) {} 
        Rgb(float _r, float _g, float _b) : r(_r), g(_g), b(_b) {} 
        bool operator != (const Rgb &c) const 
        { return c.r != r || c.g != g || c.b != b; } 
        Rgb& operator *= (const Rgb &rgb) 
        { r *= rgb.r, g *= rgb.g, b *= rgb.b; return *this; } 
        Rgb& operator += (const Rgb &rgb) 
        { r += rgb.r, g += rgb.g, b += rgb.b; return *this; } 
        friend float& operator += (float &f, const Rgb rgb) 
        { f += (rgb.r + rgb.g + rgb.b) / 3.f; return f; } 
        float r, g, b; 
    }; 
 
    Spectrum() : w(0), h(0), pixels(NULL) { /* empty Spectrum */ } 
    Spectrum(const unsigned int &_w, const unsigned int &_h, const Rgb &c = kBlack) : 
        w(_w), h(_h), pixels(NULL) 
    { 
        pixels = new Rgb[w * h]; 
        for (int i = 0; i < w * h; ++i) 
            pixels[i] = c; 
    } 
    const Rgb& operator [] (const unsigned int &i) const 
    { return pixels[i]; } 
    Rgb& operator [] (const unsigned int &i) 
    { return pixels[i]; } 
    ~Spectrum() 
    { if (pixels != NULL) delete [] pixels; } 
    unsigned int w, h; // Spectrum resolution 
    Rgb *pixels; // 1D array of pixels 
    static const Rgb kBlack, kWhite, kRed, kGreen, kBlue; // Preset colors
    static Rgb getRandomColor();
    static void createSpectrum(int width, int height, const char* output);
    static Rgb buildSpectrumPixel(Rgb&, float, int);
    float mapWidthToDepth();
    float mapWidthToSpectrum();
    static float normalize(float, float, float, float, float);

    /* STAGES - for pixelbuilder */
    static const int SPECTRUM_GREEN = 0;
    static const int SPECTRUM_RED = 1;
}; 