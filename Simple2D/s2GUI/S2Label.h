/**
*    S2Label
*    @brief 标签类
*    @author cnscj
*    @link -
*    @version v1.0
*    @date 09/03/2018
*    @update 09/03/2018
*/

#ifndef _S2LABEL_H_
#define _S2LABEL_H_
#include "S2Control.h"
class S2Font;

class S2Label :public S2Control
{
public:
    //获取\设置字体
    void SetFont(S2Font *pFont);
    S2Font *GetFont(S2Font *pFont);

    //设置\获取文本内容
    void SetText(S2String text);
    S2String GetText();

    //设置\获取颜色
    void SetColor(S2ColorRef dwColor);
    S2ColorRef GetColor();

    //设置\获取绘制格式
    void SetFormat(S2uInt uFormat);
    S2uInt GetFormat();
private:
    S2String        m_strWord;       //文字
    S2Font          *m_pFont;        //字体

    S2ColorRef      m_dwColor;       //绘制的颜色
    S2uInt          m_unFormat;      //绘制的参数

};
#endif