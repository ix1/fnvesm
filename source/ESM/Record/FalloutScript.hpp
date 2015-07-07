#pragma once

namespace ESM
{
    class FalloutScript {
    public:
        FalloutScript(FormIdentifier id);
        ~FalloutScript();
        
        bool Parse(ESMStream& stream);
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
        inline const std::string& GetEditorID() const {
            return mEditorID;
        }
        
        inline const std::string& GetScriptSource() const {
            return mScriptSource;
        }
        
        inline const std::vector<uint8_t>& GetScriptByteCode() const {
            return mScriptBytecode;
        }
        
        inline uint32_t GetVariableCount() const {
            return mScriptHeader.VariableCount;
        }
        
    private:
        FormIdentifier mFormID;
        std::string mEditorID;
        std::string mScriptSource;
        std::vector<uint8_t> mScriptBytecode;
        SCHRField mScriptHeader;
        
    };
}