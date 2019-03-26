#ifndef OGLWIDGET_H
#define OGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class OGLWidget : public QOpenGLWidget,
                  protected QOpenGLFunctions
{
    Q_OBJECT

public:
    OGLWidget(QWidget *parent = nullptr);
    ~OGLWidget();

public slots:
    void setParamA( int newa );
    void setParamB( int newb );
    void setParamC( int newc );
    void setParamD( int newd );
protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

protected:
    int parama;
    int paramb;
    int paramc;
    int paramd;

};


#endif // OGLWIDGET_H
