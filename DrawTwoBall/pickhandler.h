#ifndef PICKHANDLER_H
#define PICKHANDLER_H

#endif // PICKHANDLER_H

#include "libs.h"

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgFX/Scribe>

#include <osgGA/GUIEventHandler>

#include <osgUtil/Optimizer>

#include <iostream>

#include <osgGA/TrackballManipulator>
#include <osgGA/CameraManipulator>

//对象选取事件处理器
class PickHandler:public osgGA::GUIEventHandler
{
public:
    PickHandler();
    ~PickHandler();

    bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
    void pick(osg::ref_ptr<osgViewer::View> view,float x,float y);
    //鼠标位置
    float _mx;
    float _my;
};
