#pragma once

namespace ESM
{
    struct LandHeightmap {
        float Offset;
        uint8_t Height[33][33];
    };
    
    class LandDefinition {
    public:
        LandDefinition(FormIdentifier id);
        ~LandDefinition();
        
        bool Parse(ESMStream& stream);
        
        inline const LandHeightmap& GetHeightmap() const {
            return mHeightmap;
        }
        
    private:
        FormIdentifier mFormID;
        
        LandHeightmap mHeightmap;
    };
}