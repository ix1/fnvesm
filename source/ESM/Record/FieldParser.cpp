#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

bool FieldParser::ParseFormID(ESMStream& stream, uint16_t length, FormIdentifier& outValue) {
    if (length != sizeof(outValue))
        return false;
    
    stream.ReadRaw(&outValue, sizeof(outValue));
    
    return true;
}

bool FieldParser::ParseEDIDField(ESMStream& stream, uint16_t length, std::string& outValue) {
    if (length == 0)
        return true;
    
    stream.ReadCString(length, outValue);
    return true;
}

bool FieldParser::ParseTXNNField(ESMStream& stream, uint16_t length, std::string& outValue) {
    return ParseEDIDField(stream, length, outValue);
}

bool FieldParser::ParseOBDNField(ESMStream& stream, uint16_t length, OBNDField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseDODTField(ESMStream& stream, uint16_t length, DODTField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseSCHRField(ESMStream& stream, uint16_t length, SCHRField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseBinaryField(ESMStream& stream, uint16_t length, std::vector<uint8_t>& outVector) {
    outVector.resize(length);
    
    stream.ReadRaw(&outVector[0], length);
    
    return true;
}

bool FieldParser::ParseHavokData(ESMStream& stream, uint16_t length, LandTextureHavokData& havokData) {
    if (length != sizeof(havokData))
        return false;
    
    stream.ReadRaw(&havokData, sizeof(havokData));
    
    return true;
}

bool FieldParser::ParseByteValue(ESMStream& stream, uint16_t length, uint8_t& outValue) {
    if (length != sizeof(outValue))
        return false;
    
    stream.ReadRaw(&outValue, sizeof(outValue));
    
    return true;
}