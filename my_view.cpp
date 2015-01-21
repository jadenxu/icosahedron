#include"my_view.h"

Viewer::Viewer() {
	vector<Vector3d> new_light;
	create_icon(icon, new_light, 4);
}

void Viewer::init()
{
	// Restore previous viewer state.
	restoreStateFromFile();

	glEnable(GL_TEXTURE_2D);                        // Enable Texture Mapping ( NEW )
    glShadeModel(GL_SMOOTH);                        // Enable Smooth Shading
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);                   // Black Background
    glClearDepth(1.0f);                         // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                        // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                         // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);          // Really Nice Perspective 
}

void Viewer::draw()
{
	for(int i = 0; i < icon.size(); i++)
	{
		glColor3f(0.5f, 0.0f, 1.0f);
		glBegin(GL_TRIANGLES);
		glVertex3f(icon[i].v1(0), icon[i].v1(1),  icon[i].v1(2)); 
		glVertex3f(icon[i].v2(0), icon[i].v2(1),  icon[i].v2(2));
		glVertex3f(icon[i].v3(0), icon[i].v3(1),  icon[i].v3(2));
		glEnd();
		glColor3f(0.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(icon[i].v1(0), icon[i].v1(1),  icon[i].v1(2));
		glVertex3f(icon[i].v2(0), icon[i].v2(1),  icon[i].v2(2));
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(icon[i].v1(0), icon[i].v1(1),  icon[i].v1(2));
		glVertex3f(icon[i].v3(0), icon[i].v3(1),  icon[i].v3(2));
		glEnd();
		glBegin(GL_LINES);
		glVertex3f(icon[i].v2(0), icon[i].v2(1),  icon[i].v2(2));
		glVertex3f(icon[i].v3(0), icon[i].v3(1),  icon[i].v3(2));
		glEnd();
	}
}

bool my_cmp (Vector3d i,Vector3d j) 
{
  return (i(0)<j(0) || (i(0)==j(0)&&i(1)<j(1)) || (i(0)==j(0)&&i(1)==j(1)&&i(2)<j(2)));
}

void Viewer::create_icon(vector<my_tri>& icon, vector<Vector3d>& new_light, int num_recursion)
{
	vector<Vector3d> pts;
	double gold = (1.0 + sqrt(5.0)) / 2.0;
	pts.push_back(Vector3d(-1,  gold,  0));
	pts.push_back(Vector3d( 1,  gold,  0));
	pts.push_back(Vector3d(-1, -gold,  0));
	pts.push_back(Vector3d( 1, -gold,  0));

	pts.push_back(Vector3d( 0, -1,  gold));
	pts.push_back(Vector3d( 0,  1,  gold));
	pts.push_back(Vector3d( 0, -1, -gold));
	pts.push_back(Vector3d( 0,  1, -gold));

	pts.push_back(Vector3d( gold,  0, -1));
	pts.push_back(Vector3d( gold,  0,  1));
	pts.push_back(Vector3d(-gold,  0, -1));
	pts.push_back(Vector3d(-gold,  0,  1));

	for(int i = 0; i < pts.size(); i++)
	{
		pts[i].normalize();
	}

	// 5 faces around point 0
	icon.push_back(my_tri(pts[0], pts[11], pts[5]));
	icon.push_back(my_tri(pts[0], pts[5], pts[1]));
	icon.push_back(my_tri(pts[0], pts[1], pts[7]));
	icon.push_back(my_tri(pts[0], pts[7], pts[10]));
	icon.push_back(my_tri(pts[0], pts[10], pts[11]));

	// 5 adjacent faces 
	icon.push_back(my_tri(pts[1], pts[5], pts[9])); 
	icon.push_back(my_tri(pts[5], pts[11], pts[4])); 
	icon.push_back(my_tri(pts[11], pts[10], pts[2]));
	icon.push_back(my_tri(pts[10], pts[7], pts[6]));
	icon.push_back(my_tri(pts[7], pts[1], pts[8]));


	// 5 faces around point 3
	icon.push_back(my_tri(pts[3], pts[9], pts[4]));
	icon.push_back(my_tri(pts[3], pts[4], pts[2]));
	icon.push_back(my_tri(pts[3], pts[2], pts[6]));
	icon.push_back(my_tri(pts[3], pts[6], pts[8]));
	icon.push_back(my_tri(pts[3], pts[8], pts[9]));

	// 5 adjacent faces 
	icon.push_back(my_tri(pts[4], pts[9], pts[5]));
	icon.push_back(my_tri(pts[2], pts[4], pts[11]));
	icon.push_back(my_tri(pts[6], pts[2], pts[10]));
	icon.push_back(my_tri(pts[8], pts[6], pts[7]));
	icon.push_back(my_tri(pts[9], pts[8], pts[1]));

	int num = num_recursion;
	for(int i = 0; i < num; i++)
	{
		vector<my_tri> new_icon;
		for(int j = 0; j < icon.size(); j++)
		{
			Vector3d a = (icon[j].v1 + icon[j].v2) / 2.0;
			Vector3d b = (icon[j].v2 + icon[j].v3) / 2.0;
			Vector3d c = (icon[j].v1 + icon[j].v3) / 2.0;
			a.normalize();
			b.normalize();
			c.normalize();

			new_icon.push_back(my_tri(icon[j].v1, a, c));
			new_icon.push_back(my_tri(icon[j].v2, b, a));
			new_icon.push_back(my_tri(icon[j].v3, c, b));
			new_icon.push_back(my_tri(a, b, c));
		}
		icon = new_icon;
	}

	for(int i = 0; i < icon.size(); i++)
	{
		new_light.push_back(icon[i].v1);
		new_light.push_back(icon[i].v2);
		new_light.push_back(icon[i].v3);
	}
	sort(new_light.begin(), new_light.end(), my_cmp);
	vector<Vector3d> pts_tem;
	for(int i = 0; i < new_light.size(); i=i+6)
	{
		if(new_light[i](2) >= 0)
			pts_tem.push_back(new_light[i]);
	}
	new_light = pts_tem;
}

Viewer::~Viewer() {
}
