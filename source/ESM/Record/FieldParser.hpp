#pragma once

namespace ESM
{
    enum class DODTFlag : uint8_t {
        Parallax = 1,
        AlphaBlend = 2,
        AlphaTest = 4
    };
    
    enum class ScriptTypeValue : uint16_t {
        Object = 0,
        Quest = 1,
        Effect = 256
    };
    
    enum class HavokMaterialType : uint8_t {
        Stone = 0,
        Cloth,
        Dirt,
        Glass,
        Grass,
        Metal,
        Organic,
        Skin,
        Water,
        Wood,
        HeavyStone,
        HeavyMetal,
        HeavyWood,
        Chain,
        Snow,
        Elevator,
        HollowMetal,
        SheetMetal,
        Sand,
        BrokenConcrete,
        VehicleBody,
        VehiclePartSolid,
        VehiclePartHollow,
        Barrel,
        Bottle,
        SodaCan,
        Pistol,
        Rifle,
        ShoppingCart,
        Lunchbox,
        BabyRattle,
        RubberBall
    };
    
#pragma pack(push, 1)
    struct OBNDField {
        struct {
            int16_t X;
            int16_t Y;
            int16_t Z;
        } Lower, Upper; //TODO: These need better names
    };
    
    struct DODTField {
        float MinWidth;
        float MaxWidth;
        float MinHeight;
        float MaxHeight;
        
        float Depth;
        float Shininess;
        float ParallaxScale;
        uint8_t ParallaxPasses;
        
        DODTFlag Flags;
        uint8_t Unused[2];
        
        uint32_t Colour; //TODO: Use a proper type for this
    };
    
    struct SCHRField {
        uint32_t Unused;
        uint32_t ReferenceCount;
        uint32_t CompiledSize;
        uint32_t VariableCount;
        ScriptTypeValue Type;
        uint16_t Flags;
    };
    
    struct LandTextureHavokData {
        HavokMaterialType Type;
        uint8_t Friction;
        uint8_t Restitution;
    };
#pragma pack(pop)
    
    class FieldParser {
    public:
        static bool ParseFormID(ESMStream& stream, uint16_t length, FormIdentifier& outValue);
        static bool ParseEDIDField(ESMStream& stream, uint16_t length, std::string& outValue);
        static bool ParseTXNNField(ESMStream& stream, uint16_t length, std::string& outValue);
        static bool ParseOBDNField(ESMStream& stream, uint16_t length, OBNDField& outField);
        static bool ParseDODTField(ESMStream& stream, uint16_t length, DODTField& outField);
        static bool ParseSCHRField(ESMStream& stream, uint16_t length, SCHRField& outField);
        static bool ParseBinaryField(ESMStream& stream, uint16_t length, std::vector<uint8_t>& outVector);
        static bool ParseHavokData(ESMStream& stream, uint16_t length, LandTextureHavokData& havokData);
        static bool ParseByteValue(ESMStream& stream, uint16_t length, uint8_t& outValue);
    };
}