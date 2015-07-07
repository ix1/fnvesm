#include "../FNVESM.hpp"
#include "ESMTag.hpp"
#include "Record/Records.hpp"
#include "ESMStream.hpp"
using namespace ESM;

ESMStream::ESMStream(std::ifstream& stream, std::vector<uint8_t>& buffer) 
    : mStream(stream), mBuffer(buffer), mParent(*this), mOffset(0)
{
    stream.seekg(0, std::ios::end);
    
    mLocalSize = (size_t)stream.tellg();
    
    stream.seekg(0, std::ios::beg);
}

ESMStream::ESMStream(ESMStream& parent, size_t localSize) 
    : mStream(parent.mStream), mBuffer(parent.mBuffer), mParent(parent), mLocalSize(localSize), mOffset(0)
{
    
}

ESMStream::~ESMStream() {
    if (this != &mParent) {
        mParent.Merge(*this);
    }
}