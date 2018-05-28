#include"S2Texture.h"
#include "S2Renderer.h"
#include "S2TexturePool.h"
S2Texture::S2Texture()
:m_pHandle(nullptr)
, m_nPixelWidth(0), m_nPixelHeight(0)
{

}
S2Texture::~S2Texture()
{
    S2RELEASE(GetHandle<IDirect3DTexture9 *>());
    S2TexturePool::GetInstance()->Release(this);
}
S2Texture *S2Texture::CreateWithFile(S2Renderer *pRenderer, S2String file)
{
    S2RELEASE(GetHandle<IDirect3DTexture9 *>());
    IDirect3DTexture9 *pTexture = nullptr;
    D3DXIMAGE_INFO info;
    ::D3DXCreateTextureFromFileEx(
        pRenderer->GetDeviceHandle<LPDIRECT3DDEVICE9>(),
        file.c_str(),
        D3DX_DEFAULT,   //FIXME:使用D3DX_DEFAULT会导致图片扩大2倍(缩小会造成模糊),使用D3DX_DEFAULT_NONPOW2不会,但效率低(且不都支持)
        D3DX_DEFAULT,
        0,
        0,
        D3DFMT_UNKNOWN, 
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT, 
        0,
        &info,
        NULL,
        &pTexture);
    m_pHandle = pTexture;
    m_nPixelWidth = info.Width;
    m_nPixelHeight = info.Height;
    return m_pHandle ? this : false;
}
S2Texture *S2Texture::CreateWithResource(S2Renderer *pRenderer, S2uInt unRcid)
{
    S2RELEASE(GetHandle<IDirect3DTexture9 *>());
    IDirect3DTexture9 *pTexture = nullptr;
    D3DXIMAGE_INFO info;
    ::D3DXCreateTextureFromResourceEx(
        pRenderer->GetDeviceHandle<LPDIRECT3DDEVICE9>(),
        ::GetModuleHandle(NULL),
        MAKEINTRESOURCE(unRcid),
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        0,
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        &info,
        NULL,
        &pTexture);
    m_pHandle = pTexture;
    m_nPixelWidth = info.Width;
    m_nPixelHeight = info.Height;
    return m_pHandle ? this : false;
}
S2Texture *S2Texture::CreateWithMemory(S2Renderer *pRenderer, const S2Data pAddr, S2uInt len)
{
    S2RELEASE(GetHandle<IDirect3DTexture9 *>());
    IDirect3DTexture9 *pTexture = nullptr;
    D3DXIMAGE_INFO info;
    ::D3DXCreateTextureFromFileInMemoryEx(
        pRenderer->GetDeviceHandle<LPDIRECT3DDEVICE9>(),
        pAddr,
        len,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        0, 
        D3DFMT_UNKNOWN,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT, 
        0,
        &info,
        NULL,
        &pTexture
        );
    m_pHandle = pTexture;
    m_nPixelWidth = info.Width;
    m_nPixelHeight = info.Height;
    return m_pHandle ? this : false;
}

S2uInt S2Texture::GetSurfaceWidth()const
{
    D3DSURFACE_DESC desc;
    GetHandle<IDirect3DTexture9 *>()->GetLevelDesc(0, &desc);
    return desc.Width;
}
S2uInt S2Texture::GetSurfaceHeight()const
{
    D3DSURFACE_DESC desc;
    GetHandle<IDirect3DTexture9 *>()->GetLevelDesc(0, &desc);
    return desc.Height;
}

S2uInt S2Texture::GetWidth()const
{
    return m_nPixelWidth;
}
S2uInt S2Texture::GetHeight()const
{
    return m_nPixelHeight;
}