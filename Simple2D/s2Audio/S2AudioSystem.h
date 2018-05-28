/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-04-28 09:00:30 
 * @Brief: 音频系统
 * @Last Modified by: cnscj
 * @Last Modified time: 2018-05-26 12:45:15
 * @Last Modified log: 
 */
#ifndef _S2AUDIOSYSTEM_H_
#define _S2AUDIOSYSTEM_H_
#include "../s2Core/S2Singleton.hpp"
#include "S2NullAudio.h"
class S2BaseAudio;
class S2AudioSystem : public S2Singleton<S2AudioSystem>
{
public:
    S2BaseAudio *GetAudio() const;

    void Provide(S2BaseAudio *pService);
protected:
  S2AudioSystem();
  ~S2AudioSystem();
private:
  S2BaseAudio *m_pService;
  S2NullAudio m_nullService;
};
#endif
