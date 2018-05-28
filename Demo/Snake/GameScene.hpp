#include <Simple2D>
#include <s2Base/sMath/SMath.h>
#include <s2Base/sMath/SMathX.hpp>
class CSnake;
class CFood;

static S2Size WINSIZE;

class CSnake : public S2SceneNode
{
    const char *snake_head = "./res/snake/normal_headright.png";
    const char *snake_body = "./res/snake/v_body.png";
public:
    CSnake()
    {

        WINSIZE = S2Director::GetInstance()->GetRenderView()->GetViewSize();
        m_moveto.SetSpeed(2.f);

        auto pSpriteFrmae = S2SpriteFrameCache::GetInstance()->CreateWithFile(snake_head);
        m_headSprite.CreateWithSpriteFrame(pSpriteFrmae);
        m_headSprite.SetAnchorPoint(0.5f, 0.5f);
        m_headSprite.SetPosition(WINSIZE.width / 2, WINSIZE.height / 2);
        m_headSprite.RunAction(&m_moveto);
        __AddBody(10);

        
        AddChild(&m_snakeBodyLayer);
        AddChild(&m_headSprite);

        m_mouseListener.OnMouseMove = [=](S2MouseEvent *e)
        {
            __Move(e->mouseX, e->mouseY);

        };
        S2Application::GetInstance()->GetDispatcher()->AddEventListener(&m_mouseListener);//TODO:添加事件过于复杂


    }

    void Eat(CFood *pFood)
    {
        __AddBody();
    }

    S2Rect GetRect()
    {
        return S2Rect(m_headSprite.GetPosition().x, m_headSprite.GetPosition().y, m_headSprite.GetPosition().x + m_headSprite.GetSize().width, m_headSprite.GetPosition().y + m_headSprite.GetSize().height);
    }
    ~CSnake()
    {
        S2Application::GetInstance()->GetDispatcher()->RemoveEventListener(&m_mouseListener);
    }
private:
    void __AddBody(int nCount = 1)
    {
        auto pSpriteFrmae = S2SpriteFrameCache::GetInstance()->CreateWithFile(snake_body);

        for (int i = 0; i < nCount; ++i)
        {
            auto pSprite = S2Object::Create<S2Sprite>()->CreateWithSpriteFrame(pSpriteFrmae);
            pSprite->SetAnchorPoint(0.5f, 0.5f);
            if (!m_snakeBodySprites.empty())
                pSprite->SetPosition(m_snakeBodySprites.back()->GetPosition());
            else
                pSprite->SetPosition(m_headSprite.GetPosition());

            m_snakeBodySprites.push_back(pSprite);
            pSprite->Retain();
            m_snakeBodyLayer.AddChild(pSprite);
        }
    }

    void __Move(int x,int y)
    {
        m_moveto.SetDestPoint(S2Point(x, y));
        //m_moveto.Reset();

    }
    void OnUpdate(float fDelay)
    {
        auto vec2 = S2Vector2(m_moveto.GetDestPoint().x - m_headSprite.GetPosition().x, m_moveto.GetDestPoint().y - m_headSprite.GetPosition().y);
        double fAngle = SVec2Angle(&S2Vector2(1.f, 0.f), &vec2);
        m_headSprite.SetRotation(fAngle);
        if (m_snakeBodySprites.size() > 1)
        {
            for (size_t i = m_snakeBodySprites.size() - 1; i >= 1; --i){
                //vec2 = S2Vector2(m_snakeBodySprites.at(i - 1)->GetPosition().x - m_snakeBodySprites.at(i)->GetPosition().x, m_snakeBodySprites.at(i - 1)->GetPosition().y - m_snakeBodySprites.at(i)->GetPosition().y);
                //fAngle = SVec2Angle(&S2Vector2(1.f, 0.f), &vec2);
                m_snakeBodySprites.at(i)->SetPosition(m_snakeBodySprites.at(i - 1)->GetPosition());
                //m_snakeBodySprites.at(i)->SetRotation(fAngle);

            }
            //vec2 = S2Vector2(m_headSprite.GetPosition().x - m_snakeBodySprites.at(0)->GetPosition().x, m_headSprite.GetPosition().y - m_snakeBodySprites.at(0)->GetPosition().y);
            //fAngle = SVec2Angle(&S2Vector2(1.f, 0.f), &vec2);
            m_snakeBodySprites.at(0)->SetPosition(m_headSprite.GetPosition());
            //m_snakeBodySprites.at(0)->SetRotation(fAngle);
        }
    }
private:
    S2Layer                 m_snakeBodyLayer;
    S2Sprite                m_headSprite;
    S2MoveTo                m_moveto;
    S2Array<S2Sprite *>     m_snakeBodySprites;
    S2MousemEventListener   m_mouseListener;
};

class CFood :public S2SceneNode
{
    const char *food_normal = "./res/food/r_apple.png";
public:
    CFood() :m_count(0)
    {
        WINSIZE = S2Director::GetInstance()->GetRenderView()->GetViewSize();
        m_sprite.CreateWithFile(food_normal);
        m_sprite.SetAnchorPoint(0.5f, 0.5f);
        AddChild(&m_sprite);
        Reset(WINSIZE.width, WINSIZE.height);
    }
    void Reset(int width, int hight)
    {
        int x = SMath::Random(0, width-50);
        int y = SMath::Random(0, hight-50);
        this->SetPosition(x, y);
    }

    S2Rect GetRect()
    {
        return S2Rect(GetPosition().x, GetPosition().y, GetPosition().x + m_sprite.GetSize().width, GetPosition().y + m_sprite.GetSize().height);
    }

    void Eaten(CSnake *pSnake)
    {
        m_count++;
        Reset(WINSIZE.width, WINSIZE.height);
    }
    ~CFood()
    {

    }
private:
    S2Sprite    m_sprite;
    int         m_count;
};

class GameScene :public S2Scene
{
    const static int COLLECTION_RETURN_NONE = 0;
    const static int COLLECTION_RETURN_BORDER = 1;
    const static int COLLECTION_RETURN_FOOD = 2;
public:
    GameScene()
    {
        WINSIZE = S2Director::GetInstance()->GetRenderView()->GetViewSize();

        S2Sprite *pBgSprite = new S2Sprite();
        pBgSprite->CreateWithFile("./res/ui/background.jpg");
        m_background.AddChild(pBgSprite);

        m_objects.AddChild(&m_food);
        m_objects.AddChild(&m_snake);

        S2Sprite *pGameOverSprite = new S2Sprite();
        pGameOverSprite->CreateWithFile("./res/ui/gameover.png");
        pGameOverSprite->SetPosition(WINSIZE.width / 2, WINSIZE.height / 2);
        pGameOverSprite->SetAnchorPoint(0.5f, 0.5f);
        m_tip.AddChild(pGameOverSprite);
        m_tip.SetVisible(false);

        this->AddChild(&m_background);
        this->AddChild(&m_objects);
        this->AddChild(&m_tip);
    }
    ~GameScene()
    {

    }

    void OnUpdate(float fDelay)
    {
        
        switch (__IsCollection())
        {
        case COLLECTION_RETURN_BORDER:
        {
            __GameOver();
        }break;
        case COLLECTION_RETURN_FOOD:
        {
            m_snake.Eat(&m_food);
            m_food.Eaten(&m_snake);
        }break;
        case COLLECTION_RETURN_NONE:break;
        }
    }

    virtual void OnDraw(S2Renderer *pRenderer, const S2Matrix *mat4, S2uInt flag)
    {
        char szFPS[128];
        auto pFont = S2Object::Create<S2Font>();
        auto pGraphics = pRenderer->CreateGraphics();
        pFont->CreateWithFaceName(S2Director::GetInstance()->GetRenderView()->GetViewRenderer(), "微软雅黑", 20);
        sprintf_s(szFPS, "FPS:%0.1f", S2Director::GetInstance()->GetFramesPerSecond());
        pGraphics->DrawFont(pFont, szFPS, nullptr, S2COLOR_RGB(255, 255, 255), DT_CENTER);
    }
private:

    int __IsCollection()
    {
        //边界碰撞
        S2Rect winborder(0, 0, WINSIZE.width, WINSIZE.height);
        if (!m_snake.GetRect().IsInRect(winborder))
            return COLLECTION_RETURN_BORDER;

        //食物碰撞
        if (m_snake.GetRect().IsCollision(m_food.GetRect()))
            return COLLECTION_RETURN_FOOD;
        //

        return COLLECTION_RETURN_NONE;
    }

    void __GameOver()
    {
        m_snake.SetEnabled(false);
        m_food.SetEnabled(false);
        m_tip.SetVisible(true);
    }

private:
    CSnake  m_snake;
    CFood   m_food;
    S2Layer m_background;
    S2Layer m_objects;
    S2Layer m_tip;
};