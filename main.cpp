#include <QtGui/QApplication>
#include "habrawidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HabraWidget w;
	w.show();
	
	return a.exec();
}
