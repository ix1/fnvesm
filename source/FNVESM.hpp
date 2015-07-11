
#pragma once

#include <cstddef>
#include <map>
#include <fstream>
#include <string>
#include <vector>
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
        
        Vector3F() : X(0.0f), Y(0.0f), Z(0.0f) {}
    };
}