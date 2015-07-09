#pragma once

namespace ESM
{
    class Worldspace {
        friend class FalloutESM;
        
    public:
        Worldspace(FormIdentifier id);
        ~Worldspace();
        
        bool Parse(ESMStream& stream);
        
        void ExportXML(std::ostream& output) const;
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
    private:
        FormIdentifier mFormID;
        std::string mEditorID;
        std::string mFullName;
        std::string mLargeIconFile;
        std::string mSmallIconFile;
        std::string mCanopyShadowFile;
        std::string mWaterNoiseTextureFile;
        
        FormIdentifier mEncounterZoneID;
        FormIdentifier mParentWorldspaceID;
        FormIdentifier mClimateID;
        FormIdentifier mWaterID;
        FormIdentifier mLODWaterType;
        FormIdentifier mImageSpaceID;
        FormIdentifier mMusicID;
        
        LandDataField mLandData;
        MapDataField mMapData;
        WorldMapOffsetField mWorldMapOffset;
        
        ObjectBoundsField mMinBounds;
        ObjectBoundsField mMaxBounds;
        
        IMPSField mImpactData;
        IMPFField mFootstepData;
        
        std::vector<uint32_t> mOffsetData;
        std::vector<FormIdentifier> mCells;
        
        float mLODWaterHeight;
        uint16_t mParentFlags;
        uint8_t mFlags;
        
        inline std::vector<FormIdentifier>& GetCellsWritable() {
            return mCells;
        }
    };
}