#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

TextureSet::TextureSet(FormIdentifier id) 
    : mFormIdentifier(id)
{
    
}
TextureSet::~TextureSet() {}

bool TextureSet::Parse(ESMStream& stream) {
    
    while(stream.IsValid() == true) {
        FieldHeader fieldHeader;
        
        stream.ReadFieldHeader(fieldHeader);
        
        switch(fieldHeader.Tag) {
            case ESMTag::EDID:
                FieldParser::ParseEDIDField(stream, fieldHeader.Size, mEditorId);
                break;
                
            case ESMTag::OBND:
                FieldParser::ParseOBDNField(stream, fieldHeader.Size, mBounds);
                break;
                
            case ESMTag::TX00:
            case ESMTag::TX01:
            case ESMTag::TX02:
            case ESMTag::TX03:
            case ESMTag::TX04:
            case ESMTag::TX05:
            case ESMTag::TX06:
            case ESMTag::TX07:
            {
                std::string textureName;
                FieldParser::ParseTXNNField(stream, fieldHeader.Size, textureName);
                
                mTextureNames.push_back(std::move(textureName));
                break;
            }
                
            case ESMTag::DODT:
                FieldParser::ParseDODTField(stream, fieldHeader.Size, mDecalData);
                break;
                
            case ESMTag::DNAM:
                stream.Read16((uint16_t&)mFlags);
                break;
                
            default:
                return false;
        }
    }
    
    return true;
}

LandscapeTextureSet::LandscapeTextureSet(FormIdentifier id) 
    : mFormIdentifier(id)
{
    
}

LandscapeTextureSet::~LandscapeTextureSet() {
    
}

bool LandscapeTextureSet::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        
        stream.ReadFieldHeader(header);
        
        switch(header.Tag) {
            case ESMTag::EDID:
                FieldParser::ParseEDIDField(stream, header.Size, mEditorId);
                break;
                
            case ESMTag::ICON:
                FieldParser::ParseEDIDField(stream, header.Size, mLargeIconFilename);
                break;
                
            case ESMTag::MICO:
                FieldParser::ParseEDIDField(stream, header.Size, mSmallIconFilename);
                break;
                
            case ESMTag::TNAM:
                FieldParser::ParseFormID(stream, header.Size, mTextureIdentifier);
                break;
                
            case ESMTag::HNAM:
                FieldParser::ParseHavokData(stream, header.Size, mHavokData);
                break;
                
            case ESMTag::SNAM:
                FieldParser::ParseByteValue(stream, header.Size, mSpecularExponent);
                break;
                
            case ESMTag::GNAM:
                FieldParser::ParseFormID(stream, header.Size, mGrassIdentifier);
                break;
                
            default:
                return false;
        }
    }
    
    return true;
}