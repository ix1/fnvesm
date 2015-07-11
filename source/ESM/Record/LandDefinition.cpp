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
        
        switch(header.Tag) {
            case ESMTag::VHGT:
                if (header.Size != (sizeof(mHeightmap.Height) + sizeof(float) + 3))
                    return false;
                
                FieldParser::ParseFloatField(stream, 4, mHeightmap.Offset);
                stream.ReadRaw(mHeightmap.Height, sizeof(mHeightmap.Height));
                stream.Skip(3);
                break;
                
            default:
                stream.Skip(header.Size);
                break;
        }
    }
    return true;
}