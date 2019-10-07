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
#pragma once
#include <QWidget>
#include <QOpenGLWidget>
#include <osg/ref_ptr>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/Viewer>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
class QtOSGWidget : public QOpenGLWidget 
{
public:
	QtOSGWidget(QWidget *parent = 0);
	virtual ~QtOSGWidget();
protected:
	virtual void paintGL();	
	virtual void resizeGL(int width, int height); 
	virtual void initializeGL(); 
	virtual void mouseMoveEvent(QMouseEvent *event); 
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event); 
	virtual void wheelEvent(QWheelEvent *event); 

	virtual void keyPressEvent(QKeyEvent *);
	virtual void keyReleaseEvent(QKeyEvent *);
	/*virtual void focusInEvent(QFocusEvent *);
	virtual void focusOutEvent(QFocusEvent *);
	virtual void enterEvent(QEvent *);
	virtual void leaveEvent(QEvent *);
	virtual void paintEvent(QPaintEvent *);
	virtual void moveEvent(QMoveEvent *);
	virtual void resizeEvent(QResizeEvent *);
	virtual void closeEvent(QCloseEvent *);*/

	virtual bool event(QEvent *event); 
private:
	osgGA::EventQueue *getEventQueue() const; 
	osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _mGraphicsWindow;
	osg::ref_ptr<osgViewer::Viewer> _mViewer;
	qreal m_scale;
};

