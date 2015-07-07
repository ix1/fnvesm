
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
        
        inline const std::map<FormIdentifier, LandscapeTextureSet>& GetLandscapeTextureSets() const {
            return mLandTextures;
        }
        
    protected:
        void Parse();
        
        bool ParseHeader(ESMStream& primaryStream);
        
        bool ParseGameSettings(ESMStream& substream);
        bool ParseTextureSets(ESMStream& substream);
        bool ParseLandTextureSets(ESMStream& substream);
        bool ParseScripts(ESMStream& substream);
        bool ParseCells(ESMStream& substream);
        bool ParseWorld(ESMStream& substream);
        
    private:
        const std::string& mFile;
        std::ifstream mFileStream;
        std::vector<uint8_t> mBuffer;
        std::vector<std::string> mLoadMessages;
        bool mIsOpen;
        
        std::map<FormIdentifier, GameSetting> mSettings;
        std::map<FormIdentifier, TextureSet> mTextures;
        std::map<FormIdentifier, LandscapeTextureSet> mLandTextures;
        std::map<FormIdentifier, FalloutScript> mScripts;
    };
}