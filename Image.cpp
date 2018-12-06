//
//  Image.cpp
//  StevensImage
//
//  Created by Matt Sorrentino on 11/10/18.
//

#include "Image.hpp"


Image::Image(const char filename[])
{
    ilInit();
    load(filename);
    setWidth();
    setHeight();
    setRGBA();
}


Image::Image(uint32_t width, uint32_t height, const uint32_t RGBAVAL)
{
    //ilInit();
    width_ = width;
    height_ = height;
    
    for (int i = 0; i < width_ * height_; i++)
    {
        rgba[i] = RGBAVAL;
    }
    
    //pushPixelDataToDevIL();
}


Image::Image(const Image &i2) : width_(i2.width_), height_(i2.height_)
{
    rgba = new uint32_t [width_ * height_];
    for (int i = 0; i < width_ * height_; i++)
    {
        rgba[i] = i2.rgba[i];
    }
    
    // rgba = new uint32_t[i2.width_ * i2.height_];
    // std::copy(i2.rgba, i2.rgba + i2.width_ * i2.height_, rgba);
}


Image& Image::operator =(const Image &i2)
{
    if (this != &i2)
    {
        uint32_t * newrgba = new uint32_t[i2.width_ * i2.height_];
        std::copy(i2.rgba, i2.rgba + i2.width_ * i2.height_, newrgba);
        
        delete[] rgba;
        
        rgba = newrgba;
    }
    
    return *this;
}


void Image::setWidth()
{
    width_ = ilGetInteger(IL_IMAGE_WIDTH);
}


void Image::setHeight()
{
    height_ = ilGetInteger(IL_IMAGE_HEIGHT);
}


void Image::setRGBA()
{
    ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
    ILubyte *bytes = ilGetData();
    
    rgba = new uint32_t [width_ * height_];

    for (int i = 0; i < height_; i++)
    {
        for (int j = 0; j < width_; j++)
        {
            rgba[(i*width_ + j)] = bytes[(i * width_ + j) * 4 + 0]
                                | (bytes[(i * width_ + j) * 4 + 1] << 8)
                                | (bytes[(i * width_ + j) * 4 + 2] << 16)
                                | (bytes[(i * width_ + j) * 4 + 3] << 24);
        }
    }
}


void Image::pushPixelDataToDevIL()
{
    ILubyte *data = new ILubyte[width_ * height_ * 4];
    
    for (int i = 0, j = 0; i < width_ * height_; i++, j+=4)
    {
        data[j] = (rgba[i] & 0x000000FF);
        data[j + 1] = (rgba[i] & 0x0000FF00) >> 8;
        data[j + 2] = (rgba[i] & 0x00FF0000) >> 16;
        data[j + 3] = (rgba[i] & 0xFF000000) >> 24;
    }

    ilSetData(data);
    delete [] data;
}


void Image::clear(const uint32_t RGBAVAL)
{
    for (int i = 0; i < width_ * height_; i++)
    {
        rgba[i] = RGBAVAL;
    }
}


void Image::rotate180()
{
    uint32_t temp;
    
    for (int i = 0; i < (width_ * height_) / 2; i++)
    {
        temp = rgba[i];
        rgba[i] = rgba[(width_ * height_) - i - 1];
        rgba[(width_ * height_) - i - 1] = temp;
    }
    
    pushPixelDataToDevIL();
}


void Image::flipHorizontal()
{
    uint32_t temp [height_];
    
    for (int currentCol = 0; currentCol < (width_) / 2; currentCol++)
    {
        //populate temp array with a col of pixels
        for (int row = 0; row < height_; row++)
        {
            temp[row] = rgba[(row * width_ + currentCol)];
        }
        
        //overrite saved col with opposite col
        for (int row = 0; row < height_; row++)
        {
            rgba[row * width_ + currentCol] = rgba[(width_ * row) + width_ - currentCol ];
        }
        
        //overrite opposite col with saved col
        for (int row = 0; row < height_; row++)
        {
            rgba[(width_ * row) + width_ - currentCol ] = temp[row];
        }
        
        pushPixelDataToDevIL();
    }
}


void Image::flipVertical()
{
    uint32_t temp [width_];
    
    for (int currentRow = 0; currentRow < (height_) / 2; currentRow++)
    {
        //populate temp array with a row of pixels
        for (int col = 0; col < width_; col++)
        {
            temp[col] = rgba[(currentRow * width_ + col)];
        }
        
        //overrite saved row with opposite row
        for (int col = 0; col < width_; col++)
        {
            rgba[currentRow * width_ + col] = rgba[((height_ - currentRow - 1) * width_ + col)];
        }
        
        //overrite opposite row with saved row
        for (int col = 0; col < width_; col++)
        {
            rgba[((height_ - currentRow - 1) * width_ + col)] = temp[col];
        }

        pushPixelDataToDevIL();
    }
}


std::string Image::checkExtension(const char filename[])
{
    bool hitDot = false;
    std::string ext;
    for (int i = 0; i < strlen(filename); i++)
    {
        if (!hitDot && filename[i] == '.')
        {
            hitDot = true;
        }
        if (hitDot && filename[i] != '.')
        {
            ext += filename[i];
        }
    }
    return ext;
}


/**
 Description:   Loads image from file by calling devIL's ilLoadImage function.
                Future goal is to replace this function call with our own code.
 Return:
 */
bool Image::load(const char filename[])
{
    bool success = ilLoadImage(filename); //load image
    if (success)
    {
        std::cout<< "Successfully loaded image. \n";
        return true;
    }
    else
    {
        std::cout<< "Could not load image. \n";
        //throw Exception(__FILE__, __LINE__, 0);
        return false;
    }
}

bool Image::save(const char filename[])
{
    bool save = ilSaveImage(filename);
    if (save)
    {
        std::cout<< "Successfully saved image. \n";
        return true;
    }
    else
    {
        std::cout << "Save failed. \n";
        //throw Exception(__FILE__, __LINE__, 1);
        return false;
    }
}

