/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-28 13:56:26 
 * @Brief: 全局音效
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 12:45:50
 * @Last Modified log: 
 */
#ifndef _S2GLOBALAUDIO_H_
#define _S2GLOBALAUDIO_H_
#include "S2BaseAudio.h"
class S2GlobalAudio : public S2BaseAudio
{
public:
  virtual void PlaySound(int soundID);
  virtual void StopSound(int soundID);
  virtual void StopAllSounds();
};
#endif
