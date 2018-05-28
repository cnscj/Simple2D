#include "S2Font.h"

#include "S2Renderer.h"
S2Font::S2Font()
:m_pHandle(nullptr)
{

}
S2Font::~S2Font()
{
    S2RELEASE(GetHandle<ID3DXFont *>());
}

S2Font *S2Font::CreateWithFaceName(S2Renderer *pRenderer, S2String faceName, S2uInt height)
{
    S2RELEASE(GetHandle<ID3DXFont *>());
    ID3DXFont *pFont = nullptr;
    ::D3DXCreateFont(
        pRenderer->GetDeviceHandle<LPDIRECT3DDEVICE9>(),
        height,
        0,
        0,
        1,
        false,
        DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS,
        DEFAULT_QUALITY,
        0,
        faceName.c_str(),
        &pFont);

    m_pHandle = pFont;

    return pFont ? this : nullptr;
}