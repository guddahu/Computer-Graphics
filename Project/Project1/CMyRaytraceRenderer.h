#pragma once
#include "graphics/GrRenderer.h"
#include "graphics/RayIntersection.h"
#include "graphics/GrTexture.h"

class CMyRaytraceRenderer :
	public CGrRenderer
{
public:
    CGrTexture m_bluegill;

    CMyRaytraceRenderer() { m_window = NULL; 	}
    int     m_rayimagewidth;
    int     m_rayimageheight;
    BYTE** m_rayimage;
    void SetImage(BYTE** image, int w, int h) { m_rayimage = image; m_rayimagewidth = w;  m_rayimageheight = h; }

    CWnd* m_window;

    CRayIntersection m_intersection;

    std::list<CGrTransform> m_mstack;
    CGrMaterial* m_material;

    void SetWindow(CWnd* p_window);
    bool RendererStart();
    void RayColorTexture(CRay ray, double* colorTotal, int recurse, const CRayIntersection::Object* nearest1);
    bool RendererEnd();
    void RendererMaterial(CGrMaterial* p_material);

    virtual void RendererPushMatrix();
    virtual void RendererPopMatrix();
    virtual void RendererRotate(double a, double x, double y, double z);
    virtual void RendererTranslate(double x, double y, double z);
    void RendererEndPolygon();

    void RayColor(CRay ray, double* colorTotal, int recurse, const CRayIntersection::Object* nearest);

    struct CColor
    {
        CColor();

        double r = 0;
        double g = 0;
        double b = 0;
    };

};

