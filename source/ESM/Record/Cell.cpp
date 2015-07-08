#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

Cell::Cell(FormIdentifier id, int block, int subblock) 
    : mFormID(id), mBlock(block), mSubblock(subblock)
{
    
}

Cell::~Cell() {
    
}

bool Cell::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        
        stream.ReadFieldHeader(header);
        
        switch(header.Tag) {
            case ESMTag::EDID:
                FieldParser::ParseEDIDField(stream, header.Size, mEditorID);
                break;
                
            case ESMTag::FULL:
                FieldParser::ParseEDIDField(stream, header.Size, mFullName);
                break;
                
            case ESMTag::DATA:
                FieldParser::ParseByteValue(stream, header.Size, (uint8_t&)mFlags);
                break;
                
            case ESMTag::XCLC:
                FieldParser::ParseXCLCField(stream, header.Size, mCellLocation);
                break;
                
            case ESMTag::XCLL:
                FieldParser::ParseXCLLField(stream, header.Size, mLighting);
                break;
                
            case ESMTag::IMPF:
                FieldParser::ParseIMPFField(stream, header.Size, mFootstepMaterial);
                break;
                
            case ESMTag::XCLW:
                FieldParser::ParseFloatField(stream, header.Size, mWaterHeight);
                break;
                
            case ESMTag::XNAM:
                FieldParser::ParseEDIDField(stream, header.Size, mWaterNoiseTexture);
                break;
                
            case ESMTag::LTMP:
                FieldParser::ParseFormID(stream, header.Size, mLightTemplateID);
                break;
                
            case ESMTag::LNAM:
                FieldParser::ParseUint32Field(stream, header.Size, mLightTemplateFlags);
                break;
                
            case ESMTag::XCLR:
            {
                FormIdentifier regionID;
                FieldParser::ParseFormID(stream, header.Size, regionID);
                mRegionIdentifiers.push_back(regionID);
                break;
            }
            
            case ESMTag::XCIM:
                FieldParser::ParseFormID(stream, header.Size, mImageSpaceID);
                break;
                
            case ESMTag::XCET:
                FieldParser::ParseByteValue(stream, header.Size, mUnknownByte);
                break;
                
            case ESMTag::XEZN:
                FieldParser::ParseFormID(stream, header.Size, mEncounterZoneID);
                break;
                
            case ESMTag::XCCM:
                FieldParser::ParseFormID(stream, header.Size, mClimateID);
                break;
                
            case ESMTag::XCWT:
                FieldParser::ParseFormID(stream, header.Size, mWaterID);
                break;
                
            case ESMTag::XOWN:
                FieldParser::ParseFormID(stream, header.Size, mOwnerID);
                break;
                
            case ESMTag::XRNK:
                FieldParser::ParseUint32Field(stream, header.Size, mFactionRank);
                break;
                
            case ESMTag::XCAS:
                FieldParser::ParseFormID(stream, header.Size, mAcousticSpaceID);
                break;
                
            case ESMTag::XCMT:
                FieldParser::ParseByteValue(stream, header.Size, mUnusedByte);
                break;
                
            case ESMTag::XCMO:
                FieldParser::ParseFormID(stream, header.Size, mMusicID);
                break;
                
            default:
                return false;
        }
    }
    
    return true;
}

void Cell::AddObject(CellChildType cellType, WorldObject& object) {
    switch(cellType) {
        case CellChildType::Direct:
        case CellChildType::Persistent:
            mObjects.push_back(std::move(object));
            break;
            
        case CellChildType::Temporary:
            mTemporaryObjects.push_back(std::move(object));
            break;
            
        case CellChildType::Distant:
            mDistantObjects.push_back(std::move(object));
            break;
            
        default:
            break;
    }
}