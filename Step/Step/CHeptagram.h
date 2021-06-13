#pragma once


// CHeptagram dialog

class CHeptagram : public CDialog
{
	DECLARE_DYNAMIC(CHeptagram)

public:
	CHeptagram(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CHeptagram();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HEPTA };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_centerX;
	double m_centerY;
	double m_edge;
	double m_angle;
};
