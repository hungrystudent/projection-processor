#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wcontextnavigation.h"
#include "wgldatageomstacktriangulated.h"
#include "wglmaterialsurface.h"
#include "wglmaterialwireframe.h"
#include "wglobjectrenderer.h"
#include "wglgrid.h"
#include <kdtreenode.h>
#include "wgldots.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    Wrap::WCamera3D *camera = nullptr;
    Wrap::WViewport *viewport = nullptr;
    Wrap::WContextNavigation *contextNavigation = nullptr;
    Wrap::WGLMaterialSurface *glMaterialSurface = nullptr;
    Wrap::WGLMaterialWireframe *glMaterialWireframe = nullptr;
    Wrap::WGLGrid *glGrid = nullptr;
    GeometryStack2::GeomStackTriangulated *geom = nullptr;
    Wrap::WGLDataGeomStackTriangulated *glData = nullptr;
    Wrap::WGLObjectRenderer *glRenderer = nullptr;
    QDoubleSpinBox *spinboxX;
    QDoubleSpinBox *spinboxY;
    QDoubleSpinBox *spinboxZ;
    KDTreeNode *geomTree;
    Wrap::WGLDots *glDots = nullptr;
    Wrap::WGLDots *srchglDots = nullptr;
protected:
    void initializeViewport();
    void deinitializeViewport();
    void clearGeometry();
    bool hasGeometry() const;
    void createDots(const QVector3D &coords,const QVector3D &dotToFind);
    void clearDots();
    bool hasDots() const;
protected slots:
    void loadGeometryFromFile();
    void fitToView();
    void valueChanged(double d);
};

#endif // MAINWINDOW_H
