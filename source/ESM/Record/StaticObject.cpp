#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "../ESMUtility.hpp"
#include "FieldParser.hpp"
#include <iostream>
#include <iomanip>
using namespace ESM;

StaticObject::StaticObject(FormIdentifier id)
    : mFormID(id)
{
    
}

StaticObject::~StaticObject() {
    
}

bool StaticObject::Parse(ESMStream& stream) {
    std::cout << "Parsing static object: " << (uint32_t)mFormID << " at file offset: " << std::hex << stream.GetAbsolutePosition() << std::dec << std::endl;
    
    while(stream.IsValid() == true) {
        FieldHeader header;
        stream.ReadFieldHeader(header);
        
        std::cout << "\tTag: " << ESMUtility::TagToString(header.Tag) << std::endl << "\tSize: " << header.Size << std::endl;
        std::cout << "\tStream local offset: " << stream.GetOffset() << std::endl << "\tStream size: " << stream.GetSize() << std::endl;
        
        switch(header.Tag) {
            case ESMTag::EDID:
            {
                FieldParser::ParseEDIDField(stream, header.Size, mEditorID);
                std::cout << "\tEditor ID: " << mEditorID << std::endl;
                
                break;
            }
            
            case ESMTag::MODL:
            case ESMTag::MOD2:
            case ESMTag::MOD3:
            case ESMTag::MOD4:
            {
                std::string modelName;
                
                if (header.Size + stream.GetOffset() > stream.GetSize()) {
                    std::cout << "\t============= FOUND BAD MOD* FIELD =============" << std::endl;
                    
                    std::cout << "\tOffset: " << stream.GetAbsolutePosition() << std::endl;
                    
                    assert(false && "Halting");
                }
                
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
            
            case ESMTag::RNAM:
            {
                FieldParser::ParseFormID(stream, header.Size, mSoundID);
                break;
            }
            
            default:
                return false;
        }
        
        std::cout << std::endl;
    }
    
    return true;
}

void StaticObject::ExportYAML(int tablevel, std::ostream& stream) const {
    ESMUtility::EmitTabs(tablevel, stream) << "- form:  " << mFormID << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  edid:  " << mEditorID << std::endl;
    ESMUtility::EmitTabs(tablevel, stream) << "  model: " << std::endl;
    
    for(auto itr = mModelData.begin(); itr != mModelData.end(); ++itr) {
        (*itr).ExportYAML(tablevel + 1, stream);
    }
    
    stream << std::endl;
}