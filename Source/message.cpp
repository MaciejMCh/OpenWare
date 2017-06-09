#include "message.h"
#include "device.h"
#include "ProgramVector.h"
#include <string.h>

static char buffer[64];
static const char hexnumerals[] = "0123456789abcdef";

#ifndef abs
#define abs(x) ((x)>0?(x):-(x))
#endif /* abs */

char* msg_itoa(int val, int base, int pad){
  static char buf[13] = {0};
  int i = 11;
  unsigned int part = abs(val);
  do{
    buf[i--] = hexnumerals[part % base];
    part /= base;
  }while(i && (--pad > 0 || part));
  if(val < 0)
    buf[i--] = '-';
  return &buf[i+1];
}

char* msg_itoa(int val, int base){
  return msg_itoa(val, base, 0);
}

char* msg_ftoa(float val, int base){
  static char buf[16] = {0};
  int i = 14;
  // print 4 decimal points
  unsigned int part = abs((int)((val-int(val))*10000));
  do{
    buf[i--] = hexnumerals[part % base];
    part /= base;
  }while(i>10);
  buf[i--] = '.';
  part = abs(int(val));
  do{
    buf[i--] = hexnumerals[part % base];
    part /= base;
  }while(part && i);
  if(val < 0.0f)
    buf[i--] = '-';
  return &buf[i+1];
}

void debugMessage(const char* msg){
  if(msg == NULL){
    getProgramVector()->message = NULL;
  }else{
    strlcpy(buffer, msg, 64);
    getProgramVector()->message = buffer;
  }
}

void debugMessage(const char* msg, int a){
  char* p = buffer;
  p = stpncpy(p, msg, 48);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_itoa(a, 10));
  getProgramVector()->message = buffer;
}

void debugMessage(const char* msg, int a, int b){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_itoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_itoa(b, 10));
  getProgramVector()->message = buffer;
}

void debugMessage(const char* msg, int a, int b, int c){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_itoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_itoa(b, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_itoa(c, 10));
  getProgramVector()->message = buffer;
}

void debugMessage(const char* msg, float a){
  char* p = buffer;
  p = stpncpy(p, msg, 48);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_ftoa(a, 10));
  getProgramVector()->message = buffer;
}

void debugMessage(const char* msg, float a, float b){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_ftoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_ftoa(b, 10));
  getProgramVector()->message = buffer;
}

void debugMessage(const char* msg, float a, float b, float c){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_ftoa(a, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_ftoa(b, 10));
  p = stpcpy(p, (const char*)" ");
  p = stpcpy(p, msg_ftoa(c, 10));
  getProgramVector()->message = buffer;
}

// volatile int8_t errorcode = 0;
// static char* errormessage = NULL;
// int8_t getErrorStatus(){
//   return errorcode;
// }

// void setErrorStatus(int8_t err){
//   errorcode = err;
//   if(err == NO_ERROR)
//     errormessage = NULL;
//   // else
//   //   setLed(RED);
// }

// void error(int8_t err, const char* msg){
//   setErrorStatus(err);
//   errormessage = (char*)msg;
// }

// const char* getErrorMessage(){
//   return errormessage;
// }

const char* getDebugMessage(){
  ProgramVector* pv = getProgramVector();
  if(pv != NULL)
    return pv->message;    
  return NULL;
}

void assert_failed(const char* msg, const char* location, int line){
  char* p = buffer;
  p = stpncpy(p, msg, 32);
  p = stpcpy(p, (const char*)" in ");
  p = stpncpy(p, location, 32);
  p = stpcpy(p, (const char*)" line ");
  p = stpcpy(p, msg_itoa(line, 10));
  getProgramVector()->message = buffer;
  if(getProgramVector()->programStatus != NULL)
    getProgramVector()->programStatus(AUDIO_ERROR_STATUS);
}

// void assert_failed(uint8_t* location, uint32_t line){
//   assert_failed("Assertion Failed", (const char*)location, line);
// }
