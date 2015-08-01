#pragma once

namespace ESM
{
    enum class StaticObjectType {
        Static = 0,
        Furniture,
        Tree,
        Activator
    };

    std::string StaticObjectTypeName(StaticObjectType type);
    
    class StaticObject {
    public:
        StaticObject(StaticObjectType type, FormIdentifier id);
        ~StaticObject();
        
        bool Parse(ESMStream& stream);
        
        void ExportYAML(int tablevel, std::ostream& stream) const;
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
    private:
        StaticObjectType mType;
        FormIdentifier mFormID;
        std::string mEditorID;
        std::string mFullName;
        OBNDField mBounds;
        std::vector<ModelData> mModelData;
        FormIdentifier mSoundID;
        FormIdentifier mScriptID;
        int8_t mBrushPassthroughSound;
    };
}