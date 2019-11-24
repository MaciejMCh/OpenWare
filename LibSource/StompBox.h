#ifndef __StompBox_h__
#define __StompBox_h__

#include "basicmaths.h"
#include "FloatArray.h"
#include "MemoryBuffer.hpp"
#include <iostream>


static void ASSERT(bool condition, char *message) {
    if (!condition) {
        std::cout << message;
        exit(-1234);
    }
}

class PatchProcessor;

enum PatchParameterId {
  PARAMETER_A,
  PARAMETER_B,
  PARAMETER_C,
  PARAMETER_D,
  PARAMETER_E,
  PARAMETER_F
};

enum PatchButtonId {
  BYPASS_BUTTON = 0,
  PUSHBUTTON,
  GREEN_BUTTON,
  RED_BUTTON
};

enum PatchChannelId {
  LEFT_CHANNEL = 0,
  RIGHT_CHANNEL = 1
};

class Patch {
public:
  Patch();
  virtual ~Patch();
//  void registerParameter(PatchParameterId pid, const char* name, const char* description = "");
//  float getParameterValue(PatchParameterId pid);
//  bool isButtonPressed(PatchButtonId bid);
//  int getSamplesSinceButtonPressed(PatchButtonId bid);
//  void setButton(PatchButtonId bid, bool pressed);
  int getBlockSize();
  double getSampleRate();
  AudioBuffer* createMemoryBuffer(int channels, int samples);
//  float getElapsedBlockTime();
//  int getElapsedCycles();
public:
  virtual void reset(){};
  virtual void encoderChanged(PatchParameterId pid, int32_t dir, uint16_t samples){};
  /* virtual void processScreen(ScreenBuffer&) = 0; */
  virtual void processAudio(AudioBuffer&) = 0;
  /* virtual void encoderChanged(PatchParameterId pid, int16_t delta, uint16_t samples){}; */
  virtual void buttonChanged(PatchButtonId bid, uint16_t value, uint16_t samples){}
private:
  PatchProcessor* processor;
};

#endif // __StompBox_h__
