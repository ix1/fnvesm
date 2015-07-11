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
        
        void ExportYAML(int tablevel, std::ostream& stream) const;
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
        inline const std::string& GetEditorID() const {
            return mEditorID;
        }
        
        inline const std::string& GetFullName() const {
            return mFullName;
        }
        
        inline bool IsInterior() const {
            return mLocationType == CellLocationType::Internal;
        }
        
        inline CellFlag GetFlags() const {
            return mFlags;
        }
        
        inline const std::list<WorldObject> GetObjects() const {
            return mObjects;
        }
        
    private:
        FormIdentifier mFormID;
        
        //Still unsure as to what these relate to, seemingly random
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
        
        //This appears to be the important location
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
        FormIdentifier mLandscapeID;
        
        uint32_t mLightTemplateFlags;
        uint32_t mFactionRank;
        
        uint8_t mUnknownByte;
        uint8_t mUnusedByte;
        
        void AddObject(CellChildType cellType, WorldObject& object);
        
        inline void SetLandscapeID(FormIdentifier id) {
            mLandscapeID = id;
        }
    };
}