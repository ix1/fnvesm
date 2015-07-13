#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "../ESMUtility.hpp"
#include "FieldParser.hpp"
#include <iostream>
#include <iomanip>
using namespace ESM;

StaticObject::StaticObject(StaticObjectType type,FormIdentifier id)
    : mType(type), mFormID(id)
{
    
}

StaticObject::~StaticObject() {
    
}

bool StaticObject::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        stream.ReadFieldHeader(header);
        
        switch(header.Tag) {
            case ESMTag::EDID:
            {
                FieldParser::ParseEDIDField(stream, header.Size, mEditorID);
                
                break;
            }
            
            case ESMTag::FULL:
            {
                FieldParser::ParseEDIDField(stream, header.Size, mFullName);
                break;
            }
            
            case ESMTag::MODL:
            case ESMTag::MOD2:
            case ESMTag::MOD3:
            case ESMTag::MOD4:
            {
                std::string modelName;
                
                stream.ReadCString(header.Size, modelName);
                
                ModelData modelData(modelName);
                
                if (modelData.Parse(stream) == false) {
                    return false;
                }
                
                mModelData.push_back(std::move(modelData));
                break;
            }
            
            case ESMTag::OBND:
            {
                FieldParser::ParseOBDNField(stream, header.Size, mBounds);
                break;
            }
            
            case ESMTag::BRUS:
            {
                FieldParser::ParseByteValue(stream, header.Size, (uint8_t &)mBrushPassthroughSound);
                break;
            }
            
            case ESMTag::SCRI:
            {
                FieldParser::ParseFormID(stream, header.Size, mScriptID);
                break;
            }
            
            case ESMTag::RNAM:
            {
                FieldParser::ParseFormID(stream, header.Size, mSoundID);
                break;
            }
            
            case ESMTag::MNAM:
            {
                stream.Skip(header.Size);
                break;
            }
            
            //Destruction header
            case ESMTag::DEST:
            {
                stream.Skip(header.Size);
                break;
            }
            
            //Destruction stage data
            case ESMTag::DSTD:
            case ESMTag::DMDL:
            case ESMTag::DMDT:
            case ESMTag::DSTF:
            {
                stream.Skip(header.Size);
                break;
            }
            
            default:
                return false;
        }
    }
    
    return true;
}

void StaticObject::ExportYAML(int tablevel, std::ostream& stream) const {
    ESMUtility::EmitTabs(tablevel, stream) << "- form:  " << mFormID << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  edid:  " << mEditorID << std::endl;
    
    if (mType == StaticObjectType::Furniture) {
        ESMUtility::EmitTabs(tablevel, stream) << "  full:  " << mFullName << std::endl;
        ESMUtility::EmitTabs(tablevel, stream) << "  scpt:  " << mScriptID << std::endl;
    }
    
    ESMUtility::EmitTabs(tablevel, stream) << "  lwrb:  " << mBounds.Lower.X << "," << mBounds.Lower.Y << "," << mBounds.Lower.Z << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  uprb:  " << mBounds.Upper.X << "," << mBounds.Upper.Y << "," << mBounds.Upper.Z << std::endl;
    
    ESMUtility::EmitTabs(tablevel, stream) << "  model: " << std::endl;
    
    for(auto itr = mModelData.begin(); itr != mModelData.end(); ++itr) {
        (*itr).ExportYAML(tablevel + 1, stream);
    }
    
    stream << std::endl;
}