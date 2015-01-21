#include "my_view.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
  Viewer viewer;
	viewer.setWindowTitle("Sphere Mesh");
	viewer.show();
	
  return a.exec();
}
