#include "../../FNVESM.hpp"
#include "../ESMTag.hpp"
#include "../Record/Records.hpp"
#include "../ESMStream.hpp"
#include "FieldParser.hpp"
using namespace ESM;

LandDefinition::LandDefinition(FormIdentifier id) 
    : mFormID(id)
{
    
}

LandDefinition::~LandDefinition() {
    
}

bool LandDefinition::Parse(ESMStream& stream) {
    while(stream.IsValid() == true) {
        FieldHeader header;
        
        stream.ReadFieldHeader(header);
        
        stream.Skip(header.Size);
        
        switch(header.Tag) {
            default:
                break;
        }
    }
    return true;
}