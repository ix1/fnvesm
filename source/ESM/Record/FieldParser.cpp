#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

//TODO: These all need to be implemented in a portable manner

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

bool FieldParser::ParseXCLCField(ESMStream& stream, uint16_t length, XCLCField& outField) {
    //FIXME: According to the documents this is a 12 byte field, however I'm encountering only 8 bytes.
    if (length != sizeof(outField))
    {
        if (length == sizeof(uint32_t) * 2) {
            stream.Read32((uint32_t &)outField.X);
            stream.Read32((uint32_t &)outField.Y);
            
            outField.LandHideFlags = LandHideFlag::None;
            return true;
        }
        
        return false;
    }
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseXCLLField(ESMStream& stream, uint16_t length, XCLLField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseIMPFField(ESMStream& stream, uint16_t length, IMPFField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseFloatField(ESMStream& stream, uint16_t length, float& outValue) {
    if (length != sizeof(outValue))
        return false;
    
    stream.ReadRaw(&outValue, sizeof(outValue));
    
    return true;
}

bool FieldParser::ParseUint16Field(ESMStream& stream, uint16_t length, uint16_t& outValue) {
    if (length != sizeof(outValue))
        return false;
    
    stream.ReadRaw(&outValue, sizeof(outValue));
    
    return true;
}

bool FieldParser::ParseUint32Field(ESMStream& stream, uint16_t length, uint32_t& outValue) {
    if (length != sizeof(outValue))
        return false;
    
    stream.ReadRaw(&outValue, sizeof(outValue));
    
    return true;
}

bool FieldParser::ParseLandDataField(ESMStream& stream, uint16_t length, LandDataField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseMapDataField(ESMStream& stream, uint16_t length, MapDataField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseWorldMapOffsetField(ESMStream& stream, uint16_t length, WorldMapOffsetField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseObjectBoundsField(ESMStream& stream, uint16_t length, ObjectBoundsField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseIMPSField(ESMStream& stream, uint16_t length, IMPSField& outField) {
    if (length != sizeof(outField))
        return false;
    
    stream.ReadRaw(&outField, sizeof(outField));
    
    return true;
}

bool FieldParser::ParseOFSTField(ESMStream& stream, uint32_t length, std::vector<uint32_t>& outValue) {
    outValue.reserve(length / sizeof(uint32_t));
    
    stream.ReadRaw(&outValue[0], length);
    
    return true;
}

bool FieldParser::ParseVector3Field(ESMStream& stream, uint16_t length, Vector3F& outVector) {
    if (length <= sizeof(float) * 3)
        return false;
    
    stream.ReadRaw(&outVector.X, sizeof(outVector.X));
    stream.ReadRaw(&outVector.Y, sizeof(outVector.Y));
    stream.ReadRaw(&outVector.Z, sizeof(outVector.Z));
    
    return true;
}