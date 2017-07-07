#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "wcontextnavigation.h"
#include "wgldatageomstacktriangulated.h"
#include "wglmaterialsurface.h"
#include "wglmaterialwireframe.h"
#include "wglobjectrenderer.h"
#include "wglgrid.h"

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
    QSpinBox *spinboxX;
    QSpinBox *spinboxY;
    QSpinBox *spinboxZ;
protected:
    void initializeViewport();
    void deinitializeViewport();
    void clearGeometry();
    bool hasGeometry() const;
protected slots:
    void loadGeometryFromFile();
    void fitToView();
    void valueChanged(int i);
};

#endif // MAINWINDOW_H
