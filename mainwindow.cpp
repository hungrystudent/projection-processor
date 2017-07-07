#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

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

void MainWindow::valueChanged(int i)
{
    int xData;
    int yData;
    int zData;
    qDebug() << "------S------";
    qDebug() << spinboxX->value();
    qDebug() << spinboxY->value();
    qDebug() << spinboxZ->value();
    qDebug() << "------E------";
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

