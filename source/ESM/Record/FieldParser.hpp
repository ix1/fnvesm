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
    
    enum class LandHideFlag : uint32_t {
        None = 0,
        FirstQuadrant = 1,
        SecondQuadrant = 2,
        ThirdQuadrant = 4,
        FourthQuadrant = 8
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
    
    struct XCLCField {
        int32_t X;
        int32_t Y;
        LandHideFlag LandHideFlags; //FIXME: documented but doesn't exist in the FNV master
    };
    
    struct XCLLField {
        uint32_t AmbientColour;
        uint32_t DirectionalColour;
        uint32_t FogColour;
        float FogNear;
        float FogFar;
        int32_t DirectionalRotationXY;
        int32_t DirectionalRotationZ;
        float DirectionalFade;
        float FogDistance;
        float FogPower;
    };
    
    //TODO: The structre of the inner fields are unknown
    struct IMPFField {
        uint8_t ConcreteSolid[30];
        uint8_t ConcreteBroken[30];
        uint8_t MetalSolid[30];
        uint8_t MetalHollow[30];
        uint8_t MetalSheet[30];
        uint8_t Wood[30];
        uint8_t Sand[30];
        uint8_t Dirt[30];
        uint8_t Grass[30];
        uint8_t Water[30];
    };
    
    struct LandDataField {
        float LandHeight;
        float WaterHeight;
    };
    
    struct MapDataField {
        int32_t XSize;
        int32_t YSize;
        
        struct {
            int16_t X;
            int16_t Y;
        } NorthWestCorner;
        
        struct {
            int16_t X;
            int16_t Y;
        } SouthEastCorner;
    };
    
    struct WorldMapOffsetField {
        float MapScale;
        float CellX;
        float CellY;
    };
    
    struct ObjectBoundsField {
        float X;
        float Y;
    };
    
    struct IMPSField {
        uint32_t MaterialType;
        FormIdentifier OldIPCTID;
        FormIdentifier NewIPCTID;
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
        static bool ParseXCLCField(ESMStream& stream, uint16_t length, XCLCField& outField);
        static bool ParseXCLLField(ESMStream& stream, uint16_t length, XCLLField& outField);
        static bool ParseIMPFField(ESMStream& stream, uint16_t length, IMPFField& outField);
        static bool ParseFloatField(ESMStream& stream, uint16_t length, float& outValue);
        static bool ParseUint32Field(ESMStream& stream, uint16_t length, uint32_t& outValue);
        static bool ParseUint16Field(ESMStream& stream, uint16_t length, uint16_t& outValue);
        static bool ParseLandDataField(ESMStream& stream, uint16_t length, LandDataField& outField);
        static bool ParseMapDataField(ESMStream& stream, uint16_t length, MapDataField& outField);
        static bool ParseWorldMapOffsetField(ESMStream& stream, uint16_t length, WorldMapOffsetField& outField);
        static bool ParseObjectBoundsField(ESMStream& stream, uint16_t length, ObjectBoundsField& outField);
        static bool ParseIMPSField(ESMStream& stream, uint16_t length, IMPSField& outField);
        static bool ParseOFSTField(ESMStream& stream, uint32_t length, std::vector<uint32_t>& outValue);
        static bool ParseVector3Field(ESMStream& stream, uint16_t length, Vector3F& outVector);
    };
}