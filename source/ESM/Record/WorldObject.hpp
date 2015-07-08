#pragma once

namespace ESM
{
    enum class WorldObjectType {
        Static = 0,
        Creature,
        Character
    };
    
    class WorldObject {
    public:
        WorldObject(WorldObjectType type, FormIdentifier id);
        ~WorldObject();
        
        bool Parse(ESMStream& stream);
        
        inline WorldObjectType GetType() const {
            return mType;
        }
        
        inline FormIdentifier GetFormID() const {
            return mFormID;
        }
        
        inline const std::string& GetEditorID() const {
            return mEditorID;
        }
        
        inline const Vector3F& GetPosition() const {
            return mPosition;
        }
        
        inline const Vector3F& GetRotation() const {
            return mRotation;
        }
        
        const std::string& GetTypeName() const;
        
    private:
        WorldObjectType mType;
        FormIdentifier mFormID;
        std::string mEditorID;
        std::string mMapMarkerName;

        FormIdentifier mBaseID;
        FormIdentifier mEncounterZoneID;
        FormIdentifier mMapMarkerReputationID;
        FormIdentifier mAudioLocationID;
        FormIdentifier mIdleID;
        FormIdentifier mTargetID;
        FormIdentifier mTopicID;
        FormIdentifier mAmmoTypeID;
        FormIdentifier mLitWaterID;
        
        Vector3F mPosition;
        Vector3F mRotation;
        
        float mScale;
        
        uint8_t mMapMarkerFlags;
    };
}