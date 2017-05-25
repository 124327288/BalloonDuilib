#ifndef __UIMARKUP_H__
#define __UIMARKUP_H__

#pragma once

namespace DuiLib {

enum
{
    XMLFILE_ENCODING_UTF8 = 0,
    XMLFILE_ENCODING_UNICODE = 1,
    XMLFILE_ENCODING_ASNI = 2,
};

class CMarkup;
class CMarkupNode;


class DUILIB_API CMarkup
{
    friend class CMarkupNode;
public:
    CMarkup(LPCTSTR pstrXML = NULL);
    ~CMarkup();

    bool Load(LPCTSTR pstrXML);
    bool LoadFromMem(BYTE* pByte, DWORD dwSize, int encoding = XMLFILE_ENCODING_UTF8);
    bool LoadFromFile(LPCTSTR pstrFilename, int encoding = XMLFILE_ENCODING_UTF8);
    void Release();
    bool IsValid() const;

    void SetPreserveWhitespace(bool bPreserve = true);
    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;

    CMarkupNode GetRoot();

private:
    typedef struct tagXMLELEMENT
    {
        ULONG iStart;               //xmlԪ�ر�ǩ�ַ��������m_pstrXML���ڴ��е�ƫ��ֵ
        ULONG iChild;               //xmlԪ����Ԫ�صĸ���
        ULONG iNext;
        ULONG iParent;
        ULONG iData;                //��ǰ��ǩ���һ�����Խ���λ�������m_pstrXML���ڴ��е�ƫ��ֵ
    } XMLELEMENT;

    LPTSTR      m_pstrXML;              //ָ���ڴ��е�xml�����ļ�����0���������ڴ棩
    XMLELEMENT* m_pElements;            //���500��Ԫ�أ�
    ULONG       m_nElements;
    ULONG       m_nReservedElements;
    TCHAR       m_szErrorMsg[100];
    TCHAR       m_szErrorXML[50];
    bool m_bPreserveWhitespace;

private:
    bool _Parse();
    bool _Parse(LPTSTR& pstrText, ULONG iParent);
    XMLELEMENT* _ReserveElement();                      //Ԥ����500���ڵ�Ԫ��
    inline void _SkipWhitespace(LPTSTR& pstr) const;
    inline void _SkipWhitespace(LPCTSTR& pstr) const;
    inline void _SkipIdentifier(LPTSTR& pstr) const;
    inline void _SkipIdentifier(LPCTSTR& pstr) const;
    bool _ParseData(LPTSTR& pstrText, LPTSTR& pstrData, char cEnd);
    void _ParseMetaChar(LPTSTR& pstrText, LPTSTR& pstrDest);
    bool _ParseAttributes(LPTSTR& pstrText);
    bool _Failed(LPCTSTR pstrError, LPCTSTR pstrLocation = NULL);
};


class DUILIB_API CMarkupNode
{
    friend class CMarkup;
private:
    CMarkupNode();
    CMarkupNode(CMarkup* pOwner, int iPos);

public:
    bool IsValid() const;

    CMarkupNode GetParent();
    CMarkupNode GetSibling();
    CMarkupNode GetChild();
    CMarkupNode GetChild(LPCTSTR pstrName);

    bool HasSiblings() const;
    bool HasChildren() const;
    LPCTSTR GetName() const;
    LPCTSTR GetValue() const;

    bool HasAttributes();
    bool HasAttribute(LPCTSTR pstrName);
    int GetAttributeCount();
    LPCTSTR GetAttributeName(int iIndex);
    LPCTSTR GetAttributeValue(int iIndex);
    LPCTSTR GetAttributeValue(LPCTSTR pstrName);
    bool GetAttributeValue(int iIndex, LPTSTR pstrValue, SIZE_T cchMax);
    bool GetAttributeValue(LPCTSTR pstrName, LPTSTR pstrValue, SIZE_T cchMax);

private:
    void _MapAttributes();

    enum { MAX_XML_ATTRIBUTES = 64 };

    typedef struct
    {
        ULONG iName;            //��ǰ��ǩ�����������m_pstrXML���ڴ��е�ƫ��ֵ
        ULONG iValue;           //��ǰ��ǩ����ֵ�����m_pstrXML���ڴ��е�ƫ��ֵ
    } XMLATTRIBUTE;

    int                 m_iPos;                             //��Ԫ����CMarkup::m_pElements�����е�����
    int                 m_nAttributes;
    XMLATTRIBUTE        m_aAttributes[MAX_XML_ATTRIBUTES];  //��ǩ���������ԣ����֧��64��
    CMarkup*            m_pOwner;
};

} // namespace DuiLib

#endif // __UIMARKUP_H__
