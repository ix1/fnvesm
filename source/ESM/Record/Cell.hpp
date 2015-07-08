#pragma once

namespace ESM
{
    enum class CellLocationType {
        Internal = 0,
        External
    };
    
    enum class CellFlag : uint8_t {
        Interior = 0x01,
        Water = 0x02,
        NoFastTravel = 0x04,
        NoWaterLOD = 0x08,
        PublicArea = 0x20,
        HandChanged = 0x40,
        MasqueradeExterior = 0x80
    };
    
    enum class CellChildType {
        Direct = 0,
        Persistent,
        Temporary,
        Distant,
    };
    
    class Cell {
        friend class FalloutESM;
        
    public:
        Cell(FormIdentifier id, int block, int subblock);
        Cell(FormIdentifier id, int x, int y, bool isblock);
        ~Cell();
        
        bool Parse(ESMStream& stream);
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
        inline const std::string& GetEditorID() const {
            return mEditorID;
        }
        
        inline const std::string& GetFullName() const {
            return mFullName;
        }
        
        inline CellFlag GetFlags() const {
            return mFlags;
        }
        
        inline const std::list<WorldObject> GetObjects() const {
            return mObjects;
        }
        
    private:
        FormIdentifier mFormID;
        
        union {
            struct {
                int Block;
                int Subblock;
            } AsInterior;
            
            struct {
                int X;
                int Y;
            } AsExterior;
        } mCellBlockLocation;
        
        CellLocationType mLocationType;
        
        std::string mEditorID;
        std::string mFullName;
        CellFlag mFlags;
        
        XCLCField mCellLocation;
        XCLLField mLighting;
        IMPFField mFootstepMaterial;
        
        float mWaterHeight;
        std::string mWaterNoiseTexture;
        
       
        std::vector<FormIdentifier> mRegionIdentifiers;
        
        std::list<WorldObject> mObjects;
        std::list<WorldObject> mTemporaryObjects;
        std::list<WorldObject> mDistantObjects;
        
        FormIdentifier mLightTemplateID;
        FormIdentifier mImageSpaceID;
        FormIdentifier mEncounterZoneID;
        FormIdentifier mClimateID;
        FormIdentifier mWaterID;
        FormIdentifier mOwnerID;
        FormIdentifier mAcousticSpaceID;
        FormIdentifier mMusicID;
        
        uint32_t mLightTemplateFlags;
        uint32_t mFactionRank;
        
        uint8_t mUnknownByte;
        uint8_t mUnusedByte;
        
        void AddObject(CellChildType cellType, WorldObject& object);
    };
}