
// ChildView.h : interface of the CChildView class
//


#pragma once
#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"
#include "graphics/GrCamera.h"
#include "Mesh.h"

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
	double r = 10;
	double l = 10;

	bool mobius_spin = false;
	bool box_spin = false;

	CGrTexture m_wood;
	CGrTexture m_bluegill;
	CGrTexture m_mobius_tex;

	double  m_spinAngle;
	double  m_spinAngleMobius;

	UINT_PTR m_spinTimer;
	UINT_PTR m_spinTimer1;

	CGrCamera m_camera;

	CMesh m_mesh;
	int m_scene;

	CMesh m_surface;
	CMesh m_fish;
	CMesh m_mobius;

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
	afx_msg
		void Box(GLdouble p_x, GLdouble p_y, GLdouble p_z, const GLdouble* p_color);
	void OnStepstuffRotateheptagram();
	afx_msg void OnStepSpin();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStepMesh();
	void CreateMesh();
	afx_msg void OnStepMeshrotation();
	afx_msg void OnStepMeshdlg();
};

