#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <kdtree.h>
#include <kdtreenode.h>

using namespace Wrap;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu *menuEdit = menuBar()->addMenu("Edit");
    menuEdit->addAction("Load geometry",this,&MainWindow::loadGeometryFromFile,QKeySequence::Open);
    menuEdit->addAction("Fit to view",this,&MainWindow::fitToView,QKeySequence(Qt::Key_F));


    initializeViewport();

    //    QKeyEvent event(QKeyEvent::KeyPress, Qt::Key_S, Qt::KeyboardModifiers());

    //    contextNavigation->onKeyPress(&event);

    //    QQuaternion rotation = contextNavigation->rotation;
    //    rotation = snapQuatToWorldAxis(rotation);
    //    contextNavigation->rotation = rotation;
    //    contextNavigation->updateCameraRotation();
}

MainWindow::~MainWindow()
{
    if (hasGeometry())
        clearGeometry();
    deinitializeViewport();
    delete ui;
}

void MainWindow::initializeViewport()
{
    camera = new WCamera3D(25,QVector3D(0,0,3),QVector3D(),WCamera3D::Perspective,0.01,1000);
    viewport = new WViewport(camera);
    viewport->makeCurrent();
    contextNavigation = new WContextNavigation(viewport,camera);
    contextNavigation->setRotationMode(WContextNavigation::Standard);
    //setCentralWidget(viewport);

    QVBoxLayout *layout = new QVBoxLayout();
    QHBoxLayout *hlayout = new QHBoxLayout();
    layout->addWidget(viewport);
    centralWidget()->setLayout(layout);
    spinboxX = new QDoubleSpinBox();
    spinboxY = new QDoubleSpinBox();
    spinboxZ = new QDoubleSpinBox();

    spinboxX->setMinimum(-100);
    spinboxX->setMaximum(100);
    spinboxY->setMinimum(-100);
    spinboxY->setMaximum(100);
    spinboxZ->setMinimum(-100);
    spinboxZ->setMaximum(100);

    QObject::connect(
                spinboxX, SIGNAL(valueChanged(double )),
                this, SLOT(valueChanged(double )));
    QObject::connect(
                spinboxY, SIGNAL(valueChanged(double )),
                this, SLOT(valueChanged(double )));
    QObject::connect(
                spinboxZ, SIGNAL(valueChanged(double )),
                this, SLOT(valueChanged(double )));

    hlayout->addWidget(spinboxX);
    hlayout->addWidget(spinboxY);
    hlayout->addWidget(spinboxZ);
    layout->addLayout(hlayout);
    glGrid = new WGLGrid(20,1,WGLGrid::Axis_X,WGLGrid::Axis_Z,10);
    glGrid->setColor(QColor(60,60,60));
    viewport->addObject(glGrid);
    glMaterialSurface = new WGLMaterialSurface();
    glMaterialWireframe = new WGLMaterialWireframe();

}

void MainWindow::deinitializeViewport()
{
    viewport->removeObject(glGrid);
    delete glGrid;
    delete glMaterialSurface;
    delete glMaterialWireframe;
    delete contextNavigation;
    delete viewport;
    delete camera;
}

void MainWindow::loadGeometryFromFile()
{
    if (hasGeometry())
        clearGeometry();
    const QString fileName = QFileDialog::getOpenFileName(this,"Load geometry",QString(),"OBJ-file (*.obj)");
    if (fileName.isNull())
        return;
    QString errorMsg;
    geom = new GeometryStack2::GeomStackTriangulated(fileName,errorMsg);
    if (!errorMsg.isNull())
        qFatal(QString("Can not load file: %1").arg(fileName).toUtf8().constData());
    glData = new WGLDataGeomStackTriangulated(*geom);
    glRenderer = new WGLObjectRenderer(glData,glMaterialSurface,WGLObjectRenderer::CullFace_Back,true);
    glRenderer->addRenderPass(glMaterialWireframe,WGLObjectRenderer::CullFace_None,false);
    viewport->addObject(glRenderer);
    fitToView();


    QVector<QVector3D> vertices;
    vertices = geom->v;
    int vertCount = geom->v.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    geomTree = KDTree::createTree(vertices,indexArray,0);

}

void MainWindow::fitToView()
{
    WBoundingBox boundingBox(QVector3D(-1,-1,-1) * 5, QVector3D(1,1,1) * 5);
    if (hasGeometry())
        boundingBox = WBoundingBox(geom->v);
    camera->fitToView(boundingBox,viewport->size());
    viewport->updateGL();
}

void MainWindow::valueChanged(double d)
{
    if (hasDots())
        clearDots();
    QVector3D dot((float)spinboxX->value(),(float)spinboxY->value(),(float)spinboxZ->value());
    KDTreeNode *finded;
    finded = KDTree::findClosest(geomTree,dot,0);
    qDebug() << finded->coordinates;
    createDots(finded->coordinates,dot);
    viewport->updateGL();
}

void MainWindow::clearGeometry()
{
    Q_ASSERT(hasGeometry());
    viewport->removeObject(glRenderer);
    delete glRenderer;
    glRenderer = nullptr;
    delete glData;
    glData = nullptr;
    delete geom;
    geom = nullptr;
}

bool MainWindow::hasGeometry() const
{
    return geom != nullptr;
}

void MainWindow::createDots(const QVector3D &coords,const QVector3D &dotToFind)
{
    QVector<QVector3D> dots = { coords };
    glDots = new WGLDots(dots);
    glDots->setPointSize(3);
    glDots->setColor(QColor(255,0,255));
    viewport->addObject(glDots,WViewport::Overlay);

    QVector<QVector3D> dotsTofind = { dotToFind };
    srchglDots = new WGLDots(dotsTofind);
    srchglDots->setPointSize(4);
    srchglDots->setColor(QColor(250,250,0));

    viewport->addObject(srchglDots,WViewport::Overlay);
}

void MainWindow::clearDots()
{
    viewport->removeObject(glDots,WViewport::Overlay);
    viewport->removeObject(srchglDots,WViewport::Overlay);
    delete glDots;
    delete srchglDots;
    glDots = nullptr;
    srchglDots = nullptr;
}

bool MainWindow::hasDots() const
{
    return glDots != nullptr;
}
