#ifndef MY_VIEW_H
#define MY_VIEW_H

#include <iostream>
#include <vector>
#include <QGLViewer/qglviewer.h>
#include <Eigen/dense>

using namespace std;
using namespace Eigen;

class my_tri
{
public:

	Vector3d v1, v2, v3;
	my_tri(Vector3d v1, Vector3d v2, Vector3d v3)
	{
		this->v1 = v1;
		this->v2 = v2;
		this->v3 = v3;
	}
};

class Viewer : public QGLViewer
{
public:
  Viewer();
  ~Viewer();
  
protected:
  virtual void draw();
  virtual void init();

private:
  vector<my_tri> icon;
  void create_icon(vector<my_tri>& icon, vector<Vector3d>& new_light, int num_recursion);
};

#endif
