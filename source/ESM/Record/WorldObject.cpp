#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

static const std::string sWorldObjectTypeUnknown = "Unknown";
static const std::string sWorldObjectTypeStaticName = "Static";
static const std::string sWorldObjectTypeCreatureName = "Creature";
static const std::string sWorldObjectTypeCharacterName = "Character";

WorldObject::WorldObject(WorldObjectType type, FormIdentifier id) 
    :  mType(type), mFormID(id)
{
    
}

WorldObject::~WorldObject() {
    
}

bool WorldObject::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        
        stream.ReadFieldHeader(header);
        ESMStream substream(stream, header.Size);
        
        switch(header.Tag) {
            case ESMTag::EDID:
                FieldParser::ParseEDIDField(substream, header.Size, mEditorID);
                break;
                
            case ESMTag::NAME:
                FieldParser::ParseFormID(substream, header.Size, mBaseID);
                break;
                
            case ESMTag::XSCL:
                FieldParser::ParseFloatField(substream, header.Size, mScale);
                break;
            
            case ESMTag::DATA:
                FieldParser::ParseVector3Field(substream, header.Size, mPosition);
                FieldParser::ParseVector3Field(substream, header.Size, mRotation);
                break;
            
            default:
                substream.Skip(header.Size);
                break;
        }
    }
    
    return true;
}

const std::string& WorldObject::GetTypeName() const {
    switch(mType) {
        case WorldObjectType::Static:
            return sWorldObjectTypeStaticName;
        
        case WorldObjectType::Creature:
            return sWorldObjectTypeCreatureName;
            
        case WorldObjectType::Character:
            return sWorldObjectTypeCharacterName;
            
        default:
            return sWorldObjectTypeUnknown;
    }
}