// CHeptagram.cpp : implementation file
//

#include "pch.h"
#include "Step.h"
#include "CHeptagram.h"
#include "afxdialogex.h"


// CHeptagram dialog

IMPLEMENT_DYNAMIC(CHeptagram, CDialog)

CHeptagram::CHeptagram(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_HEPTA, pParent)
	, m_centerX(0)
	, m_centerY(0)
	, m_edge(0)
	, m_angle(0)
{

}

CHeptagram::~CHeptagram()
{
}

void CHeptagram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CEN, m_centerX);
	DDX_Text(pDX, IDC_CENY, m_centerY);
	DDX_Text(pDX, IDC_EDGE, m_edge);
	DDX_Text(pDX, IDC_ANGLE, m_angle);
}


BEGIN_MESSAGE_MAP(CHeptagram, CDialog)
END_MESSAGE_MAP()


// CHeptagram message handlers
