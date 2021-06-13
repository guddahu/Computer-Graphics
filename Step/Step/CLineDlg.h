#pragma once


// CLineDlg dialog

class CLineDlg : public CDialog
{
	DECLARE_DYNAMIC(CLineDlg)

public:
	CLineDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CLineDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LINEDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_fmx;
	double m_fmy;
	double m_fox;
	double m_foy;
};
