#pragma once

namespace ESM
{
    class StaticObject {
    public:
        StaticObject(FormIdentifier id);
        ~StaticObject();
        
        bool Parse(ESMStream& stream);
        
        void ExportYAML(int tablevel, std::ostream& stream) const;
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
    private:
        FormIdentifier mFormID;
        std::string mEditorID;
        OBNDField mBounds;
        std::vector<ModelData> mModelData;
        FormIdentifier mSoundID;
        int8_t mBrushPassthroughSound;
    };
}