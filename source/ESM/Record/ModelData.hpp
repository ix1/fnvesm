#pragma once

namespace ESM
{
    enum class ModelDataFlag {
        Head = 1,
        Torso = 2,
        RightHand = 4,
        LeftHand = 8
    };
    
    struct AlternateModelTexture {
        FormIdentifier AlternateTextureID;
        std::string AlternateTextureName;
        int32_t AlternateIndex;
        
        AlternateModelTexture(FormIdentifier id, std::string& altName, int32_t altIndex);
    };
    
    class ModelData {
    public:
        ModelData(std::string& modelFilename);
        ~ModelData();
        
        bool Parse(ESMStream& stream);
        
        void ExportYAML(int tablevel, std::ostream& stream) const;
        
    private:
        std::string mModelFilename;
        std::vector<AlternateModelTexture> mAlternateTextures;
        
        ModelDataFlag mModelDataFlags;
        
    };
}