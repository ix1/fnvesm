#pragma once

namespace ESM
{
    class ESMUtility {
    public:
        
        static std::string TagToString(ESMTag tag);
        
        static bool ZlibDecompress(std::vector<uint8_t>& source, std::vector<uint8_t>& destination, size_t sourceLength, size_t outLength);
    };
}