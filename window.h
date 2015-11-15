#ifndef WINDOW_H
#define WINDOW_H

#include <QtGui>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QSlider;
QT_END_NAMESPACE
class GLWidget;
class GLWidget2;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

protected:
    void keyPressEvent(QKeyEvent *event);

private:
	QSlider *createSlider();
	QSlider *createZoomSlider();
	QSlider *createtSlider();
	QDial *createVaria();

	QPushButton *createButton();

	GLWidget *glWidget;
	GLWidget2 *glWidget2;

	QDoubleSpinBox *densiteSpinBox;
	QSpinBox *maillesSpinBox;

	QSlider *zoomSlider;
	QSlider *xSlider;
	QSlider *ySlider;
	QSlider *zSlider;

	QSlider *xtSlider;
	QSlider *ytSlider;
	QSlider *ztSlider;

	QDial *variaEcrasement;
	QDial *variaCouleur;

	QCheckBox *bouton;
	QCheckBox *boutonDela;
	QCheckBox *boutonLight;
	QCheckBox *boutonTopoli;
	QCheckBox *boutonIsoligne2d;
	QCheckBox *boutonIsoligne3d;

};

#endif
