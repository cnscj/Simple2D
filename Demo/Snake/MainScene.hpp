//#include <s2Scene/S2Scene.h>
//#include <s2Scene/S2Sprite.h>
//#include <s2Scene/Action/S2MoveTo.h>
//#include <s2Render/S2Font.h>
//#include <s2Render/S2Graphics.h>
#include <stdio.h>
#include <Simple2D>
#include "GameScene.hpp"
class TestSprite :public S2Layer
{
public:
    TestSprite()
    {
        S2SequenceAction *pSqu = new S2SequenceAction();
        S2ActionRepeat *pAction = new S2ActionRepeat(pSqu, -1);
        S2MoveTo *pMoveTo = nullptr;
        pMoveTo = new S2MoveTo();
        pMoveTo->SetDestPoint(S2Point(500, 500));
        pSqu->AddAction(pMoveTo);

        pMoveTo = new S2MoveTo();
        pMoveTo->SetDestPoint(S2Point(800, 0));
        pSqu->AddAction(pMoveTo);

        auto pSnake = (S2Sprite *)nullptr;
        for (int i = 0; i < 100; i++)
        {
            pSnake = new S2Sprite();
            pSnake->CreateWithFile("./res/snake/normal_headright.png");
            pSnake->SetPosition(i, 50);
            pSnake->SetOpacity(0.5f);
            this->AddChild(pSnake);
            pSnake->RunAction(pAction);

        }
    }

    ~TestSprite()
    {

    }
};

class TestSPriteAminate : public S2Layer
{
public:
    TestSPriteAminate()
    {
        m_pSpriteAnimation = new S2SpriteAnimation();
        m_pSpriteAnimation->CreateWithTextureFilesName("./res/people/man%d.bmp", 0, 7);

        m_pSprite = new S2Sprite();
        m_pSprite->SetPosition(S2Director::GetInstance()->GetRenderView()->GetViewWidth() / 2, S2Director::GetInstance()->GetRenderView()->GetViewHeight() / 2);
        m_pSprite->SetAnchorPoint(0.5f, 0.5f);
        m_pSprite->SetColorKey(S2COLOR_XRGB(255, 255, 255));
        m_pSprite->PlayAnimation(m_pSpriteAnimation);
        m_pSprite->AdaptiveSize();
        m_pSprite->SetRotation(30.f);
        AddChild(m_pSprite);

    }
    ~TestSPriteAminate()
    {
        m_pSpriteAnimation->Release();
        m_pSprite->Release();
    }
private:
    S2SpriteAnimation *m_pSpriteAnimation;
    S2Sprite *m_pSprite;
};



class MainScene : public S2Scene
{
public:
    MainScene()
    {
        m_mouseListener.OnMouseMove = [=](S2MouseEvent *e)
        {
            
            m_mouseX = e->mouseX;m_mouseY = e->mouseY;
        };
        S2Application::GetInstance()->GetDispatcher()->AddEventListener(&m_mouseListener);//TODO:添加事件过于复杂

        m_pFont = new S2Font();
        m_pFont->CreateWithFaceName(S2Director::GetInstance()->GetRenderView()->GetViewRenderer(), "微软雅黑", 20);

        ///
        //m_testLayer = new TestSPriteAminate();
        //AddChild(m_testLayer);

        //S2Director::GetInstance()->SetCamera(nullptr);
        S2Director::GetInstance()->SetFramesPerSecond(62.5f);
        m_pGameScene = new GameScene();
    }

    void OnEnter()
    {
        S2Director::GetInstance()->PushScene(m_pGameScene);
    }
    virtual ~MainScene()
    {

    }
public:
    virtual void Update(float fDelay)
    {
        
      

    }

    virtual void OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag)
    {
        auto pGraphics = pRenderer->CreateGraphics();
        sprintf_s(m_strFPS, "FPS:%0.1f\n%d,%d", S2Director::GetInstance()->GetFramesPerSecond(), m_mouseX, m_mouseY);
        pGraphics->DrawFont(m_pFont, m_strFPS, nullptr, S2COLOR_RGB(255, 255, 255), DT_CENTER);

    }

private:
    S2Font      *m_pFont;
    S2Char      m_strFPS[128];
    S2Layer     *m_testLayer;
    S2Scene     *m_pGameScene;
    S2MousemEventListener   m_mouseListener;
    S2uInt      m_mouseX, m_mouseY;
};