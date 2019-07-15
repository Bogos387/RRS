#ifndef SVETOFORSTRUCT_H
#define SVETOFORSTRUCT_H

#include    <iostream>

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
struct svetofor_struct_t
{
    double      x;
    std::string type;

    svetofor_struct_t()
        : x(0.0)
        , type("")
    {

    }
};

#endif // SVETOFORSTRUCT_H
