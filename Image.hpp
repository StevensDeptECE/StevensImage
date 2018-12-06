//
//  Image.hpp
//  StevensImage
//
//  Created by Matt Sorrentino on 11/10/18.
//

#pragma once

#include <iostream>
#include <IL/il.h>
#include <jasper/jasper.h>
#include "Exception.hpp"

class Image
{
private:
    uint32_t width_;                // Holds the width of the image (in pixels).
    uint32_t height_;               // Holds the height of the image (in pixels).
    uint32_t *rgba;                 // Pointer to 1D array that holds pixel data as RGBA.

    void setWidth();                // Sets width_ to the correct value
    void setHeight();               // Sets height_ to the correct value
    void setRGBA();                 // Loads uint32_t *rgba with pixel data from devIL
    void pushPixelDataToDevIL();    // Replaces devIL's byte array of pixel data with our latest pixel data
    
    bool isValidPNG() const;        // Not yet implemented.
    bool isValidJPeg() const;       // Not yet implemented.
    static char* loadFile();        // Not yet implemented.
    
    /*
     The following methods are for use when we replace
     the devIL load and save calls with our own code.
    */
    bool loadJPEG2000(const char filename[]);               // Not yet implemented.
    void saveJPEG2000(const char filename[]);               // Not yet implemented.
    void loadPNG(int fh);                                   // Not yet implemented.
    void savePNG(int fh);                                   // Not yet implemented.
    
    // For future use when we need to check file extensions at load time.
    // Extension checking is currently handled by devIL in the load function we call.
    std::string checkExtension(const char filename[]);
    
    Image(uint32_t width, uint32_t height) : width_(width), height_(height), rgba(new uint32_t[width*height]) {}
    
public:
    Image(const char filename[]);
    Image(uint32_t width, uint32_t height, const uint32_t RGBAVAL);     // Not yet functional.
    ~Image() { delete [] rgba; }
    
    Image(const Image &i2);
    Image& operator =(const Image &i2);
    Image(Image&& orig) : width_(orig.width_), height_(orig.height_), rgba(orig.rgba) { orig.rgba = nullptr; }
    
    bool load(const char filename[]);
    bool save(const char filename[]);

    void clear(const uint32_t RGBAVAL);
    void flipHorizontal();
    void flipVertical();
    void rotate180();
    void copy(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t x2, uint32_t y2);        // Not yet implemented.
    void resize(uint32_t w, uint32_t h);                                                        // Not yet implemented.

    // Image Characteristics
    uint32_t    width() const { return width_; }        // Public access to width of image.
    uint32_t    height() const { return height_; }      // Public access to height of image.
    uint32_t*   getPixels() { return rgba; }            // Public access to pixel data of image.
};

