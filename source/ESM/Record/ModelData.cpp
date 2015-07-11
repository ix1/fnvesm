#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "../ESMUtility.hpp"
#include "FieldParser.hpp"
using namespace ESM;

AlternateModelTexture::AlternateModelTexture(FormIdentifier id, std::string& altName, int32_t altIndex) 
    : AlternateTextureID(id), AlternateTextureName(std::move(altName)), AlternateIndex(altIndex)
{
    
}

ModelData::ModelData(std::string& modelFilename) 
    : mModelFilename(std::move(modelFilename))
{
    
}

ModelData::~ModelData() {
    
}

bool ModelData::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        ESMTag tag = ESMTag::Invalid;
        
        stream.PeekTag(tag);
        
        switch(tag) {
            //Unknown field of fixed length
            case ESMTag::MODB:
            {
                FieldHeader header;
                stream.ReadFieldHeader(header);
                stream.Skip(header.Size);
                break;
            }
            
            //Texture file hashes
            //TODO: Decide if these are needed
            case ESMTag::MODT:
            case ESMTag::MO2T:
            case ESMTag::MO3T:
            case ESMTag::MO4T:
            {
                FieldHeader header;
                stream.ReadFieldHeader(header);
                stream.Skip(header.Size);
                break;
            }
                
            case ESMTag::MODS:
            case ESMTag::MO2S:
            case ESMTag::MO3S:
            case ESMTag::MO4S:
            {
                FieldHeader header;
                stream.ReadFieldHeader(header);
                
                uint32_t count = 0;
                
                stream.Read32(count);
                mAlternateTextures.reserve(count);
                
                for(uint32_t x = 0; x < count; ++x) {
                    uint32_t nameLength = 0;
                    std::string textureName;
                    FormIdentifier alternateID;
                    int32_t index;
                    
                    stream.Read32(nameLength);
                    stream.ReadCString(nameLength, textureName);
                    FieldParser::ParseFormID(stream, 4, alternateID);
                    stream.Read32((uint32_t &)index);
                    
                    mAlternateTextures.push_back(AlternateModelTexture(alternateID, textureName, index));
                }
                
                break;
            }
                
            case ESMTag::MODD:
            case ESMTag::MOSD:
            {
                FieldHeader header;
                stream.ReadFieldHeader(header);
                
                FieldParser::ParseByteValue(stream, header.Size, (uint8_t &)mModelDataFlags);
                break;
            }
            
            default:
                return true;
        }
        
    }
    
    return true;
}

void ModelData::ExportYAML(int tablevel, std::ostream& stream) const {
    ESMUtility::EmitTabs(tablevel, stream) << "- model: " << mModelFilename << std::endl;
}