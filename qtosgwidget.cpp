#include "qtosgwidget.h"

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
//#include <stdlib.h>
//#include <stdio.h>
//#include <iostream>
#include <QApplication>
//#include <QMainWindow>
#include <QDesktopWidget>
#include <QScreen>
#include <QtGlobal>
#include <QWindow>
#include <osg/Camera>
#include <osg/ShapeDrawable>
#include <osg/StateSet>
#include <osg/Material>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>
#include <libs.h>
#include "KeyboardHandler.h"
QtOSGWidget::QtOSGWidget(QWidget *parent)
		: QOpenGLWidget(parent)
		, _mGraphicsWindow(new osgViewer::GraphicsWindowEmbedded(this->x(), this->y(),
		this->width(), this->height()))
		, _mViewer(new osgViewer::Viewer)
		// take care of HDPI screen, e.g. Retina display on Mac
		, m_scale(QApplication::desktop()->devicePixelRatio()) 
{
		osg::Cylinder *cylinder = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 0.25f, 0.5f);
		osg::ShapeDrawable *sd = new osg::ShapeDrawable(cylinder);
		sd->setColor(osg::Vec4(0.8f, 0.5f, 0.2f, 1.f));
		osg::Geode *geode = new osg::Geode;
		geode->addDrawable(sd);

		osg::Camera *camera = new osg::Camera;
		camera->setViewport(0, 0, this->width(), this->height());
		camera->setClearColor(osg::Vec4(0.9f, 0.9f, 1.f, 1.f));
		float aspectRatio = static_cast<float>(this->width()) / static_cast<float>(this->height());
		camera->setProjectionMatrixAsPerspective(30.f, aspectRatio, 1.f, 1000.f);
		camera->setGraphicsContext(_mGraphicsWindow);

		_mViewer->setCamera(camera);
		_mViewer->setSceneData(geode);
		osgGA::TrackballManipulator *manipulator = new osgGA::TrackballManipulator;
		manipulator->setAllowThrow(false);
		this->setMouseTracking(true);
		_mViewer->setCameraManipulator(manipulator);

		//_mViewer->addEventHandler(new KeyboardHandler);//追加用户自定义的交互事件处理器，这里是键盘响应事件。这时就开始接受事件了。
		//
		_mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
		_mViewer->realize();

		this->setFocusPolicy(Qt::StrongFocus);
	}
QtOSGWidget::~QtOSGWidget() 
{

}

void QtOSGWidget::paintGL() 
{
		_mViewer->frame();
}
void QtOSGWidget::resizeGL(int width, int height) 
{
		this->getEventQueue()->windowResize(this->x()*m_scale, this->y() * m_scale, width * m_scale, height * m_scale);
		_mGraphicsWindow->resized(this->x()*m_scale, this->y() * m_scale, width * m_scale, height * m_scale);
		osg::Camera *camera = _mViewer->getCamera();
		camera->setViewport(0, 0, this->width()*m_scale, this->height()* m_scale);
}

void QtOSGWidget::initializeGL() 
{
		osg::Geode *geode = dynamic_cast<osg::Geode *>(_mViewer->getSceneData());
		osg::StateSet *stateSet = geode->getOrCreateStateSet();
		osg::Material *material = new osg::Material;
		material->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
		stateSet->setAttributeAndModes(material, osg::StateAttribute::ON);
		stateSet->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

void QtOSGWidget::mouseMoveEvent(QMouseEvent *event) 
{
		this->getEventQueue()->mouseMotion(event->x()*m_scale, event->y()*m_scale);
}

void QtOSGWidget::mousePressEvent(QMouseEvent *event)
{
		unsigned int button = 0;
		switch (event->button()) 
		{
		case Qt::LeftButton:
			button = 1;
			break;
		case Qt::MiddleButton:
			button = 2;
			break;
		case Qt::RightButton:
			button = 3;
			break;
		default:
			break;
		}
		this->getEventQueue()->mouseButtonPress(event->x()*m_scale, event->y()*m_scale, button);
	}

void QtOSGWidget::mouseReleaseEvent(QMouseEvent *event) 
{
		unsigned int button = 0;
		switch (event->button()) 
		{
		case Qt::LeftButton:
			button = 1;
			break;
		case Qt::MiddleButton:
			button = 2;
			break;
		case Qt::RightButton:
			button = 3;
			break;
		default:
			break;
		}
		this->getEventQueue()->mouseButtonRelease(event->x()*m_scale, event->y()*m_scale, button);
	}

void QtOSGWidget::wheelEvent(QWheelEvent *event) 
{
		int delta = event->delta();
		osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
		this->getEventQueue()->mouseScroll(motion);
}
void QtOSGWidget::keyPressEvent(QKeyEvent *event)
{	 
	this->getEventQueue()->keyPress((osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
	
}
void QtOSGWidget::keyReleaseEvent(QKeyEvent *event)
{
	this->getEventQueue()->keyRelease((osgGA::GUIEventAdapter::KeySymbol)*(event->text().toLatin1().data()));
}
bool QtOSGWidget::event(QEvent *event)
{
		bool handled = QOpenGLWidget::event(event);
		this->update();
		return handled;
}
osgGA::EventQueue *QtOSGWidget::getEventQueue() const 
{
		osgGA::EventQueue *eventQueue = _mGraphicsWindow->getEventQueue();
		return eventQueue;
}


