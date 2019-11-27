//��������¼�
#pragma once
#include<osg/Switch>
#include<osgDB/ReadFile>
#include<osgGA/GUIEventHandler>
#include<osgViewer/Viewer>
class KeyboardHandler :public osgGA::GUIEventHandler//�˻������¼�������
{
public:
	//�ع�����GUIEventHandler.handle���¼����������Զ��彻��������
	//����1:��ǰ����˴��������¼���ֻ���Ա���ȡ�����ܱ��޸�
	//����2���������������������������Ի�ȡҲ�����޸ĵĲ������󲿷�ʱ���������ֵ��ʾ��ǰ���õ���ͼ����View��������������ȡ
	//        ������Ӿ�����״̬�仯���磺osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
	//����3������ָ��obj������ô������Ķ��󣬿����ǵ�ǰ�¼��ص����ڵ�Node�ڵ�ָ�룬Ҳ������Drawableָ��
	//����4�����ݸ��¼��ķ�������EventVisitor����nvͨ��Ϊ��ǰʱ�������ָ�롣
	virtual bool handle(const osgGA::GUIEventAdapter& ea,
		osgGA::GUIActionAdapter& aa,
		osg::Object* obj, osg::NodeVisitor* nv)
	{
		osgViewer::Viewer* viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		if (!viewer)return false;

		switch (ea.getEventType())//�ж��¼���������Ӧ
		{
		case osgGA::GUIEventAdapter::KEYDOWN://ea.getEventType()��ȡ��������Ǽ����¼�
			if (ea.getKey() == osgGA::GUIEventAdapter::KEY_Space)//�ո񣬿�����굽��Ļ�м�
			{
				int width = ea.getWindowWidth();
				int heigth = ea.getWindowHeight();
				viewer->requestWarpPointer(width*0.5, heigth*0.5);
			}
			else
			{
				osg::Switch* root = dynamic_cast<osg::Switch*>(viewer->getSceneData());
				if (!root) return false;
				//����1Ϊ��һ�����Ż�ķɻ���2���Ż�ɻ���3��ţ
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
