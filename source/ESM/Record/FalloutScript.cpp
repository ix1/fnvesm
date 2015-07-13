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
                
            case ESMTag::SCRO:
            {
                FormIdentifier id = 0;
                
                FieldParser::ParseFormID(stream, header.Size, id);
                mReferences.push_back(id);
                break;
            }   
            
            case ESMTag::SCVR:
            case ESMTag::SCRV: //TODO: This is undocumented, fixed uint32_t field
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

void FalloutScript::ExportJSON(std::ostream& stream) {
    stream << "{" << std::endl;
    
    stream << "\"edid\": \"" << mEditorID << "\"," << std::endl;
    stream << "\"form\": " << mFormID << "," << std::endl;
    stream << "\"refcount\": " << mScriptHeader.ReferenceCount << "," << std::endl;
    stream << "\"varcount\": " << mScriptHeader.VariableCount << "," << std::endl;
    stream << "\"refs\": [";
    
    for(auto itr = mReferences.begin(); itr != mReferences.end(); ++itr)
        stream << *itr << ", ";
    
    stream << " 0 ];" << std::endl;
    
    stream << "}" << std::endl;
}
