/*
* =====================================================================================
*
*       Filename:  main.cpp
*
*    Description: Minimalistic project example that uses both Qt and OpenSceneGraph libraries.
*
*        Version:  1.0
*        Created:  30-Jun-16 10:23:06 AM
*       Revision:  none
*       Compiler:  gcc
*
*         Author:  Victoria Rudakova (vicrucann@gmail.com),
*   Organization:  vicrucann.github.io
*
* =====================================================================================
*/
#include "qtosgwidget.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <QApplication>
#include <QMainWindow>
int main(int argc, char **argv) 
{
#if QT_VERSION >= QT_VERSION_CHECK(5,6,0)
	QApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#else
	qputenv("QT_DEVICE_PIXEL_RATIO", QByteArray("1"));
#endif

	QApplication qapp(argc, argv);
	QMainWindow window;
	QtOSGWidget *widget = new QtOSGWidget(&window);
	window.setCentralWidget(widget);
	window.setGeometry(100,100,500,600);
	window.show();

	return qapp.exec();
}
