/**
*
*    SAsyncTask类
*    异步任务处理类
*    @author ZeroX
*    @version v1.0 22/07/2017()
*
*/

#ifndef _SASYNCTASK_H_
#define _SASYNCTASK_H_
#include <functional>
#include "SRunnable.h"
template <typename TParam, typename TProgress, typename TResult>
class SAsyncTask :public SRunnable
{
public:
    //lambda表达式
    std::function<TResult(TParam param)> DoInBackground;
    std::function<void()> OnPreExecute;
    std::function<void(TResult result)> OnPostExecute;
    std::function<void(TProgress value)> OnProgressUpdate;
    std::function<void(TResult result)> OnCancelled;

public:
    SAsyncTask();
    virtual ~SAsyncTask();

    //公布进度
    void PublicProgress(TProgress value);

    //异步执行
    void Execute(TParam param);

    //悬挂任务
    bool Cancel(bool bCancle);

    //任务是否被悬挂
    bool IsCancelled();

    //取得结果
    TResult GetResult();

protected:
    //最终重写函数
    void Run() final;
private:
    SThread *m_pThread;      //线程类

    TParam m_param;          //记录参数
    TResult m_result;        //记录结果

    bool m_bCancel;          //是否被取消
};
template <typename TParam, typename TProgress, typename TResult>
SAsyncTask<TParam, TProgress, TResult>::SAsyncTask()
{
    m_pThread = new Thread(this);
    m_bCancle = false;

    DoInBackground = [](TParam param){return nullptr; };
    OnPreExecute = [](){};
    OnPostExecute = [](TResult result){};
    OnProgressUpdate = [](TProgress value){};
    OnCancelled = [](TResult result){};
}

template <typename TParam, typename TProgress, typename TResult>
SAsyncTask<TParam, TProgress, TResult>::~SAsyncTask()
{
    delete m_pThread;
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::Run()
{
    m_result = DoInBackground(m_param);
    OnPostExecute(m_result);
}

///////////////////////
template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::PublicProgress(TProgress value)
{
    OnProgressUpdate(value);
}

template <typename TParam, typename TProgress, typename TResult>
void SAsyncTask<TParam, TProgress, TResult>::Execute(TParam param)
{
    m_pParam = param;
    OnPreExecute();
    m_pThread->Start();
}

template <typename TParam, typename TProgress, typename TResult>
bool SAsyncTask<TParam, TProgress, TResult>::Cancel(bool bCancel)
{
    if (bCancle){
        m_pThread->Resume();
    }
    else{
        m_pThread->Suspend();
        OnCancelled(m_result);
    }
    m_bCancel = bCancle;
    return bCancle;

}

template <typename TParam, typename TProgress, typename TResult>
bool SAsyncTask<TParam, TProgress, TResult>::IsCancelled()
{
    return m_bCancel;
}

template <typename TParam, typename TProgress, typename TResult>
TResult SAsyncTask<TParam, TProgress, TResult>::GetResult()
{
    return m_result;
}
#endif