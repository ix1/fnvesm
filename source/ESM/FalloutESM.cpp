#include "../FNVESM.hpp"
#include "ESMTag.hpp"
#include "Record/Records.hpp"
#include "ESMStream.hpp"
#include "ESMUtility.hpp"
#include "FalloutESM.hpp"
#include <iostream> //Debugging
using namespace ESM;

//static void ParseGroupHeader(ESMStream& stream, GroupHeader& header);
static void ParseRecordHeader(ESMStream& stream, RecordHeader& header);

FalloutESM::FalloutESM(const std::string& filename)
    : mFile(filename), mFileStream(filename), mBuffer(1024), mIsOpen(false)
{
    Parse();
}

FalloutESM::~FalloutESM() {
    
}

void FalloutESM::Parse() {
    if (mFileStream.is_open() == false) {
        mLoadMessages.push_back("Error: couldn't open the ESM file");
        
        return;
    }
    
    ESMStream primaryStream(mFileStream, mBuffer);
    
    if (ParseHeader(primaryStream) == false) {
        return;
    }
    
    while(primaryStream.IsValid() == true) {
        RecordHeader header;
        
        ParseRecordHeader(primaryStream, header);
        
        if (header.Tag != ESMTag::GRUP) {
            mLoadMessages.push_back("Error: encountered a root node without a GRUP tag.");
            return;
        }
        
        //Note: this will automatically merge with the primary stream once it goes out of scope
        ESMStream substream(primaryStream, header.Size - sizeof(RecordHeader));
        
        switch(header.Meta.AsGroup.Label.AsRecord) {
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
                if (ParseCells(substream) == false) {
                    return;
                }
                
                break;
            }
            
            case ESMTag::WRLD:
            {
                if (ParseWorlds(substream) == false) {
                    return;
                }
                
                break;
            }
                
            default:
                substream.Skip(substream.GetSize());
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
        GameSetting setting(record.Meta.AsRecord.FormID);
        
        if (setting.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: malformed GMST record");
            return false;
        }
        
        mSettings.insert(std::pair<FormIdentifier, GameSetting>(record.Meta.AsRecord.FormID, std::move(setting)));
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
        TextureSet set(record.Meta.AsRecord.FormID);
        
        if (set.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: encountered a malformed texture set record");
            return false;
        }
        
        mTextures.insert(std::pair<FormIdentifier, TextureSet>(record.Meta.AsRecord.FormID, std::move(set)));
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
        LandscapeTextureSet textureSet(record.Meta.AsRecord.FormID);
        
        if (textureSet.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: malformed land-texture set record");
            return false;
        }
        
        mLandTextures.insert(std::pair<FormIdentifier, LandscapeTextureSet>(record.Meta.AsRecord.FormID, std::move(textureSet)));
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
        FalloutScript script(record.Meta.AsRecord.FormID);
        
        if (script.Parse(recordStream) == false) {
            mLoadMessages.push_back("Error: malformed script record");
            return false;
        }
        
        mScripts.insert(std::pair<FormIdentifier, FalloutScript>(record.Meta.AsRecord.FormID, std::move(script)));
    }
    
    return true;
}

bool FalloutESM::ParseCells(ESMStream& substream) {
    while(substream.IsValid() == true) {
        RecordHeader header;
        
        ParseRecordHeader(substream, header);
        
        if (header.Tag != ESMTag::GRUP) {
            mLoadMessages.push_back("Error: found a non-group record in the top level cell structure");
            return false;
        }
        
        //These are all groups of type 2 (interior cell block)
        ESMStream groupStream(substream, header.Size - sizeof(RecordHeader));
        
        if (ParseCellGroup(substream, -1, -1) == false) {            
            return false;
        }
    }
    
    std::cout << "Loaded " << mCells.size() << " cells." << std::endl;
    
    return true;
}

bool FalloutESM::ParseWorlds(ESMStream& substream) {
    while(substream.IsValid() == true) {
        RecordHeader header;
        
        ParseRecordHeader(substream, header);
        
        std::cout << "Top level world tag: " << ESMUtility::TagToString(header.Tag) << " with size " << header.Size << std::endl;
        
        switch(header.Tag) {
            case ESMTag::GRUP:
            {
                ESMStream groupStream(substream, header.Size - sizeof(RecordHeader));
                
                if (ParseCellGroup(groupStream, -1, -1) == true) {
                    //ParseCellInnerGroup adds the error message
                    return false;
                }
                
                //groupStream.Skip(groupStream.GetSize());
                break;
            }
            
            case ESMTag::WRLD:
            {
                ESMStream worldStream(substream, header.Size);
                
                Worldspace world(header.Meta.AsRecord.FormID);
                
                if (world.Parse(worldStream) == false) {
                    mLoadMessages.push_back("Error: invalid world record");
                    return false;
                }
                
                mWorldspaces.insert(std::pair<FormIdentifier, Worldspace>(header.Meta.AsRecord.FormID, std::move(world)));
                break;
            }
            
            default:
                return false;
        }
        
    }
    
    return true;
}

bool FalloutESM::ParseCellGroup(ESMStream& stream, int block, int subblock) {
    while(stream.IsValid() == true) {
        RecordHeader header;
        
        ParseRecordHeader(stream, header);
        
        switch(header.Tag) {
            case ESMTag::GRUP:
            {
                if (ParseCellInnerGroup(stream, header, block, subblock) == false) {
                    return false;
                }
                
                break;
            }
            
            case ESMTag::CELL:
            {
                ESMStream cellStream(stream, header.Size);
                
                Cell cell(header.Meta.AsRecord.FormID, block, subblock);
                
                if (cell.Parse(cellStream) == false) {
                    mLoadMessages.push_back("Error: invalid cell record");
                    return false;
                }
                
                mCells.insert(std::pair<FormIdentifier, Cell>(header.Meta.AsRecord.FormID, std::move(cell)));
                break;
            }
            
            default:
                return false;
        }
    }
    
    return true;
}

bool FalloutESM::ParseCellInnerGroup(ESMStream& stream, const RecordHeader& header, int block, int subblock) {
    ESMStream groupStream(stream, header.Size - sizeof(RecordHeader));
    
    switch(header.Meta.AsGroup.Type) {
        case GroupType::WorldChildren:
            //TODO
            break;
            
        case GroupType::InteriorCellBlock:
            return ParseCellGroup(groupStream, header.Meta.AsGroup.Label.AsCellBlockNumber, -1);
            
        case GroupType::InteriorCellSubBlock:
            return ParseCellGroup(groupStream, block, header.Meta.AsGroup.Label.AsCellBlockNumber);
            
        case GroupType::ExteriorCellBlock:
            //TODO
            break;
            
        case GroupType::ExteriorCellSubBlock:
            //TODO
            break;
            
        case GroupType::CellChildren:
            return ParseCellChildren(header.Meta.AsGroup.Label.AsFormIdentifier, CellChildType::Direct, groupStream, block, subblock);
            
        case GroupType::CellPersistentChildren:
            return ParseCellChildren(header.Meta.AsGroup.Label.AsFormIdentifier, CellChildType::Persistent, groupStream, block, subblock);
            
        case GroupType::CellTemporaryChildren:
            return ParseCellChildren(header.Meta.AsGroup.Label.AsFormIdentifier, CellChildType::Temporary, groupStream, block, subblock);
            
        case GroupType::CellVisibleDistantChildren:
            return ParseCellChildren(header.Meta.AsGroup.Label.AsFormIdentifier, CellChildType::Distant, groupStream, block, subblock);
        
        default:
            mLoadMessages.push_back("Error: invalid group type for a cell child");
            return false;
    }
    
    return true;
}

bool FalloutESM::ParseCellChildren(FormIdentifier cellID, CellChildType childType, ESMStream& stream, int block, int subblock) {
    auto cellItr = mCells.find(cellID);
    // = mCells[cellID];
    
    if (cellItr == mCells.end()) {
        mLoadMessages.push_back("Error: tried to add children for a non-existent cell");
        return false;
    }
    
    Cell& cell = (*cellItr).second;
    
    while(stream.IsValid() == true) {
        RecordHeader header;
        
        ParseRecordHeader(stream, header);
        
        switch(header.Tag) {
            case ESMTag::REFR: 
            {
                ESMStream substream(stream, header.Size);
                WorldObject obj(WorldObjectType::Static, header.Meta.AsRecord.FormID);
                
                if (obj.Parse(substream) == false) {
                    mLoadMessages.push_back("Error: invalid REFR record");
                    return false;
                }
                
                cell.AddObject(childType, obj);
                break;
            }
            
            case ESMTag::ACRE:
            {
                ESMStream substream(stream, header.Size);
                WorldObject obj(WorldObjectType::Creature, header.Meta.AsRecord.FormID);
                
                if (obj.Parse(substream) == false) {
                    mLoadMessages.push_back("Error: invalid ACRE record");
                    return false;
                }
                
                cell.AddObject(childType,obj);
                break;
            }
                
            case ESMTag::PGRE:
            {
                ESMStream substream(stream, header.Size);
                substream.Skip(substream.GetSize());
                break;
            }
                
            case ESMTag::PMIS:
            {
                ESMStream substream(stream, header.Size);
                substream.Skip(substream.GetSize());
                break;
            }
                
            case ESMTag::ACHR:
            {
                ESMStream substream(stream, header.Size);
                WorldObject obj(WorldObjectType::Character, header.Meta.AsRecord.FormID);
                
                if (obj.Parse(substream) == false) {
                    mLoadMessages.push_back("Error: invalid ACHR record");
                    return false;
                }
                
                cell.AddObject(childType, obj);
                break;
            }
                
            case ESMTag::GRUP:
            {
                if (ParseCellInnerGroup(stream, header, block, subblock) == false) {
                    return false;
                }
                
                break;
            }
                
            case ESMTag::NAVM:
            {
                ESMStream substream(stream, header.Size);
                
                substream.Skip(substream.GetSize());
                break;
            }
                
            default:
                std::cout << "Found unhandled tag: " << ESMUtility::TagToString(header.Tag) << " " << header.Size << std::endl;
                break;
        }
        
        
    }
    
    return true;
}

void ParseRecordHeader(ESMStream& stream, RecordHeader& header) {
    //FIXME: This is not portable.
    stream.ReadRaw(&header, sizeof(header));
}