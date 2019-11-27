//处理键盘事件
#pragma once
#include<osg/Switch>
#include<osgDB/ReadFile>
#include<osgGA/GUIEventHandler>
#include<osgViewer/Viewer>
class KeyboardHandler :public osgGA::GUIEventHandler//人机交互事件处理器
{
public:
	//重构父类GUIEventHandler.handle，事件处理函数，自定义交互操作，
	//参数1:当前传入此处理器的事件，只可以被获取，不能被修改
	//参数2：反馈动作，动作适配器，可以获取也可以修改的参数，大部分时候这个传入值表示当前所用的视图对象View，可以用它来获取
	//        或控制视景器的状态变化。如：osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	//参数3：对象指针obj，保存该处理器的对象，可能是当前事件回调所在的Node节点指针，也可能是Drawable指针
	//参数4：传递该事件的访问器（EventVisitor），nv通常为当前时间访问器指针。
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa,
		osg::Object* obj, osg::NodeVisitor* nv)
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if (!viewer)return false;

		switch (ea.getEventType())//判断事件，做出响应
		{
		case osgGA::GUIEventAdapter::KEYDOWN://ea.getEventType()获取到的如果是键盘事件
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)//空格，控制鼠标到屏幕中间
			{
				int width = ea.getWindowWidth();
				int heigth = ea.getWindowHeight();
				viewer->requestWarpPointer(width*0.5, heigth*0.5);
			}
			else
			{
				osg::Switch* root = dynamic_cast<osg::Switch*>(viewer->getSceneData());
				if (!root) return false;
				//按下1为第一个不着火的飞机，2，着火飞机，3，牛
				if (ea.getKey() == '1')
				{
					root->setValue(0, true);
					root->setValue(1, false);
					root->setValue(2, false);
				}
				else if (ea.getKey() == '2')
				{
					root->setValue(0, false);
					root->setValue(1, true);
					root->setValue(2, false);
				}
				else if (ea.getKey() == '3')
				{
					root->setValue(0, false);
					root->setValue(1, false);
					root->setValue(2, true);
				}
				return true;
			}
			break;
		default:break;
		}
		return false;
	}

};
