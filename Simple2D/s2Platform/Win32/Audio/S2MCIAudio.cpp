/*********************************
游戏音乐程序文件GameMusic.cpp
*********************************/

#include "S2MCIAudio.h"
#include <windows.h>
#include <stdio.h>
#include <mmsystem.h>		//包含文件
#pragma comment(lib,"winmm.lib")

int S2MCIAudio::g_nNewID = 1;		//初始化下一个可用编号

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

S2MCIAudio::S2MCIAudio()					//构造函数
{
    m_ID = g_nNewID;
    g_nNewID++;
    m_nVolume = 100;

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

S2MCIAudio::S2MCIAudio(LPTSTR szMusicPath)	//带路径参数的构造函数
{

    m_ID = g_nNewID;
    g_nNewID++;
    m_nVolume = 100;
    if (strlen(szMusicPath)>0)	//判断路径不为空
    {
        Open(szMusicPath);	//打开音乐文件
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

S2MCIAudio::~S2MCIAudio()//析构函数
{
    Close();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
MCIERROR S2MCIAudio::Execute(LPTSTR szCommand, LPTSTR szReturnString, UINT cchReturnSize, HWND hwndCallback)
{
    return mciSendString(szCommand, szReturnString, cchReturnSize, hwndCallback);	//获取状态
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::IsPlay()		//获取音乐播放状态
{
    char szStatus[20] = { '\0' };
    char szCommand[256];

    sprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);	//创建MCI命令字符串
    mciSendString(szCommand, szStatus, 20, 0);	//获取状态
    return(0 == strcmp(szStatus, TEXT("playing")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::IsOpen()		//获取音乐文件打开状态
{
    char szStatus[20] = { '\0' };
    char szCommand[256];

    sprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
    mciSendString(szCommand, szStatus, 20, 0);

    return(0 == strcmp(szStatus, TEXT("stopped")) || 0 == strcmp(szStatus, TEXT("playing")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::IsStop()
{
    char szStatus[20] = { '\0' };
    char szCommand[256];

    sprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
    mciSendString(szCommand, szStatus, 20, 0);
    return(0 == strcmp(szStatus, TEXT("stopped")));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LPTSTR S2MCIAudio::GetMusicState(LPTSTR szStatus, UINT nBufferSize)		//获取音乐状态
{
    char szCommand[256];

    sprintf_s(szCommand, TEXT("status MUSIC%d mode"), m_ID);
    mciSendString(szCommand, szStatus, nBufferSize, 0);

    return szStatus;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

UINT S2MCIAudio::GetVolume()			//获取音量大小
{
    return m_nVolume;
}

void S2MCIAudio::SetVolume(UINT nVolume)	//设置音量
{
    if (nVolume<0)
        nVolume = 0;
    if (nVolume>1000)
        nVolume = 1000;

    char szCommand[256];
    sprintf_s(szCommand, TEXT("Setaudio MUSIC%d volume to %d"), m_ID, nVolume);	//创建MCI命令字符串
    mciSendString(szCommand, NULL, 0, 0);	//设置音量

    m_nVolume = nVolume;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void S2MCIAudio::VolumeDown()		//减小音量
{
    SetVolume(m_nVolume - 10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void S2MCIAudio::VolumeUp()			//增大音量
{
    SetVolume(m_nVolume + 10);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::Open(LPTSTR szMusicPath)	//打开音乐文件
{

    if (strlen(szMusicPath) == 0)
        return FALSE;

    if (IsPlay() || IsStop())	//如果已有音乐文件被打开，则先关闭
        Close();

    char szCommand[256];
    sprintf_s(szCommand, TEXT("OPEN %s ALIAS MUSIC%d"), szMusicPath, m_ID);
    if (!mciSendString(szCommand, NULL, 0, 0))	//打开音乐文件
    {
        return TRUE;
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::Close()		//关闭音乐文件
{
    char szCommand[256];

    if (IsOpen())
    {
        sprintf_s(szCommand, TEXT("CLOSE MUSIC%d"), m_ID);
        if (!mciSendString(szCommand, NULL, 0, 0))
        {
            return TRUE;
        }
    }
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UINT S2MCIAudio::GetLength()			//取得媒体总长度
{
    char szStatus[20] = { '\0' };
    char szCommand[256];

    sprintf_s(szCommand, TEXT("status MUSIC%d length"), m_ID);
    mciSendString(szCommand, szStatus, 20, 0);

    //字符串转数字
    return atoi(szStatus);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::Play(UINT nVolume, BOOL bRepeat, BOOL bReStart) //播放音乐，可设置是否循环播放、重新播放
{
    char szCommand[256];

    if (IsStop() || bReStart)	//判断音乐在停止状态或要求重新播放时才播放
    {

        if (bRepeat)
            sprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM 0  repeat"), m_ID);
        else
            sprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM 0"), m_ID);

        if (!mciSendString(szCommand, NULL, 0, 0))
        {
            SetVolume(nVolume);
            return TRUE;
        }
    }

    return FALSE;
}

BOOL S2MCIAudio::Play(UINT nVolume, UINT nStartTime, UINT nEndTime, BOOL bRepeat, BOOL bReStart)//从X到Y播放音乐,可设置是否循环播放、重新播放
{
    char szCommand[256];

    if (IsStop() || bReStart)	//判断音乐在停止状态或要求重新播放时才播放
    {

        if (bRepeat)
            sprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM %d to %d repeat"), m_ID, nStartTime, nEndTime);
        else
            sprintf_s(szCommand, TEXT("PLAY MUSIC%d FROM %d to %d"), m_ID, nStartTime, nEndTime);

        if (!mciSendString(szCommand, NULL, 0, 0))
        {
            SetVolume(nVolume);
            return TRUE;
        }
    }

    return FALSE;
}

BOOL S2MCIAudio::Play(){
    char szCommand[256];
    sprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        return TRUE;
    }
    else return FALSE;
}
BOOL S2MCIAudio::LoopPlay(){
    return Play(GetVolume(), true, false);
}
BOOL  S2MCIAudio::RePlay(){
    Stop();
    return Play(GetVolume(), false, true);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::Stop()		//停止播放
{
    char szCommand[256];
    if (IsPlay())
    {
        sprintf_s(szCommand, TEXT("STOP MUSIC%d"), m_ID);
        if (!mciSendString(szCommand, NULL, 0, 0))
        {
            return TRUE;
        }
    }
    return FALSE;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL S2MCIAudio::Pause()	//暂停播放
{
    char szCommand[256];
    sprintf_s(szCommand, TEXT("PAUSE MUSIC%d"), m_ID);
    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        return TRUE;
    }
    else return FALSE;

}

BOOL S2MCIAudio::Resume()				//继续播放
{
    char szCommand[256];
    sprintf_s(szCommand, TEXT("RESUME MUSIC%d"), m_ID);
    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        return TRUE;
    }
    else return FALSE;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL S2MCIAudio::Seek(UINT nTime)		//设置进度
{
    char szCommand[256];
    sprintf_s(szCommand, TEXT("SEEK MUSIC%d to %d"), m_ID, nTime);

    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        //sprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
        return TRUE;
    }
    else return FALSE;
}

BOOL S2MCIAudio::SeekToStart()			//设置到开头
{
    char szCommand[256];
    sprintf_s(szCommand, TEXT("SEEK MUSIC%d to start"), m_ID);

    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        //sprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
        return TRUE;
    }
    else return FALSE;
}
BOOL S2MCIAudio::SeekToEnd()			//设置到结尾
{
    char szCommand[256];
    sprintf_s(szCommand, TEXT("SEEK MUSIC%d to end"), m_ID);

    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        //sprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
        return TRUE;
    }
    else return FALSE;
}

UINT S2MCIAudio::Tell()				//取得当前进度
{
    char szStatus[20] = { '\0' };
    char szCommand[256];

    sprintf_s(szCommand, TEXT("status MUSIC%d position"), m_ID);
    mciSendString(szCommand, szStatus, 20, 0);

    //字符串转数字
    return atoi(szStatus);
}

BOOL S2MCIAudio::Step(UINT nTime)				//快进或快退
{
    char szCommand[256];
    sprintf_s(szCommand, TEXT("STEP MUSIC%d by %d"), m_ID, nTime);

    if (!mciSendString(szCommand, NULL, 0, 0))
    {
        //sprintf_s(szCommand, TEXT("PLAY MUSIC%d"), m_ID);
        return TRUE;
    }
    else return FALSE;
}