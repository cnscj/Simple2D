/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-28 09:01:01 
 * @Brief: 空服务
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 12:46:04
 * @Last Modified log: 
 */
#ifndef _S2NULLAUDIO_H_
#define _S2NULLAUDIO_H_
#include "S2BaseAudio.h"
class S2NullAudio : public S2BaseAudio
{
public:
  virtual void PlaySound(int soundID);
  virtual void StopSound(int soundID);
  virtual void StopAllSounds();
};
#endif
