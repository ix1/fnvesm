#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

GameSetting::GameSetting(FormIdentifier id) 
    : mFormID(id)
{
    
}
GameSetting::~GameSetting() {}

bool GameSetting::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        
        stream.ReadFieldHeader(header);
        
        switch(header.Tag) {
            case ESMTag::EDID:
                FieldParser::ParseEDIDField(stream, header.Size, mKey);
                break;
                
            case ESMTag::DATA:
                FieldParser::ParseBinaryField(stream, header.Size, mValue);
                break;
                
            default:
                return false;
        }
    }
    
    return true;
}

GameSettingValueType GameSetting::GetValueType() const {
    if (mKey.length() != 0) {
        char startingValue = mKey[0];
        
        switch(startingValue) {
            case 's':
                return GameSettingValueType::String;
                
            case 'i':
                return GameSettingValueType::Integer;
                
            case 'f':
                return GameSettingValueType::Float;
        }
    }
    
    return GameSettingValueType::Unknown;
}

std::string GameSetting::GetValueAsString() const {
    return std::string((const char *)&mValue[0]);
}

int32_t GameSetting::GetValueAsInteger() const {
    return *((int32_t *)&mValue[0]);
}

float GameSetting::GetValueAsFloat() const {
    return *((float *)&mValue[0]);
}