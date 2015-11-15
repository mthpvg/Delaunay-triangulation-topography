#ifndef GLWIDGET2_H
#define GLWIDGET2_H

#include <QtGui>
#include <QGLWidget>

class GLWidget2 : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget2(QWidget *parent = 0);
    ~GLWidget2();

    //QSize minimumSizeHint() const;
    QSize sizeHint() const;

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
	void setZoomRotation(int zoom);
	void setBooltopo();
	void setBooldela();
	//void setBoollight();
	//void setBooltopoli();
	void setBoolisoligne2d();
	void setBoolisoligne3d();
	void setXTranslation(int tra);
	void setYTranslation(int tra);
	void setZTranslation(int tra);
	void setVariaEcrasement(int ecrase);
	void setVariaCouleur(int couleur);

signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);
	void zoomRotationChanged(int zoom);
	void variaEcrasementChanged(int ecrase);
	void variaCouleurChanged(int couleur);

	void boolTopoChanged();
	void boolDelaChanged();
	//void boolLightChanged();
	//void boolTopoliChanged();
	void boolIsoligne2dChanged();
	void boolIsoligne3dChanged();

	void xTranslationChanged(int tra);
	void yTranslationChanged(int tra);
	void zTranslationChanged(int tra);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:

	int xRot;
	int yRot;
	int zRot;

	int xTra;
	int yTra;
	int zTra;

	bool topoBool;
	bool delaBool;
	//bool lightBool;
	//bool topoliBool;
	bool isoligneBool2d;
	bool isoligneBool3d;

	int azoom;
	int aecrase;
	double daecrase;
	int acouleur;
	double dacouleur;
	double p;
	double piso;
	double gdz;
	//double gdzl;
	double neuf_isolignes[9][140*140/2];
	double isolignes[140*140/2];
	double polic[4][140*140/2];
	double points[4][140*140/2];
	double triangles[4][2*140*140/2-2-4];
	double triangles_light[4][2*140*140/2-2-4];
	double voisins[140*140/2][140*140/2];
	double voisins_light[140*140/2][140*140/2];

	int npoints;
	int nlighter;
	int cisolignes;
	double hauteur_cube;
	QPoint lastPos;
	QColor qtGreen;
	QColor qtPurple;
};

#endif
