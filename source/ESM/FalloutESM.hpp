
#pragma once

namespace ESM 
{
    class FalloutESM {
    public:
        FalloutESM(const std::string& filename);
        ~FalloutESM();

        inline bool IsOpen() const {
            return mIsOpen;
        }
        
        inline const std::vector<std::string>& GetLoadMessages() const {
            return mLoadMessages;
        }
        
        inline const std::map<FormIdentifier, GameSetting>& GetGameSettings() const {
            return mSettings;
        }
        
        inline const std::map<FormIdentifier, TextureSet>& GetTextureSets() const {
            return mTextures;
        }
        
        inline const std::map<FormIdentifier, FalloutScript>& GetScripts() const {
            return mScripts;
        }
        
        inline const std::map<FormIdentifier, StaticObject>& GetFurniture() const {
            return mFurniture;
        }

        inline const std::map<FormIdentifier, StaticObject>& GetActivators() const {
            return mActivators;
        }
        
        inline const std::map<FormIdentifier, StaticObject>& GetTrees() const {
            return mTrees;
        }
        
        inline const std::map<FormIdentifier, StaticObject>& GetStaticObjects() const {
            return mStaticObjects;
        }
        
        inline const std::map<FormIdentifier, LandscapeTextureSet>& GetLandscapeTextureSets() const {
            return mLandTextures;
        }
        
        inline const std::map<FormIdentifier, Cell>& GetCells() const {
            return mCells;
        }
        
        inline const std::map<FormIdentifier, Worldspace>& GetWorldspaces() const {
            return mWorldspaces;
        }
        
    protected:
        void Parse();
        
        bool ParseHeader(ESMStream& primaryStream);
        
        bool ParseGameSettings(ESMStream& substream);
        bool ParseTextureSets(ESMStream& substream);
        bool ParseLandTextureSets(ESMStream& substream);
        bool ParseScripts(ESMStream& substream);
        bool ParseFurniture(ESMStream& substream);
        bool ParseActivators(ESMStream& substream);
        bool ParseStatics(ESMStream& substream);
        bool ParseCells(ESMStream& substream);
        bool ParseWorlds(ESMStream& substream);
        bool ParseCellGroup(ESMStream& stream, int block, int subblock);
        
        bool ParseCellInnerGroup(ESMStream& stream, const RecordHeader& header, int block, int subblock);
        bool ParseCellChildrenGroup(ESMStream& stream, const RecordHeader& header, int block, int subblock);
        bool ParseCellChildren(FormIdentifier cellID, CellChildType childType, ESMStream& stream, int block, int subblock);
        
        bool ParseWorldCellGroup(ESMStream& stream, FormIdentifier parentWorld);
        bool ParseWorldInnerGroup(ESMStream& stream, ESM::Worldspace& world, const RecordHeader& header, int x, int y);
        bool ParseCellExteriorGroup(ESMStream& stream, Worldspace& world, int x, int y, bool isblock);
        
    private:
        const std::string& mFile;
        std::ifstream mFileStream;
        std::vector<uint8_t> mBuffer;
        std::vector<uint8_t> mDecompressedBuffer;
        std::vector<std::string> mLoadMessages;
        bool mIsOpen;
        
        //Map form ID to object tag type
        std::map<FormIdentifier, ESMTag> mEntityTypeMap;
        
        std::map<FormIdentifier, GameSetting> mSettings;
        std::map<FormIdentifier, TextureSet> mTextures;
        std::map<FormIdentifier, LandscapeTextureSet> mLandTextures;
        std::map<FormIdentifier, FalloutScript> mScripts;
        
        std::map<FormIdentifier, StaticObject> mFurniture;
        std::map<FormIdentifier, StaticObject> mActivators;
        std::map<FormIdentifier, StaticObject> mTrees;
        std::map<FormIdentifier, StaticObject> mStaticObjects;
        
        std::map<FormIdentifier, Cell> mCells;
        
        std::map<FormIdentifier, LandDefinition> mLandscapes;
        
        std::map<FormIdentifier, Worldspace> mWorldspaces;
    };
}