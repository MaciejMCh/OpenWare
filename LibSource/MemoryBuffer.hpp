#include "FloatArray.h"

class AudioBuffer {
public:
    virtual ~AudioBuffer();
    virtual FloatArray getSamples(int channel) = 0;
    virtual int getChannels() = 0;
    virtual int getSize() = 0;
    virtual void clear() = 0;
    static AudioBuffer* create(int channels, int samples);
};

class MemoryBuffer : public AudioBuffer {
protected:
    float* buffer;
    int channels;
    int size;
public:
    MemoryBuffer(float* buf, int ch, int sz): buffer(buf), channels(ch), size(sz) {}
    virtual ~MemoryBuffer(){}
    void clear(){
        memset(buffer, 0, size*channels*sizeof(float));
    }
    FloatArray getSamples(int channel){
        return FloatArray(buffer+channel*size, size);
    }
    int getChannels(){
        return channels;
    }
    int getSize(){
        return size;
    }
};

class ManagedMemoryBuffer : public MemoryBuffer {
public:
    ManagedMemoryBuffer(int ch, int sz) :
    MemoryBuffer(new float[ch*sz], ch, sz) {
//        ASSERT(buffer != NULL, "Memory allocation failed");
    }
    ~ManagedMemoryBuffer(){
        delete buffer;
    }
};
