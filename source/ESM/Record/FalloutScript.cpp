#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

FalloutScript::FalloutScript(FormIdentifier id) 
    : mFormID(id)
{
    
}

FalloutScript::~FalloutScript() {
    
}

bool FalloutScript::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        
        stream.ReadFieldHeader(header);
        
        switch(header.Tag) {
            case ESMTag::EDID:
                FieldParser::ParseEDIDField(stream, header.Size, mEditorID);
                break;
                
            case ESMTag::SCHR:
                FieldParser::ParseSCHRField(stream, header.Size, mScriptHeader);
                break;
                
            case ESMTag::SCDA:
                FieldParser::ParseBinaryField(stream, header.Size, mScriptBytecode);
                break;
                
            case ESMTag::SCTX:
                FieldParser::ParseEDIDField(stream, header.Size, mScriptSource);
                break;
                
            case ESMTag::SCVR:
            case ESMTag::SCRV: //TODO: This is undocumented, fixed uint32_t field
            case ESMTag::SCRO:
            case ESMTag::SLSD:
                //TODO: Handle these
                stream.Skip(header.Size);
                break;
                
            default:
                return false;
        }
    }
    
    return true;
} 