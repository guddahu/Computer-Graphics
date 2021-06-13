// CLineDlg.cpp : implementation file
//

#include "pch.h"
#include "Step.h"
#include "CLineDlg.h"
#include "afxdialogex.h"


// CLineDlg dialog

IMPLEMENT_DYNAMIC(CLineDlg, CDialog)

CLineDlg::CLineDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LINEDLG, pParent)
	, m_fmx(0)
	, m_fmy(0)
	, m_fox(0)
	, m_foy(0)
{

}

CLineDlg::~CLineDlg()
{
}

void CLineDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_FMX, m_fmx);
	DDX_Text(pDX, IDC_FMY, m_fmy);
	DDX_Text(pDX, IDC_TOX, m_fox);
	DDX_Text(pDX, IDC_TOY, m_foy);
}


BEGIN_MESSAGE_MAP(CLineDlg, CDialog)
END_MESSAGE_MAP()


// CLineDlg message handlers
