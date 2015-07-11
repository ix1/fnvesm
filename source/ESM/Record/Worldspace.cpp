#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "../ESMUtility.hpp"
#include "FieldParser.hpp"
using namespace ESM;

Worldspace::Worldspace(FormIdentifier id) 
    : mFormID(id)
{
    
}

Worldspace::~Worldspace() {
    
}

bool Worldspace::Parse(ESMStream& stream) {
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
                
            case ESMTag::XEZN:
                FieldParser::ParseFormID(stream, header.Size, mEncounterZoneID);
                break;
                
            case ESMTag::WNAM:
                FieldParser::ParseFormID(stream, header.Size, mParentWorldspaceID);
                break;
                
            case ESMTag::PNAM:
                FieldParser::ParseUint16Field(stream, header.Size, mParentFlags);
                break;
                
            case ESMTag::CNAM:
                FieldParser::ParseFormID(stream, header.Size, mClimateID);
                break;
                
            case ESMTag::NAM2:
                FieldParser::ParseFormID(stream, header.Size, mWaterID);
                break;
                
            case ESMTag::NAM3:
                FieldParser::ParseFormID(stream, header.Size, mLODWaterType);
                break;
                
            case ESMTag::NAM4:
                FieldParser::ParseFloatField(stream, header.Size, mLODWaterHeight);
                break;
                
            case ESMTag::DNAM:
                FieldParser::ParseLandDataField(stream, header.Size, mLandData);
                break;
                
            case ESMTag::ICON:
                FieldParser::ParseEDIDField(stream, header.Size, mLargeIconFile);
                break;
                
            case ESMTag::MICO:
                FieldParser::ParseEDIDField(stream, header.Size, mSmallIconFile);
                break;
                
            case ESMTag::MNAM:
                FieldParser::ParseMapDataField(stream, header.Size, mMapData);
                break;
                
            case ESMTag::ONAM:
                FieldParser::ParseWorldMapOffsetField(stream, header.Size, mWorldMapOffset);
                break;
                
            case ESMTag::INAM:
                FieldParser::ParseFormID(stream, header.Size, mImageSpaceID);
                break;
                
            case ESMTag::DATA:
                FieldParser::ParseByteValue(stream, header.Size, mFlags);
                break;
                
            case ESMTag::NAM0:
                FieldParser::ParseObjectBoundsField(stream, header.Size, mMinBounds);
                break;
                
            case ESMTag::NAM9:
                FieldParser::ParseObjectBoundsField(stream, header.Size, mMaxBounds);
                break;
                
            case ESMTag::ZNAM:
                FieldParser::ParseFormID(stream, header.Size, mMusicID);
                break;
                
            case ESMTag::NNAM:
                FieldParser::ParseEDIDField(stream, header.Size, mCanopyShadowFile);
                break;
                
            case ESMTag::XNAM:
                FieldParser::ParseEDIDField(stream, header.Size, mWaterNoiseTextureFile);
                break;
                
            case ESMTag::IMPS:
                FieldParser::ParseIMPSField(stream, header.Size, mImpactData);
                break;
                
            case ESMTag::IMPF:
                FieldParser::ParseIMPFField(stream, header.Size, mFootstepData);
                break;
                
            case ESMTag::OFST:
                FieldParser::ParseOFSTField(stream, header.Size, mOffsetData);
                break;
                
            // This is disgusting, but there is no nice way to handle this field.
            case ESMTag::XXXX:
            {
                uint32_t sizeOverride = 0;
                
                FieldParser::ParseUint32Field(stream, header.Size, sizeOverride);
                
                stream.ReadFieldHeader(header);
                
                if (header.Tag != ESMTag::OFST || header.Size != 0)
                    return false;
                
                FieldParser::ParseOFSTField(stream, sizeOverride, mOffsetData);
                
                break;
            }
                
            default:
                return false;
        }
    }
    
    return true;
}

void Worldspace::ExportYAML(int tablevel, std::ostream& stream, const std::map<FormIdentifier, Cell>& cellMap) const {
    ESMUtility::EmitTabs(tablevel, stream) << "- form: " << mFormID << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  edid: " << mEditorID << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  name: " << mFullName << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  cells:" << std::endl;
    
    for(auto itr = mCells.begin(); itr != mCells.end(); ++itr) {
        auto cellItr = cellMap.find(*itr);
        
        if (cellItr == cellMap.end())
            continue; //TODO: This shouldn't ever happen, it's checked during the load
        
        (*cellItr).second.ExportYAML(tablevel + 1, stream);
    }
}