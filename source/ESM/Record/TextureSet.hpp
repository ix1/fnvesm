#pragma once

namespace ESM
{
    enum class TextureSetFlag : uint16_t {
        NoSpecularMap = 1,
    };
    
    class TextureSet {
    public:
        TextureSet(FormIdentifier id);
        ~TextureSet();
        
        bool Parse(ESMStream& stream);
        
        inline FormIdentifier GetFormID() const {
            return mFormIdentifier;
        }
        
        inline const std::string& GetEditorName() const {
            return mEditorId;
        }
        
        inline const std::vector<std::string>& GetTextureNames() const {
            return mTextureNames;
        }
        
        const TextureSetFlag GetFlags() const {
            return mFlags;
        }
        
    private:
        FormIdentifier mFormIdentifier;
        std::string mEditorId;
        std::vector<std::string> mTextureNames;
        OBNDField mBounds;
        DODTField mDecalData;
        TextureSetFlag mFlags;
    };
    
    class LandscapeTextureSet {
    public:
        LandscapeTextureSet(FormIdentifier id);
        ~LandscapeTextureSet();
        
        bool Parse(ESMStream& stream);
        
    private:
        FormIdentifier mFormIdentifier;
        std::string mEditorId;
        std::string mLargeIconFilename;
        std::string mSmallIconFilename;
        FormIdentifier mTextureIdentifier;
        FormIdentifier mGrassIdentifier;
        
        LandTextureHavokData mHavokData;
        uint8_t mSpecularExponent;
    };
}