#ifndef __UILABEL_H__
#define __UILABEL_H__

#pragma once

#define _USE_GDIPLUS 1

#ifdef _USE_GDIPLUS
#include <GdiPlus.h>
#pragma comment( lib, "GdiPlus.lib" )
using namespace Gdiplus;
class DUILIB_API Gdiplus::RectF;
struct DUILIB_API Gdiplus::GdiplusStartupInput;
#endif


namespace DuiLib
{
	//��Ӧlabel��ǩ
    class DUILIB_API CLabelUI : public CControlUI
	{
	public:
		CLabelUI();
		~CLabelUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

        void SetFixedWidth(int cx);
        void SetFixedHeight(int cy);
		void SetText(LPCTSTR pstrText);

		void SetTextStyle(UINT uStyle);
		UINT GetTextStyle() const;
		bool IsMultiLine();
		void SetMultiLine(bool bMultiLine = true);
		void SetTextColor(DWORD dwTextColor);
		DWORD GetTextColor() const;
		void SetDisabledTextColor(DWORD dwTextColor);
		DWORD GetDisabledTextColor() const;
        /**����ʹ�õ�����id
         *@param index ����id��-1ʹ��Ĭ�����壬������default=true��<Font>��ǩ
         **/
		void SetFont(int index);
		int GetFont() const;
		RECT GetTextPadding() const;
		void SetTextPadding(RECT rc);
        /**
         * ���ǵ���xml�༭����ʹ��<>���Ų����㣬����ʹ��{}���Ŵ���
         * ֧�ֱ�ǩǶ�ף���<l><b>text</b></l>�������ǽ���Ƕ����Ӧ�ñ���ģ���<l><b>text</l></b>��
         * The string formatter supports a kind of "mini-html" that consists of various short tags:
         *
         *   Bold:             <b>text</b>
         *   Color:            <c #xxxxxx>text</c>  where x = RGB in hex
         *   Font:             <f x>text</f>        where x = font id
         *   Italic:           <i>text</i>
         *   Image:            <i x y z>            where x = image name and y = imagelist num and z(optional) = imagelist id
         *   Link:             <a x>text</a>        where x(optional) = link content, normal like app:notepad or http:www.xxx.com
         *   NewLine           <n>
         *   Paragraph:        <p x>text</p>        where x = extra pixels indent in p
         *   Raw Text:         <r>text</r>
         *   Selected:         <s>text</s>
         *   Underline:        <u>text</u>
         *   X Indent:         <x i>                where i = hor indent in pixels
         *   Y Indent:         <y i>                where i = ver indent in pixels
         *   Vertical align    <v x>				where x = top or x = center or x = bottom
         **/
		bool IsShowHtml();
		void SetShowHtml(bool bShowHtml = true);

		SIZE EstimateSize(SIZE szAvailable);
		void DoEvent(TEventUI& event);

        /**
         *  ֧�ֵ����ԣ�
         *  align��left/center/right
         *  valign: top/vcenter/bottom
         *  endellipsis: bool �������Ƿ���...����
         *  font: int fontid
         *  textcolor: #AARRGGBB��0xAARRGGBB ������16����
         *  disabledtextcolor   #AARRGGBB��0xAARRGGBB ������16����
         *  textpadding int ˳����left,top,right,bottom 
         *  multiline   bool 
         *  showhtml    bool ��ʾΪhtml�ı�
         *  enabledeffect   bool 
         *  luminousfuzzy   bool ģ������
         *  gradientangle   bool ��������
         *  enabledstroke   bool �ڷ���
         *  enabledshadow   bool ��Ӱ
         *  gradientlength  int ��������
         *  shadowoffset    int ��Ӱ��Χ
         *  textcolor1      #AARRGGBB��0xAARRGGBB ������16����
         *  textshadowcolora    ��Ӱ��ɫ #AARRGGBB��0xAARRGGBB ������16����
         *  textshadowcolorb    ��Ӱ��ɫ #AARRGGBB��0xAARRGGBB ������16����
         *  strokecolor         �ڷ�����ɫ #AARRGGBB��0xAARRGGBB ������16����
         **/
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintText(HDC hDC);

#ifdef _USE_GDIPLUS
		void		SetEnabledEffect(bool _EnabledEffect);
		bool		GetEnabledEffect();
		void		SetEnabledLuminous(bool bEnableLuminous);
		bool		GetEnabledLuminous();
		void		SetLuminousFuzzy(float fFuzzy);
		float		GetLuminousFuzzy();
		void		SetGradientLength(int _GradientLength);
		int			GetGradientLength();
		void		SetShadowOffset(int _offset,int _angle);
		RectF		GetShadowOffset();
		void		SetTextColor1(DWORD _TextColor1);
		DWORD		GetTextColor1();
		void		SetTextShadowColorA(DWORD _TextShadowColorA);
		DWORD		GetTextShadowColorA();
		void		SetTextShadowColorB(DWORD _TextShadowColorB);
		DWORD		GetTextShadowColorB();
		void		SetStrokeColor(DWORD _StrokeColor);
		DWORD		GetStrokeColor();
		void		SetGradientAngle(int _SetGradientAngle);
		int			GetGradientAngle();
		void		SetEnabledStroke(bool _EnabledStroke);
		bool		GetEnabledStroke();
		void		SetEnabledShadow(bool _EnabledShadowe);
		bool		GetEnabledShadow();
#endif
	
	protected:
		LPWSTR  m_pWideText;
		DWORD	m_dwTextColor;              //������ɫ����Ӧtextcolor���ԣ�ȡֵ0xAARRGGBB
		DWORD	m_dwDisabledTextColor;      //����������ɫ����Ӧdisabledtextcolor,ȡֵ0xAARRGGBB
		int		m_iFont;                    //����id
		UINT	m_uTextStyle;
		RECT	m_rcTextPadding;
		bool	m_bShowHtml;
        SIZE    m_szAvailableLast;
        SIZE    m_cxyFixedLast;
        bool    m_bNeedEstimateSize;

		float					m_fLuminousFuzzy;
		int						m_GradientLength;
		int						m_GradientAngle;
		bool					m_EnableEffect;
		bool					m_bEnableLuminous;
		bool					m_EnabledStroke;
		bool					m_EnabledShadow;
		DWORD					m_dwTextColor1;
		DWORD					m_dwTextShadowColorA;
		DWORD					m_dwTextShadowColorB;
		DWORD					m_dwStrokeColor;
		RectF					m_ShadowOffset;
		ULONG_PTR				m_gdiplusToken;
#ifdef _USE_GDIPLUS
		GdiplusStartupInput		m_gdiplusStartupInput;
#endif
	};
}

#endif // __UILABEL_H__