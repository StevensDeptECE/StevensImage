//
//  Exception.hpp
//  StevensImage
//
//  Created by Matt Sorrentino on 11/13/18.
//

#pragma once

class Exception
{
private:
    static const char** messages;
    static void loadErrors(const char filename[]);
    
public:
    Exception(const char filename[], uint32_t linenum, uint32_t message);
    
    enum MyErrors
    {
        COULD_NOT_OPEN_FILE = 0,
        COULD_NOT_SAVE_FILE = 1,
        PERMISSION_DENIED = 2,
        FILE_ALREADY_EXISTS = 3,
        INVALID_PARAM = 4,
        ILLEGAL_OPERATION = 5,
        INVALID_EXTENSION = 6,
        LIB_JP2_ERROR = 100,
    };
};


