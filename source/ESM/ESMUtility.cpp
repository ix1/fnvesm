#include "../FNVESM.hpp"
#include "ESMTag.hpp"
#include "ESMUtility.hpp"
#include <zlib.h>
#include <cstring>
using namespace ESM;

std::string ESMUtility::TagToString(ESMTag tag)
{
    char name[8], *pvalue = name;
    uint32_t tagValue = (uint32_t)tag;
    
    for(size_t x = 0; x < 4; x++) {
        uint8_t charValue = (tagValue >> (8 * x)) & 0xFF;

        if (charValue < ' ') {
            *pvalue++ = 'X';
            charValue = '0' + charValue;
        }
        
        *pvalue++ = charValue;
    }
    
    *pvalue = '\0';
    
    return std::string(name);
}

bool ESMUtility::ZlibDecompress(std::vector<uint8_t>& source, std::vector<uint8_t>& destination, size_t sourceLength, size_t outLength) {
    z_stream zlibStream;
    
    memset(&zlibStream, 0, sizeof(zlibStream));
    
    zlibStream.avail_in = sourceLength;
    zlibStream.avail_out = outLength;
    zlibStream.next_in = &source[0];
    zlibStream.next_out = &destination[0];
    
    if (inflateInit2(&zlibStream, 0) != Z_OK) {
        return false;
    }
    
    int result = inflate(&zlibStream, Z_FINISH);
    
    inflateEnd(&zlibStream);
    
    if (result != Z_STREAM_END) {
        return false;
    }
    
    return true;
}

std::ostream& ESMUtility::EmitTabs(int tabs, std::ostream& stream) {
    for(int x = 0; x < tabs; ++x) {
        stream << "    ";
    }
    
    return stream;
}
