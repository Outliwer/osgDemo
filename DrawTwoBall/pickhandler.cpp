#include "pickhandler.h"

PickHandler::PickHandler()
{
    _mx=0.0f;
    _my=0.0f;
}

PickHandler::~PickHandler()
{

}

bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
    osg::ref_ptr<osgViewer::View> view=dynamic_cast<osgViewer::View*>(&aa);
    if(!view)return false;

    switch(ea.getEventType())
    {
    //鼠标按下
    case(osgGA::GUIEventAdapter::PUSH):
    {
        //更新鼠标位置
        _mx=ea.getX();
        _my=ea.getY();
        break;
    }
    //鼠标释放
    case(osgGA::GUIEventAdapter::RELEASE):
    {
        if(_mx==ea.getX() && _my==ea.getY())
        {
            pick(view.get(),ea.getX(),ea.getY());//执行对象选取

//            osg::Vec3 eye1=osg::Vec3(10.0f,0.0f,0.0f);
//            osg::Vec3 center1=osg::Vec3(0.0f,0.0f,0.0f);
//            osg::Vec3 up1=osg::Vec3(0.0f,0.0f,1.0f);

//            view->setCameraManipulator(new osgGA::TrackballManipulator);

//            osg::ref_ptr<osgGA::CameraManipulator> mt=view->getCameraManipulator();
//            mt->setHomePosition(eye1,center1,up1);//后面可以设成全景球的中心
//            view->setCameraManipulator(mt);
            //view->home();
        }
        break;
    }
    default:
        break;
    }
    return false;
}

//对象选取事情处理器
void PickHandler::pick(osg::ref_ptr<osgViewer::View> view, float x, float y)
{
    osg::ref_ptr<osg::Node> node=new osg::Node;
    osg::ref_ptr<osg::Group> parent=new osg::Group;
    //创建一个线段交集检测函数
    osgUtil::LineSegmentIntersector::Intersections intersections;
    if(view->computeIntersections(x,y,intersections))
    {
        osgUtil::LineSegmentIntersector::Intersection intersection=*intersections.begin();
        osg::NodePath& nodePath=intersection.nodePath;
        //得到选择的物体
        node=(nodePath.size()>=1)?nodePath[nodePath.size()-1]:0;
        parent=(nodePath.size()>=2)?dynamic_cast<osg::Group*>(nodePath[nodePath.size()-2]):0;
    }
    //，如果被选中，用一种高亮显示来显示被选中的物体
    if(parent.get()&&node.get())
    {
        osg::ref_ptr<osgFX::Scribe> parentAsScribe=dynamic_cast<osgFX::Scribe*>(parent.get());
        if(!parentAsScribe)
        {
            //如果对象被选中，高亮显示
            osg::ref_ptr<osgFX::Scribe> scribe=new osgFX::Scribe;
            scribe->addChild(node.get());
            parent->replaceChild(node.get(),scribe.get());
        }
        else
        {
            //如果没有被选中，则移除高亮显示
            osg::Node::ParentList parentList=parentAsScribe->getParents();
            for(osg::Node::ParentList::iterator itr=parentList.begin();itr!=parentList.end();++itr)
            {
                (*itr)->replaceChild(parentAsScribe.get(),node.get());
            }
        }
    }
}


