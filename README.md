# StevensImage
Clean wrapper for some ugly image libraries, designed to teach encapsulation and modernizing code.

## The Basics
StevensImage allows for simple image manipulations. It currently utilizes Developer's Image Library (devIL) to load and save images. The initial spec was created by Professor Dov Kruger and the initial implementation was performed by Matt Sorrentino during a C++ independent study with Professor Kruger. 

## Getting Started
Download StevensImage. Install devIL from source (along with all of its dependencies) and add it to your project. 

## Goals
1) Implement all methods that are currently specified in Image.hpp.

2) Complete the implementation of exception handling using the Exception class.

3) Rewrite our load and save methods with clean code instead of calling devIL's ilLoadImage(filename) and ilSaveImage(filename) functions.

4) Implement additional methods, which may include image rotation and shape drawing functionality, amongst other things.


## Code

### Public Members

#### Constructors
```c++
Image(const char filename[]);
```
Creates an Image object of an image loaded from file using the filepath specified by the single argument.
<br/><br/>
```c++
Image(uint32_t width, uint32_t height, const uint32_t RGBAVAL);
```
Creates an Image object of a single color as specified by the thrid argument. Size of the image is based on the width and height declared by the first and second arguments. Right now this is not fully functional because we need to find a way to tell devIL the size of our image so we can feed it data. Because of this, two lines of code are commented out for now. The image data cannot be manipulated or saved until we can properly share the image characteristics with devIL.
<br/><br/>
#### IO Methods
```c++
bool load(const char filename[]);
```
Loads an image from file using the filepath specified by the single argument. Returns true if the load is successful, false if something goes wrong. Right now it also prints a message in the console as to the result of the operation. Exception handling is not currently in use, but should be. This method currently calls devIL's ilLoadImage(filename) to perform the loading. Our goal is to rewrite our load method with clean code instead of using their's. Because we are using devIL, the private methods for loading images and checking extensions are not currently in use.
<br/><br/>
```c++
bool save(const char filename[]);
```
Saves an image to disk using the filepath specified by the single argument. Returns true if the load is successful, false if something goes wrong. Right now it also prints a message in the console as to the result of the operation. Exception handling is not currently in use, but should be. This method calls devIL's ilSaveImage(filename) to perform the saving right now. Our goal is to rewrite our save method with clean code. Because we are using devIL, the private methods for saving images are not currently in use.
<br/><br/>
#### Manipulation Methods
```c++
void clear(const uint32_t RGBAVAL);
```
Makes the image a single color -- the color specified by the single argument in RGBA format.
<br/><br/>
```c++
void flipHorizontal();
```
Flips the image horizontally.
<br/><br/>
```c++
void flipVertical();
```
Flips the image vertically.
<br/><br/>
```c++
void rotate180();
```
Efficiently rotates the image 180 degrees. The visual outcome is equivalent to that of flipping the image both vertically and horizontally, but the algorithm for this rotation is much more efficient than calling those two methods.
<br/><br/>
```c++
void copy(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t x2, uint32_t y2);
```
**Not yet implemented.** Copies a rectangular section of the image specified by the first four arguments to a new location within the image specified by the last two arguments. The efficient way of writing this is as follows: Check to see if there are overlapping pixels between the original and new sections. If there are, copy the pixel data in the order that prevents data from being overwritten. There is no need to copy the pixel data to a temporary structure.
<br/><br/>
```c++
void resize(uint32_t w, uint32_t h);
```
**Not yet implemented.** Resizes an image to the height and width specified by the two arguments. Linear algebra will probably be necessary to resize for scaling values that are not multiples of two.
<br/><br/>
#### Get Methods
```c++
uint32_t width() const { return width_; } 
```
Returns a uint32_t representing the width of the image in pixels.
<br/><br/>
```c++
uint32_t height() const { return height_; }
```
Returns a uint32_t representing the height of the image in pixels.
<br/><br/>
```c++
uint32_t* getPixels() { return rgba; }
```
Returns a pointer to a 1D array of uint32_t representing all of the pixels in the image.
<br/><br/>
