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
    layout->addWidget(viewport);
    centralWidget()->setLayout(layout);
    spinboxX = new QSpinBox();
    spinboxY = new QSpinBox();
    spinboxZ = new QSpinBox();

    QObject::connect(spinboxX, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    QObject::connect(spinboxY, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    QObject::connect(spinboxZ, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));

    layout->addWidget(spinboxX);
    layout->addWidget(spinboxY);
    layout->addWidget(spinboxZ);

    glGrid = new WGLGrid(20,1,WGLGrid::Axis_X,WGLGrid::Axis_Z,10);
    glGrid->setColor(QColor(60,60,60));
    viewport->addObject(glGrid);
    glMaterialSurface = new WGLMaterialSurface();
    glMaterialWireframe = new WGLMaterialWireframe();

    QVector<QVector3D> vertices;
    vertices = geom->v;
    int vertCount = geom->v.count();
    QVector<int> indexArray(vertCount);
    for (int vIndex=0; vIndex < vertCount; vIndex++){
        indexArray[vIndex]=vIndex;
    }
    geomTree = KDTree::createTree(vertices,indexArray,0);

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
}

void MainWindow::fitToView()
{
    WBoundingBox boundingBox(QVector3D(-1,-1,-1) * 5, QVector3D(1,1,1) * 5);
    if (hasGeometry())
        boundingBox = WBoundingBox(geom->v);
    camera->fitToView(boundingBox,viewport->size());
    viewport->updateGL();
}

void MainWindow::valueChanged()
{
    QVector3D dot((float)spinboxX->value(),(float)spinboxY->value(),(float)spinboxZ->value());
    KDTreeNode *finded;
    finded = KDTree::findClosest(geomTree,dot,0);
    createDots();
//    qDebug() << "------S------";
//    qDebug() << spinboxX->value();
//    qDebug() << spinboxY->value();
//    qDebug() << spinboxZ->value();
//    qDebug() << "------E------";
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

void MainWindow::createDots()
{
    QVector<QVector3D> dots = { QVector3D(0,0,0),QVector3D(1,0,0),QVector3D(0,1,0),QVector3D(0,0,1) };
    glDots = new WGLDots(dots);
    glDots->setPointSize(3);
    glDots->setColor(QColor(255,0,255));
    viewport->addObject(glDots,WViewport::Overlay);
}

void MainWindow::clearDots()
{
    viewport->removeObject(glDots,WViewport::Overlay);
    delete glDots;
    glDots = nullptr;
}
