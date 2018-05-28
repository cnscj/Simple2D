#include <Simple2D>
class MainScene : public S2Scene
{
public:
    MainScene()
    {
       
        auto pSrrite = new S2Sprite();
        pSrrite->CreateWithFile("bg.png");
        pSrrite->SetPosition(S2Director::GetInstance()->GetRenderView()->GetViewWidth()/2, S2Director::GetInstance()->GetRenderView()->GetViewHeight()/2);
        pSrrite->SetAnchorPoint(0.5f, 0.5f);
        this->AddChild(pSrrite);

        m_pFont = new S2Font();
        m_pFont->CreateWithFaceName(S2Director::GetInstance()->GetRenderView()->GetViewRenderer(), "Î¢ÈíÑÅºÚ",20 );


    }
    virtual ~MainScene()
    {
  
    }
public:


    virtual void OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag)
    {
        int charCount = sprintf_s(m_strFPS, "FPS:%0.1f", S2Director::GetInstance()->GetFramesPerSecond());
        auto pGraphics = pRenderer->CreateGraphics();
        pGraphics->DrawFont(m_pFont, m_strFPS, nullptr, S2COLOR_RGB(255, 255, 255), DT_CENTER);

    }

private:
    S2Char      m_strFPS[128];
    S2Font      *m_pFont;
};