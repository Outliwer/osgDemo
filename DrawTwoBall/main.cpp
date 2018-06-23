//#include <QCoreApplication>

//#include "drawtwoball.h"
//#include "pickhandler.h"

//int main()
//{
//    osg::ref_ptr<osgViewer::Viewer> viewer=new osgViewer::Viewer();
//    PickHandler* p=new PickHandler();
//    viewer->addEventHandler(p);
//    osg::ref_ptr<osg::Group> root=new osg::Group();

//    //读取模型
//    osg::ref_ptr<osg::Node> node=osgDB::readNodeFile("cow.osg");

//    //创建位置变换位置节点pat2
//    osg::ref_ptr<osg::PositionAttitudeTransform> pat2=new osg::PositionAttitudeTransform();
//    pat2->setPosition(osg::Vec3(10.0f,0.0f,0.0f));
//    pat2->addChild(node.get());

//    root->addChild(node.get());
//    root->addChild(pat2.get());

//    printf_s("X:%lf,Y:%lf,Z:%lf\n\n",node->getBound().center().x(),
//             node->getBound().center().y(),
//             node->getBound().center().z());
//    printf_s("X:%lf,Y:%lf,Z:%lf",pat2->getBound().center().x(),
//             pat2->getBound().center().y(),
//             pat2->getBound().center().z());

//    viewer->setUpViewInWindow(100,100,800,600);

//    //优化场景数据
//    osgUtil::Optimizer op;
//    op.optimize(root.get());

//    viewer->setSceneData(root.get());
//    viewer->realize();
//    viewer->run();

//    return 0;

//}

/* -*-c++-*- OpenSceneGraph Cookbook
* Chapter 9 Recipe 1
* Author: Wang Rui <wangray84 at gmail dot com>
*/

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>
#include <QVBoxLayout>
#include <QApplication>


osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h )
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;

    return new osgQt::GraphicsWindowQt(traits.get());
}

class ViewerWidget : public QWidget
{
public:
    ViewerWidget( osgQt::GraphicsWindowQt* gw, osg::Node* scene )
    : QWidget()
    {
        const osg::GraphicsContext::Traits* traits = gw->getTraits();

        osg::Camera* camera = _viewer.getCamera();
        camera->setGraphicsContext( gw );
        camera->setClearColor( osg::Vec4(0.2, 0.2, 0.6, 1.0) );
        camera->setViewport( new osg::Viewport(0, 0, traits->width, traits->height) );
        camera->setProjectionMatrixAsPerspective(
            30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), 1.0f, 10000.0f );

        _viewer.setSceneData( scene );
        _viewer.addEventHandler( new osgViewer::StatsHandler );
        _viewer.setCameraManipulator( new osgGA::TrackballManipulator );
        _viewer.setThreadingModel( osgViewer::Viewer::SingleThreaded );

        QVBoxLayout* layout = new QVBoxLayout;
        layout->addWidget( gw->getGLWidget() );
        setLayout( layout );

        connect( &_timer, SIGNAL(timeout()), this, SLOT(update()) );
        _timer.start( 40 );
    }

protected:
    virtual void paintEvent( QPaintEvent* event )
    { _viewer.frame(); }

    osgViewer::Viewer _viewer;
    QTimer _timer;
};

int main( int argc, char** argv )
{
    QApplication app( argc, argv );
    osgQt::GraphicsWindowQt* gw = createGraphicsWindow( 50, 50, 640, 480 );
    osg::Node* scene = osgDB::readNodeFile("cow.osg");

    ViewerWidget* widget = new ViewerWidget(gw, scene);
    widget->setGeometry( 100, 100, 800, 600 );
    widget->show();
    return app.exec();
}

