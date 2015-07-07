#pragma once

namespace ESM
{
    enum class GameSettingValueType {
        Unknown = 0,
        Integer,
        Float,
        String
    };
    
    class GameSetting {
    public:
        GameSetting(FormIdentifier id);
        ~GameSetting();
        
        bool Parse(ESMStream& stream);
        
        inline const std::string& GetEditorID() const {
            return mKey;
        }
        
        GameSettingValueType GetValueType() const;
        
        std::string GetValueAsString() const;
        int32_t GetValueAsInteger() const;
        float GetValueAsFloat() const;
        
    private:
        FormIdentifier mFormID;
        std::string mKey;
        std::vector<uint8_t> mValue;
    };
}