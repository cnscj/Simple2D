/**
 * @Author: cnscj 
 * @Version: v1.0 
 * @Date: 2018-05-26 12:46:18 
 * @Brief: 音效基类
 * @Last Modified by: cnscj 
 * @Last Modified time: 2018-05-26 12:46:18 
 * @Last Modified log: 
 */
#ifndef _S2BASEAUDIO_H_
#define _S2BASEAUDIO_H_
#include "../s2Core/S2Object.h"
class S2BaseAudio : public S2Object
{
public:
    virtual ~S2BaseAudio(){}

    /**
    * @brief 播放声音
    *
    * @param soundID 音频ID
    */
    virtual void PlaySound(int soundID) = 0;

    /**
    * @brief 暂停播放
    *
    * @param soundID 播放声音
    */
    virtual void StopSound(int soundID) = 0;

    /**
    * @brief 停止所有声音播放
    *
    */
    virtual void StopAllSounds() = 0;
};
#endif
