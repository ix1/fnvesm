#include "../FNVESM.hpp"
#include "ESMTag.hpp"
#include "ESMUtility.hpp"
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
