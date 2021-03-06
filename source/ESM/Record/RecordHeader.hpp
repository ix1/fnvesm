#pragma once

namespace ESM 
{
    enum class GroupType : uint32_t {
        Record = 0,
        WorldChildren = 1,
        InteriorCellBlock = 2,
        InteriorCellSubBlock = 3,
        ExteriorCellBlock = 4,
        ExteriorCellSubBlock = 5,
        CellChildren = 6,
        DialogueChildren = 7,
        CellPersistentChildren = 8,
        CellTemporaryChildren = 9,
        CellVisibleDistantChildren = 10
    };
    
    enum class GlobalRecordFlag : uint32_t {
        Deleted = 0x20,
        Disabled = 0x800,
        Ignored = 0x1000,
        Compressed = 0x40000
    };
    
#pragma pack(push, 1)

    struct RecordHeader {
        ESMTag Tag;
        uint32_t Size;
        
        union {
            struct {
                union {
                    ESMTag AsRecord;
                    FormIdentifier AsFormIdentifier;
                    uint32_t AsCellBlockNumber;
                    struct {
                        int8_t Y;
                        int8_t X;
                    } AsExteriorCellNumber;
                } Label;
                
                GroupType Type;
                uint16_t Datestamp;
                uint8_t Unknown[6];
            } AsGroup;
            
            struct {
                uint32_t Flags;
                FormIdentifier FormID;
                uint32_t Revision;
                uint16_t Version;
                uint16_t Unknown;
            } AsRecord;
        } Meta;
    };
    
    struct FieldHeader {
        ESMTag Tag;
        uint16_t Size;
    };
#pragma pack(pop)
}