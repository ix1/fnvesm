#pragma once

namespace ESM
{
    class LandDefinition {
    public:
        LandDefinition(FormIdentifier id);
        ~LandDefinition();
        
        bool Parse(ESMStream& stream);
        
    private:
        FormIdentifier mFormID;
    };
}