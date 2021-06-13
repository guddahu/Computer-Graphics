
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"


// CChildView window

class CChildView : public COpenGLWnd
{

private:
	double m_linefmx = 0.5;
	double m_linefmy = 0.5;
	double m_linetox = 0.2;
	double m_linetoy = 0.55;


	double m_edge = 0.6;
	double m_centerX = 0.4;
	double m_centerY = 0.4;
	double pi = 3.141593;
	double phi = 0;

// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnGLDraw(CDC* pDC);
	afx_msg void OnSaveImage();
	afx_msg void OnStepstuffLineendto0();
	afx_msg void OnStepstuffLinedialog();
	afx_msg void OnStepstuffHeptagram();
	afx_msg void OnStepstuffRotateheptagram();
};

