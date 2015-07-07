#include "../FNVESM.hpp"
#include "ESMTag.hpp"
#include "Record/Records.hpp"
#include "ESMStream.hpp"
#include "FalloutESM.hpp"
using namespace ESM;

static void ParseGroupHeader(ESMStream& stream, GroupHeader& header);
static void ParseRecordHeader(ESMStream& stream, RecordHeader& header);

FalloutESM::FalloutESM(const std::string& filename)
    : mFile(filename), mFileStream(filename), mBuffer(1024), mIsOpen(false)
{
    Parse();
}

FalloutESM::~FalloutESM() {
    
}

void FalloutESM::Parse() {
    ESMStream primaryStream(mFileStream, mBuffer);
    
    if (ParseHeader(primaryStream) == false) {
        return;
    }
    
    while(primaryStream.IsValid() == true) {
        GroupHeader header;
        
        ParseGroupHeader(primaryStream, header);
        
        if (header.Tag != ESMTag::GRUP) {
            mLoadMessages.push_back("Error: encountered a root node without a GRUP tag. This is invalid.");
            return;
        }
        
        //Note: this will automatically merge with the primary stream once it goes out of scope
        ESMStream substream(primaryStream, header.Size - sizeof(GroupHeader));
        
        switch(header.Label.AsRecord) {
            //Game settings
            case ESMTag::GMST:
            {
                if (ParseGameSettings(substream) == false) {
                    return;
                }
                
                break;
            }
            
            //Texture set definitions
            case ESMTag::TXST:
            {
                if (ParseTextureSets(substream) == false) {
                    return;
                }
                
                break;
            }
            
            //Land textures
            case ESMTag::LTEX:
            {
                if (ParseLandTextureSets(substream) == false) {
                    return;
                }
                
                break;
            }
            
            //Scripts
            case ESMTag::SCPT:
            {
                if (ParseScripts(substream) == false) {
                    return;
                }
                
                break;
            }
            
            case ESMTag::CELL:
            {
                break;
            }
            
            case ESMTag::WRLD:
            {
                break;
            }
                
            default:
                mLoadMessages.push_back("Info: skipping unwanted root node");
                break;
        }
    }
    
    //Done
    mIsOpen = true;
}

bool FalloutESM::ParseHeader(ESMStream& primaryStream) {
    RecordHeader header;
    
    ParseRecordHeader(primaryStream, header);
    
    if (header.Tag != ESMTag::TES4 || header.Size > primaryStream.GetSize()) {
        mLoadMessages.push_back("Error: the opening record was not valid. Expected 'TES4'");
        return false;
    }
    
    ESMStream recordStream(primaryStream, header.Size);
    
    while(recordStream.IsValid() == true) {
        FieldHeader header;
        recordStream.ReadFieldHeader(header);
        
        //TODO: Consume the header data
        switch(header.Tag) {
            case ESMTag::HEDR:  
            case ESMTag::OFST:  
            case ESMTag::CNAM: 
            case ESMTag::SNAM:
            case ESMTag::MAST:
            case ESMTag::DATA:
            case ESMTag::ONAM:
                recordStream.Skip(header.Size);
                break;
                
            default:
                mLoadMessages.push_back("Error: encountered an invalid tag type inside the TES4 header");
                return false;
        }
    }
    
    return true;
}

bool FalloutESM::ParseGameSettings(ESMStream& substream) {
    while(substream.IsValid() == true) {
        RecordHeader record;
        
        ParseRecordHeader(substream, record);
        
        if (record.Tag != ESMTag::GMST) {
            mLoadMessages.push_back("Error: encountered a non-GMST tag in the game settings group");
            return false;
        }
        
        ESMStream recordStream(substream, record.Size);
        GameSetting setting(record.FormID);
        
        if (setting.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: malformed GMST record");
            return false;
        }
        
        mSettings.insert(std::pair<FormIdentifier, GameSetting>(record.FormID, std::move(setting)));
    }
    
    return true;
}

bool FalloutESM::ParseTextureSets(ESMStream& substream) {
    
    while(substream.IsValid() == true) {
        RecordHeader record;
        
        ParseRecordHeader(substream, record);
        
        if (record.Tag != ESMTag::TXST) {
            mLoadMessages.push_back("Error: encountered a non-texture set record in the texture set group");
            return false;
        }
        
        ESMStream recordStream(substream, record.Size);
        TextureSet set(record.FormID);
        
        if (set.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: encountered a malformed texture set record");
            return false;
        }
        
        mTextures.insert(std::pair<FormIdentifier, TextureSet>(record.FormID, std::move(set)));
    }
    
    return true;
}

bool FalloutESM::ParseLandTextureSets(ESMStream& substream) {
    while(substream.IsValid() == true) {
        RecordHeader record;
        
        ParseRecordHeader(substream, record);
        
        if (record.Tag != ESMTag::LTEX) {
            mLoadMessages.push_back("Error: encountered a non-land-texture set record");
            return false;
        }
        
        ESMStream recordStream(substream, record.Size);
        LandscapeTextureSet textureSet(record.FormID);
        
        if (textureSet.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: malformed land-texture set record");
            return false;
        }
        
        mLandTextures.insert(std::pair<FormIdentifier, LandscapeTextureSet>(record.FormID, std::move(textureSet)));
    }
    
    return true;
}

bool FalloutESM::ParseScripts(ESMStream& substream) {
    while(substream.IsValid() == true) {
        RecordHeader record;
        
        ParseRecordHeader(substream, record);
        
        if (record.Tag != ESMTag::SCPT) {
            mLoadMessages.push_back("Error: encountered a non-script record in the script group");
            return false;
        }
        
        ESMStream recordStream(substream, record.Size);
        FalloutScript script(record.FormID);
        
        if (script.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: malformed script record");
            return false;
        }
        
        mScripts.insert(std::pair<FormIdentifier, FalloutScript>(record.FormID, std::move(script)));
    }
    
    return true;
}

bool FalloutESM::ParseCells(ESMStream& substream) {
    while(substream.IsValid() == true) {
        RecordHeader header;
        
        ParseRecordHeader();
    }
}

bool FalloutESM::ParseWorld(ESMStream& substream) {
    
}

void ParseGroupHeader(ESMStream& stream, GroupHeader& header) {
    //FIXME: Not portable.
    stream.ReadRaw(&header, sizeof(header));
}

void ParseRecordHeader(ESMStream& stream, RecordHeader& header) {
    //FIXME: This is not portable.
    stream.ReadRaw(&header, sizeof(header));
}