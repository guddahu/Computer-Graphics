#include "pch.h"
#include "CMyRaytraceRenderer.h"
#include "graphics/GrPoint.h"
#include <GL/glu.h>

void CMyRaytraceRenderer::SetWindow(CWnd* p_window)
{
    m_window = p_window;

}

bool CMyRaytraceRenderer::RendererStart()
{
	m_intersection.Initialize();
	m_bluegill.LoadFile(L"models/BLUEGILL.BMP");

	m_mstack.clear();


	// We have to do all of the matrix work ourselves.
	// Set up the matrix stack.
	CGrTransform t;
	t.SetLookAt(Eye().X(), Eye().Y(), Eye().Z(),
		Center().X(), Center().Y(), Center().Z(),
		Up().X(), Up().Y(), Up().Z());

	m_mstack.push_back(t);

	m_material = NULL;


	return true;
}

void CMyRaytraceRenderer::RendererMaterial(CGrMaterial* p_material)
{
	m_material = p_material;
}

void CMyRaytraceRenderer::RendererPushMatrix()
{
	m_mstack.push_back(m_mstack.back());
}

void CMyRaytraceRenderer::RendererPopMatrix()
{
	m_mstack.pop_back();
}

void CMyRaytraceRenderer::RendererRotate(double a, double x, double y, double z)
{
	CGrTransform r;
	r.SetRotate(a, CGrPoint(x, y, z));
	m_mstack.back() *= r;
}

void CMyRaytraceRenderer::RendererTranslate(double x, double y, double z)
{
	CGrTransform r;
	r.SetTranslate(x, y, z);
	m_mstack.back() *= r;
}

//
// Name : CMyRaytraceRenderer::RendererEndPolygon()
// Description : End definition of a polygon. The superclass has
// already collected the polygon information
//

void CMyRaytraceRenderer::RendererEndPolygon()
{
    const std::list<CGrPoint>& vertices = PolyVertices();
    const std::list<CGrPoint>& normals = PolyNormals();
    const std::list<CGrPoint>& tvertices = PolyTexVertices();

    // Allocate a new polygon in the ray intersection system
    m_intersection.PolygonBegin();
    m_intersection.Material(m_material);


    if (PolyTexture())
    {
        m_intersection.Texture(PolyTexture());
    }

    std::list<CGrPoint>::const_iterator normal = normals.begin();
    std::list<CGrPoint>::const_iterator tvertex = tvertices.begin();

    for (std::list<CGrPoint>::const_iterator i = vertices.begin(); i != vertices.end(); i++)
    {
        if (normal != normals.end())
        {
            m_intersection.Normal(m_mstack.back() * *normal);
            normal++;
        }

        if (tvertex != tvertices.end())
        {
            m_intersection.TexVertex(*tvertex);
            tvertex++;
        }

        m_intersection.Vertex(m_mstack.back() * *i);
    }

    m_intersection.PolygonEnd();
}

void CMyRaytraceRenderer::RayColor(CRay ray, double* colorTotal, int recurse, const CRayIntersection::Object* nearest1) {

	double t;                                   // Will be distance to intersection
	CGrPoint intersect;                         // Will by x,y,z location of intersection
	const CRayIntersection::Object* nearest;    // Pointer to intersecting object

	CGrPoint N;
	CGrMaterial* material;
	CGrTexture* texture;
	CGrPoint texcoord;



	if (m_intersection.Intersect(ray, 1e20, NULL, nearest, t, intersect) )//m_intersection.Intersect(ray, 1e20, nearest1, nearest, t, intersect)
	{
		m_intersection.IntersectInfo(ray, nearest, t,
			N, material, texture, texcoord);
		if (t >= 0.001 && texture == NULL ) {
			
			
			CGrPoint lightdirection;

			double Kdr = 1.f;

			for (int c = 0; c < 3; c++) {
				double light_ambient = 0;

				for (int i = 0; i < LightCnt(); i++) {
					light_ambient += GetLight(i).m_ambient[c];

				}
				
				
					colorTotal[c] += (Kdr * light_ambient) * (Kdr * material->Ambient(c));
				
				

				
			}

			//return;
			for (int i = 0; i < LightCnt(); i++) {
				if (GetLight(i).m_pos[3] == 0)
					lightdirection = Normalize3(GetLight(i).m_pos);
				else
					lightdirection = Normalize3(GetLight(i).m_pos - intersect);

				if (Dot3(N, lightdirection) < 0)
					continue; // Light is not hitting the surface

				CRay Ray1(intersect,lightdirection);
				if (!m_intersection.Intersect(Ray1, 1e20, nearest, nearest, t, intersect)) {
					for (int c = 0; c < 3; c++) {
						colorTotal[c] += GetLight(i).m_diffuse[c] * material->Diffuse(c) * Dot3(N, lightdirection);

					}

					auto view_direction = Normalize3(-ray.Direction());
					auto half = Normalize3(lightdirection + view_direction);
					auto sif = pow(Dot3(N, half), 0.1f);

					for (int c = 0; c < 3; c++)
					{
						colorTotal[c] += GetLight(i).m_specular[c] * material->Specular(c) * sif;
					}
				}
			}
			
			
				if (recurse == 1)
				{

					auto R = Normalize3((N * 2 * Dot3(N, -ray.Direction())) - (-ray.Direction()));
					intersect[0] += 0.001;
					intersect[1] += 0.001;
					intersect[2] += 0.001;
					CRay Ray(intersect, R);
					double raycolor[3] = { 0, 0, 0 };
					RayColor(Ray, raycolor, recurse - 1, nearest1);


					for (int c = 0; c < 3; c++)
					{
						colorTotal[c] += material->SpecularOther(c) * raycolor[c];
					}
					//colorTotal[1] += 0.5 * raycolor[1];
				}
			
		}

		else if (t > 0.001 && texture != NULL ) {
			m_intersection.IntersectInfo(ray, nearest, t,
				N, material, texture, texcoord);
			CGrPoint lightdirection;

			double Kdr = 1.f;

			for (int c = 0; c < 3; c++) {
				double light_ambient = 0;

				for (int i = 0; i < LightCnt(); i++) {
					light_ambient += GetLight(i).m_ambient[c];

				}
				int test = texcoord.Y() * texture->Width();
				double aaa = (texture->Row(texcoord.X() * texture->Height())[test * 3 + c]) / 255.0;

				
					colorTotal[c] += (Kdr * light_ambient) * (Kdr * aaa);
				
				
			}

			for (int i = 0; i < LightCnt(); i++) {
				if (GetLight(i).m_pos[2] == 0)
					lightdirection = Normalize3(GetLight(i).m_pos);
				else
					lightdirection = Normalize3(GetLight(i).m_pos - intersect);

				if (Dot3(N, lightdirection) < 0)
					continue; // Light is not hitting the surface

				CRay Ray1(intersect, lightdirection);
				if (!m_intersection.Intersect(Ray1, 1e20, nearest, nearest, t, intersect) ) {
					for (int c = 0; c < 3; c++) {
						int test = texcoord.Y() * texture->Width();

						double aaa = (texture->Row(texcoord.X() * texture->Height())[test * 3 + c]) / 255.0;

						colorTotal[c] += GetLight(i).m_diffuse[c] * aaa * 0.4 * Dot3(N, lightdirection);

					}

					auto view_direction = Normalize3(-ray.Direction());
					auto half = Normalize3(lightdirection + view_direction);
					auto sif = pow(Dot3(N, half), 0.1f);

					for (int c = 0; c < 3; c++)
					{
						int test = texcoord.Y() * texture->Width();

						double aaa = (texture->Row(texcoord.X() * texture->Height())[test * 3 + c]) / 255.0;
						colorTotal[c] += GetLight(i).m_specular[c] * aaa * sif * 0.05;
					}
				}
			}

			if (recurse >= 1)
			{

				auto R = Normalize3((N * 2 * Dot3(N, -ray.Direction())) - (-ray.Direction()));
				intersect[0] += 0.001;
				intersect[1] += 0.001;
				intersect[2] += 0.001;
				CRay Ray(intersect, R);
				double raycolor[3] = { 0, 0, 0 };
				RayColor(Ray, raycolor, recurse - 1, nearest);


				for (int c = 0; c < 3; c++)
				{
					colorTotal[c] += material->SpecularOther(c) * raycolor[c];
				}
				//colorTotal[1] += 0.5 * raycolor[1];
			}

		}
	}


}


bool CMyRaytraceRenderer::RendererEnd()
{
	m_intersection.LoadingComplete();

	double ymin = -tan(ProjectionAngle() / 2 * GR_DTOR);
	double yhit = -ymin * 2;

	double xmin = ymin * ProjectionAspect();
	double xwid = -xmin * 2;

	for (int r = 0; r < m_rayimageheight; r++)
	{
		for (int c = 0; c < m_rayimagewidth; c++)
		{
			double colorTotal[3] = { 0, 0, 0 };

			double x = xmin + (c + 0.5) / m_rayimagewidth * xwid;
			double y = ymin + (r + 0.5) / m_rayimageheight * yhit;


			// Construct a Ray
			CRay ray(CGrPoint(0, 0, 0), Normalize3(CGrPoint(x, y, -1, 0)));

			double t;                                   // Will be distance to intersection
			CGrPoint intersect;                         // Will by x,y,z location of intersection
			const CRayIntersection::Object* nearest;    // Pointer to intersecting object
			if (m_intersection.Intersect(ray, 1e20, NULL, nearest, t, intersect))
			{
				// We hit something...
				// Determine information about the intersection
				CGrPoint N;
				CGrMaterial* material;
				CGrTexture* texture;
				CGrPoint texcoord;
				
				m_intersection.IntersectInfo(ray, nearest, t,
					N, material, texture, texcoord);

				if (material != NULL)
				{
					
					//CGrPoint lightdirection;

					//double Kdr = 0.8f;

					//for (int c = 0; c < 3; c++) 
					//
					//{
					//	double light_ambient = 0;

					//	for (int i = 0; i < LightCnt(); i++) {
					//		light_ambient += GetLight(i).m_ambient[c];

					//	}

					//	colorTotal[c] += (Kdr * light_ambient) * (Kdr * material->Ambient(c));
					//}

					//	for (int i = 0; i < LightCnt(); i++) {


					//		if (GetLight(i).m_pos[3] == 0)
					//			lightdirection = Normalize3(GetLight(i).m_pos);
					//		else
					//			lightdirection = Normalize3(GetLight(i).m_pos - intersect);

					//		if (Dot3(N, lightdirection) < 0)
					//			continue; // Light is not hitting the surface

					//		for (int c = 0; c < 3; c++) {
					//			colorTotal[c] +=  GetLight(i).m_diffuse[c] * material->Diffuse(c) * Dot3(N, lightdirection);
					//		}

					//		auto view_direction = Normalize3(-ray.Direction());
					//		//view_direction = Normalize3((N * Dot3(N, lightdirection)) * 2 - lightdirection);
					//		auto half = Normalize3(lightdirection + view_direction);
					//		auto sif = pow(Dot3(N, half), 2);

					//		for (int c = 0; c < 3; c++)
					//		{
					//			colorTotal[c] += GetLight(i).m_specular[c] * material->Specular(c) *sif;
					//		}
					//	}
					//



					
					//if (colorTotal[0] > 1) {
					//	colorTotal[0] = 1.f;
					//}
					//else if (colorTotal[1] > 1) {
					//	colorTotal[1] = 1.f;
					//}
					//else if (colorTotal[2] > 1) {
					//	colorTotal[2] = 1.f;
					//}
					//else if (colorTotal[0] < 0) {
					//	colorTotal[0] = 0;
					//}
					//else if (colorTotal[1] < 0) {
					//	colorTotal[1] = 0;
					//}
					//else if (colorTotal[2] < 0) {
					//	colorTotal[2] = 0;
					//}
					
					RayColor(ray, colorTotal, 1, nearest);

					

					m_rayimage[r][c * 3] = BYTE(int(colorTotal[0] * 255));
					m_rayimage[r][c * 3 + 1] = BYTE(int(colorTotal[1] * 255));
					m_rayimage[r][c * 3 + 2] = BYTE(int(colorTotal[2] * 255));
				}

			}
			else
			{
				// We hit nothing...
				m_rayimage[r][c * 3] = 0;
				m_rayimage[r][c * 3 + 1] = 0;
				m_rayimage[r][c * 3 + 2] = 0;
			}
		}
		if ((r % 50) == 0)
		{
			m_window->Invalidate();
			MSG msg;
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				DispatchMessage(&msg);
		}
		//m_window->Invalidate();     //To render every time we loop
		//m_window->UpdateWindow();
	}


	return true;
}

