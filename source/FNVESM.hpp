
#pragma once

#include <cstddef>
#include <map>
#include <fstream>
#include <string>
#include <vector>
#include <streambuf> //ZZ
#include <sstream>
#include <list>
#include <cassert>

typedef uint32_t FormIdentifier;

namespace ESM
{
    class ESMStream;
    
    struct Vector3F {
        float X;
        float Y;
        float Z;
    };
}