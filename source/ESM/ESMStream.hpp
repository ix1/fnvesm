#pragma once

namespace ESM
{    
    class ESMStream {
    public:
        ESMStream(std::istream& stream, std::vector<uint8_t>& buffer);
        ESMStream(ESMStream& parent, size_t localSize);
        
        // Used for decompression only - does not merge with the parent!
        ESMStream(ESMStream& base, std::istream& source, size_t size);
        ~ESMStream();
        
        inline ESMStream& operator=(const ESMStream & rhs) {
            mOffset = rhs.mOffset;
            mLocalSize = rhs.mLocalSize;
            
            return *this;
        }
        
        inline void Skip(size_t length) {
            if (mOffset + length <= mLocalSize) {
                mStream.seekg(length, std::ios::cur);
            } else {
                assert(mOffset + length <= mLocalSize);
            }
            
            mOffset += length;
        }
        
        inline void ReadTag(ESMTag& tag) {
            if (mOffset + sizeof(tag) <= mLocalSize) {
                mStream.read((char *)&tag, sizeof(tag));
            } else {
                assert(mOffset + sizeof(tag) <= mLocalSize);
                tag = ESMTag::Invalid;
            }
            
            mOffset += sizeof(tag);
        }
        
        inline void Read16(uint16_t& value) {
            if (mOffset + sizeof(value) <= mLocalSize) {
                mStream.read((char *)&value, sizeof(value));
            } else {
                assert(mOffset + sizeof(value) <= mLocalSize);
                value = 0;
            }
            
            mOffset += sizeof(value);
        }
        
        inline void Read32(uint32_t& value) {
            if (mOffset + sizeof(value) <= mLocalSize) {
                mStream.read((char *)&value, sizeof(value));
            } else {
                assert(mOffset + sizeof(value) <= mLocalSize);
                value = 0;
            }
            
            mOffset += sizeof(value);
        }
        
        inline void Read(std::vector<uint8_t>& value) {
            if (mOffset + value.size() <= mLocalSize) {
                mStream.read((char *)&value[0], value.size());
            } else {
                assert(mOffset + value.size() <= mLocalSize);
            }
            
            mOffset += value.size();
        }
        
        inline void ReadRaw(void *buffer, size_t length) {
            if (mOffset + length <= mLocalSize) {
                mStream.read((char *)buffer, length);
            } else {
                assert(mOffset + length <= mLocalSize);
            }
            
            mOffset += length;
        }
        
        inline void ReadCString(size_t length, std::string& outValue) {
            if (mOffset + length <= mLocalSize) {
                mBuffer.reserve(length);
                mStream.read((char *)&mBuffer[0], length);
                
                if (mBuffer[length - 1] != 0) {
                    mBuffer[length - 1] = 0;
                }
                
                outValue = std::string((const char *)&mBuffer[0]);
            } else {
                assert(mOffset + length <= mLocalSize);
            }
            
            mOffset += length;
        }
        
        inline void PeekTag(ESMTag& tag) {
            if (mOffset + sizeof(tag) <= mLocalSize) {
                std::streamoff originalPosition = mStream.tellg();
                mStream.read((char *)&tag, sizeof(tag));
                mStream.seekg(originalPosition, std::ios::beg);
            } else {
                assert(mOffset + sizeof(tag) <= mLocalSize);
                tag = ESMTag::Invalid;
            }
        }
        
        inline void ReadFieldHeader(FieldHeader& header) {
            ReadRaw(&header, sizeof(header));
        }
                
        inline bool IsValid() const {
            return mOffset < mLocalSize;
        }
        
        inline size_t GetSize() const {
            return mLocalSize;
        }
        
        inline size_t GetOffset() const {
            return mOffset;
        }
        
        inline std::streamoff GetAbsolutePosition() const {
            return mStream.tellg();
        }
        
    private:
        std::istream& mStream;
        std::vector<uint8_t>& mBuffer;
        ESMStream& mParent;
        size_t mLocalSize;
        size_t mOffset;
        
        inline void Merge(const ESMStream& child) {
            mOffset += child.mLocalSize;
        }
    };
}