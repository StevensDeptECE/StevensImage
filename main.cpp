//
//  main.cpp
//  StevensImage
//
//  Created by Matt Sorrentino on 11/28/18.
//

#include "Image.hpp"
#include "Exception.hpp"


int main(int argc, const char * argv[])
{
    Image i("test.jpeg");
    i.flipHorizontal();
    i.save("test-output.jpeg");

    return 0;
}
