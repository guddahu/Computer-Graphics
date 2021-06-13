
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Step.h"
#include "ChildView.h"
#include "CLineDlg.h"
#include "CHeptagram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_SAVEAS, &CChildView::OnSaveImage)
    ON_COMMAND(ID_STEPSTUFF_LINEENDTO0, &CChildView::OnStepstuffLineendto0)
    ON_COMMAND(ID_STEPSTUFF_LINEDIALOG, &CChildView::OnStepstuffLinedialog)
    ON_COMMAND(ID_STEPSTUFF_HEPTAGRAM, &CChildView::OnStepstuffHeptagram)
    ON_COMMAND(ID_STEPSTUFF_ROTATEHEPTAGRAM, &CChildView::OnStepstuffRotateheptagram)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}



void CChildView::OnGLDraw(CDC* pDC)
{


	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Simple rectangle example
    int width, height;
    GetSize(width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, // left
        1.0, // right
        0.0, // bottom
        GLdouble(height) / GLdouble(width), // top
        1.0, // near
        -1.0); // far

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3d(1., 0., 0.);

    //glBegin(GL_POLYGON);
    //glVertex2d(0.25, 0.25);
    //glVertex2d(0.75, 0.25);
    //glVertex2d(0.75, 0.75);
    //glVertex2d(0.25, 0.75);
    //glEnd();

    //glBegin(GL_LINE_STRIP);
    //glVertex2d(0.1, 0.1);
    //glVertex2d(0.8, 0.22);
    //glVertex2d(0.78, 0.9);
    //glVertex2d(0.2, 0.9);
    //glEnd();

    //glBegin(GL_LINES);
    ////glVertex2d(m_linefmx, m_linefmy);
    ////glVertex2d(m_linetox, m_linetoy);
    //glVertex2d(m_linefmx + 0.1, m_linefmy + 0.1);
    //glVertex2d(m_linetox + 0.1, m_linetoy + 0.1);
    //glEnd();
    //if (m_linetox < 0.2) {
    //    m_linetox = 0.1;
    //}

    //double m_edge = 0.7;
    //double m_centerX = 0.5;
    //double m_centerY = 0.5;
    //double pi = 3.141593;

    //m_edge = 0.5;
    double radius = (m_edge / 2) / sin(((3.0) / 7.0) * pi);


     //phi = 0.5;

    glBegin(GL_LINES);

    
    glVertex2d((radius * cos(pi/2 + (2.0/7.0)*pi * 0 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 0 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 3 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 3 + phi)) + m_centerY);

    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 3 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 3 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 6 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 6 + phi)) + m_centerY);

    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 6 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 6 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 2 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 2 + phi)) + m_centerY);

    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 2 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 2 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 5 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 5 + phi)) + m_centerY);

    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 5 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 5 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 1 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 1 + phi)) + m_centerY);

    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 1 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 1 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 4 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 4 + phi)) + m_centerY);

    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 4 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 4 + phi)) + m_centerY);
    glVertex2d((radius * cos(pi / 2 + (2.0 / 7.0) * pi * 0 + phi)) + m_centerX, (radius * sin(pi / 2 + (2.0 / 7.0) * pi * 0 + phi)) + m_centerY);
    //glVertex2d(radius * cos(pi / 2 + (2.0 / 7.0) * pi * 1), radius * sin(pi / 2 + (2.0 / 7.0) * pi * 1));
    //glVertex2d(radius * cos(pi / 2 + (2.0 / 7.0) * pi * 3), radius * sin(pi / 2 + (2.0 / 7.0) * pi * 3));
    //glVertex2d(abs(radius * cos(pi / 2 + (2.0 / 7.0) * pi * 3)), abs(radius * sin(pi / 2 + (2.0 / 7.0) * pi * 3)));
    //glVertex2d(abs(radius * cos(pi / 2 + (2.0 / 7.0) * pi * 5)), abs(radius * sin(pi / 2 + (2.0 / 7.0) * pi * 5)));
    glColor3d(0., 1., 0.);
    //phi = 0.3;
    //radius = 1.414 * radius;
    glVertex2d(m_centerX + radius * cos(pi/2 + (2*pi / 4) * 1+ phi) - radius * sin(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 1+ phi) + radius * cos(phi));
    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) *3+ phi) - radius * sin(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 3+ phi ) + radius * cos(phi));

    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) * 0 + phi) - radius * cos(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 0 + phi) - radius * sin(phi));
    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) * 2 + phi) - radius * cos(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 2 + phi) - radius * sin(phi));

    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) * 0 + phi) + radius * cos(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 0 + phi) + radius * sin(phi));
    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) * 2 + phi) + radius * cos(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 2 + phi) + radius * sin(phi));

    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) * 1 + phi) + radius * sin(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 1 + phi) - radius * cos(phi));
    glVertex2d(m_centerX + radius * cos(pi / 2 + (2 * pi / 4) * 3 + phi) + radius * sin(phi), m_centerY + radius * sin(pi / 2 + (2 * pi / 4) * 3 + phi) - radius * cos(phi));

    glEnd();


}


void CChildView::OnSaveImage()
{
	// TODO: Add your command handler code here


}


void CChildView::OnStepstuffLineendto0()
{
    m_linetox = 0.1;
    m_linetoy = 0.1;

    m_linefmx = 0.2;
    m_linefmy = 0.2;

    Invalidate();
}


void CChildView::OnStepstuffLinedialog()
{
    CLineDlg dlg;

    dlg.m_fmx = m_linefmx;
    dlg.m_fmy = m_linefmy;
    dlg.m_fox = m_linetox;
    dlg.m_foy = m_linetoy;

    if (dlg.DoModal() == IDOK)
    {
        m_linefmx = dlg.m_fmx;
        m_linefmy = dlg.m_fmy;
        m_linetox = dlg.m_fox;
        m_linetoy = dlg.m_foy;

        Invalidate();
    }
}


void CChildView::OnStepstuffHeptagram()
{
    CHeptagram dlg;

    dlg.m_centerX = m_centerX;
    dlg.m_centerY = m_centerY;
    dlg.m_edge = m_edge;
    dlg.m_angle = phi * 180 / pi;

    if (dlg.DoModal() == IDOK)
    {
        m_centerX = dlg.m_centerX;
        m_centerY = dlg.m_centerY;
        m_edge = dlg.m_edge;
        phi = dlg.m_angle * pi / 180;

        Invalidate();
    }
}


void CChildView::OnStepstuffRotateheptagram()
{
    phi += 20 * pi / 180;
    Invalidate();

}
