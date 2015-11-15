#include <QtGui>
#include "glwidget.h"
#include "glwidget2.h"
#include "window.h"

Window::Window()
{
	glWidget = new GLWidget;
	glWidget2 = new GLWidget2;

	

	QTabWidget *onglets = new QTabWidget;
	QWidget *page1 = new QWidget;
	QWidget *page2 = new QWidget;

	xSlider = createSlider();
	ySlider = createSlider();
	zSlider = createSlider();
	xtSlider = createtSlider();
	ytSlider = createtSlider();
	ztSlider = createtSlider();
	zoomSlider = createZoomSlider();

	QDoubleSpinBox *densiteSpinBox = new QDoubleSpinBox;
	densiteSpinBox->setRange(0.01,0.40);
	densiteSpinBox->setSingleStep(0.01);

	connect(densiteSpinBox, SIGNAL(valueChanged(double)), glWidget, SLOT(setp(double)));
	connect(glWidget, SIGNAL(pChanged(double)), densiteSpinBox, SLOT(setValue(double)));

	QSpinBox *mailleSpinBox = new QSpinBox;
	mailleSpinBox->setRange(70,170);
	mailleSpinBox->setSingleStep(1);

	connect(mailleSpinBox, SIGNAL(valueChanged(int)), glWidget, SLOT(setcarre(int)));
	connect(glWidget, SIGNAL(carreChanged(int)), mailleSpinBox, SLOT(setValue(int)));

	variaEcrasement = createVaria();
	variaCouleur = createVaria();

	QGroupBox *groupbox1 = new QGroupBox("Affichage");
	QGroupBox *groupbox2 = new QGroupBox("Parametres");
	QGroupBox *groupboxRot = new QGroupBox("Rotation");
	QGroupBox *groupboxZoo = new QGroupBox("Zoom");
	QGroupBox *groupboxVar = new QGroupBox("Variables");
	QGroupBox *groupboxTra = new QGroupBox("Translation");

	connect(variaCouleur, SIGNAL(valueChanged(int)), glWidget, SLOT(setVariaCouleur(int)));
	connect(glWidget, SIGNAL(variaCouleurChanged(int)), variaCouleur, SLOT(setValue(int)));

	connect(variaEcrasement, SIGNAL(valueChanged(int)), glWidget, SLOT(setVariaEcrasement(int)));
	connect(glWidget, SIGNAL(variaEcrasementChanged(int)), variaEcrasement, SLOT(setValue(int)));

	connect(zoomSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZoomRotation(int)));
	connect(glWidget, SIGNAL(zoomRotationChanged(int)), zoomSlider, SLOT(setValue(int)));

	connect(xSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXRotation(int)));
	connect(glWidget, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
	connect(ySlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYRotation(int)));
	connect(glWidget, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
	connect(zSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZRotation(int)));
	connect(glWidget, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

	connect(xtSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setXTranslation(int)));
	connect(glWidget, SIGNAL(xTranslationChanged(int)), xtSlider, SLOT(setValue(int)));
	connect(ytSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setYTranslation(int)));
	connect(glWidget, SIGNAL(yTranslationChanged(int)), ytSlider, SLOT(setValue(int)));
	connect(ztSlider, SIGNAL(valueChanged(int)), glWidget, SLOT(setZTranslation(int)));
	connect(glWidget, SIGNAL(zTranslationChanged(int)), ztSlider, SLOT(setValue(int)));


	connect(variaCouleur, SIGNAL(valueChanged(int)), glWidget2, SLOT(setVariaCouleur(int)));
	connect(glWidget2, SIGNAL(variaCouleurChanged(int)), variaCouleur, SLOT(setValue(int)));

	connect(variaEcrasement, SIGNAL(valueChanged(int)), glWidget2, SLOT(setVariaEcrasement(int)));
	connect(glWidget2, SIGNAL(variaEcrasementChanged(int)), variaEcrasement, SLOT(setValue(int)));

	connect(zoomSlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setZoomRotation(int)));
	connect(glWidget2, SIGNAL(zoomRotationChanged(int)), zoomSlider, SLOT(setValue(int)));

	connect(xSlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setXRotation(int)));
	connect(glWidget2, SIGNAL(xRotationChanged(int)), xSlider, SLOT(setValue(int)));
	connect(ySlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setYRotation(int)));
	connect(glWidget2, SIGNAL(yRotationChanged(int)), ySlider, SLOT(setValue(int)));
	connect(zSlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setZRotation(int)));
	connect(glWidget2, SIGNAL(zRotationChanged(int)), zSlider, SLOT(setValue(int)));

	connect(xtSlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setXTranslation(int)));
	connect(glWidget2, SIGNAL(xTranslationChanged(int)), xtSlider, SLOT(setValue(int)));
	connect(ytSlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setYTranslation(int)));
	connect(glWidget2, SIGNAL(yTranslationChanged(int)), ytSlider, SLOT(setValue(int)));
	connect(ztSlider, SIGNAL(valueChanged(int)), glWidget2, SLOT(setZTranslation(int)));
	connect(glWidget2, SIGNAL(zTranslationChanged(int)), ztSlider, SLOT(setValue(int)));


	QHBoxLayout *mainLayout = new QHBoxLayout;
	

	QVBoxLayout *LayoutRZT = new QVBoxLayout;

	QVBoxLayout *LayoutRot = new QVBoxLayout;
	QVBoxLayout *LayoutZoo = new QVBoxLayout;
	QVBoxLayout *LayoutVar = new QVBoxLayout;
	QVBoxLayout *LayoutTra = new QVBoxLayout;

	QVBoxLayout *LayoutFusion = new QVBoxLayout;

	QHBoxLayout *LayoutTab1 = new QHBoxLayout;
	QHBoxLayout *LayoutTab2 = new QHBoxLayout;

	QLabel *labelRotx = new QLabel("autour de x");
	labelRotx->setFont(QFont("Comic Sans MS", 7));
	QLabel *labelRoty = new QLabel("autour de y");
	labelRoty->setFont(QFont("Comic Sans MS", 7));
	QLabel *labelRotz = new QLabel("autour de z");
	labelRotz->setFont(QFont("Comic Sans MS", 7));

	QLabel *labelTrax = new QLabel("selon de x");
	labelTrax->setFont(QFont("Comic Sans MS", 7));
	QLabel *labelTray = new QLabel("selon de y");
	labelTray->setFont(QFont("Comic Sans MS", 7));
	QLabel *labelTraz = new QLabel("selon de z");
	labelTraz->setFont(QFont("Comic Sans MS", 7));

	LayoutRot->addWidget(labelRotx);
	LayoutRot->addWidget(xSlider);
	LayoutRot->addWidget(labelRoty);
	LayoutRot->addWidget(ySlider);
	LayoutRot->addWidget(labelRotz);
	LayoutRot->addWidget(zSlider);

	groupboxRot->setLayout(LayoutRot);

	QLabel *labelVar = new QLabel("densite");
	labelVar->setFont(QFont("Comic Sans MS", 7));

	QLabel *labelMai = new QLabel("Nombre de maille");
	labelMai->setFont(QFont("Comic Sans MS", 7));

	LayoutVar->addWidget(labelVar);
	LayoutVar->addWidget(densiteSpinBox);
	LayoutVar->addWidget(labelMai);
	LayoutVar->addWidget(mailleSpinBox);
	groupboxVar->setLayout(LayoutVar);

	LayoutZoo->addWidget(zoomSlider);
	groupboxZoo->setLayout(LayoutZoo);

	LayoutTra->addWidget(labelTrax);
	LayoutTra->addWidget(xtSlider);
	LayoutTra->addWidget(labelTray);
	LayoutTra->addWidget(ytSlider);
	LayoutTra->addWidget(labelTraz);
	LayoutTra->addWidget(ztSlider);
	//mainLayout->addWidget(m_bouton);
	groupboxTra->setLayout(LayoutTra);
	//QVBoxLayout *secondoLayout = new QVBoxLayout;
	QVBoxLayout *secondLayout = new QVBoxLayout;
	//mainLayout->addLayout(secondLayout);
	LayoutRZT->addWidget(groupboxRot);
	LayoutRZT->addWidget(groupboxTra);
	LayoutRZT->addWidget(groupboxZoo);
	LayoutRZT->addWidget(groupboxVar);

	mainLayout->addLayout(LayoutRZT);

	LayoutTab1->addWidget(glWidget);
	LayoutTab2->addWidget(glWidget2);
	page1->setLayout(LayoutTab1);
	page2->setLayout(LayoutTab2);
	onglets->addTab(page1,"Triangulation");
	onglets->addTab(page2,"Isolignes");
	mainLayout->addWidget(onglets);

	//mainLayout->addWidget(glWidget);
	//groupbox1->setLayout(secondLayout);


	QLabel *labelAffichage = new QLabel("Affichage");
	labelAffichage->setFont(QFont("Comic Sans MS", 9));

	QCheckBox *bouton = new QCheckBox("topographie");
	bouton->setFont(QFont("Comic Sans MS", 7));
	//bouton->setCheckable(true);
	connect(bouton, SIGNAL(clicked()), glWidget, SLOT(setBooltopo()));
	connect(bouton, SIGNAL(clicked()), glWidget2, SLOT(setBooltopo()));

	QCheckBox *boutonDela = new QCheckBox("triangulation native"); 
	boutonDela->setFont(QFont("Comic Sans MS", 7));
	connect(boutonDela, SIGNAL(clicked()), glWidget, SLOT(setBooldela()));
	connect(boutonDela, SIGNAL(clicked()), glWidget2, SLOT(setBooldela()));

	QCheckBox *boutonLight = new QCheckBox("triangulation light");
	boutonLight->setFont(QFont("Comic Sans MS", 7));
	connect(boutonLight, SIGNAL(clicked()), glWidget, SLOT(setBoollight()));
	//connect(boutonLight, SIGNAL(clicked()), glWidget2, SLOT(setBoollight()));


	QCheckBox *boutonTopoli = new QCheckBox("topographie light");
	boutonTopoli->setFont(QFont("Comic Sans MS", 7));
	connect(boutonTopoli, SIGNAL(clicked()), glWidget, SLOT(setBooltopoli()));
	//connect(boutonTopoli, SIGNAL(clicked()), glWidget2, SLOT(setBooltopoli()));

	QCheckBox *boutonIsoligne2d = new QCheckBox("Isolignes 2D");
	boutonIsoligne2d->setFont(QFont("Comic Sans MS", 7));
	connect(boutonIsoligne2d, SIGNAL(clicked()), glWidget2, SLOT(setBoolisoligne2d()));

	QCheckBox *boutonIsoligne3d = new QCheckBox("Isolignes 3D");
	boutonIsoligne3d->setFont(QFont("Comic Sans MS", 7));
	connect(boutonIsoligne3d, SIGNAL(clicked()), glWidget2, SLOT(setBoolisoligne3d()));

	secondLayout->addWidget(bouton);
	secondLayout->addWidget(boutonDela);
	secondLayout->addWidget(boutonTopoli);
	secondLayout->addWidget(boutonLight);
	secondLayout->addWidget(boutonIsoligne2d);
	secondLayout->addWidget(boutonIsoligne3d);


	groupbox1->setLayout(secondLayout);

	//mainLayout->addWidget(groupbox1);
	

	QLabel *labelEcrasement = new QLabel("ecrasement");
	labelEcrasement->setFont(QFont("Comic Sans MS", 7));
	QLabel *labelCouleur = new QLabel("couleur");
	labelCouleur->setFont(QFont("Comic Sans MS", 7));
	QVBoxLayout *thirdLayout = new QVBoxLayout;
	thirdLayout->addWidget(labelEcrasement);
	thirdLayout->addWidget(variaEcrasement);
	thirdLayout->addWidget(labelCouleur);
	thirdLayout->addWidget(variaCouleur);
	groupbox2->setLayout(thirdLayout);

	LayoutFusion->addWidget(groupbox1);
	LayoutFusion->addWidget(groupbox2);

	mainLayout->addLayout(LayoutFusion);

	setLayout(mainLayout);

	mailleSpinBox->setValue(140);
	densiteSpinBox->setValue(0.4);
	xSlider->setValue(15 * 16);
	ySlider->setValue(345 * 16);
	zSlider->setValue(0 * 16);
	xtSlider->setValue(100);
	ytSlider->setValue(100);
	ztSlider->setValue(100);
	zoomSlider->setValue(10*16);
	variaEcrasement->setValue(1*100);
	variaCouleur->setValue(1*100);
	setWindowTitle(tr("todelideis"));
}
//! [1]



QPushButton *Window::createButton()
{
    QPushButton *bouton = new QPushButton("push_it", this);
 
    bouton->setFont(QFont("Comic Sans MS", 7));

	bouton->setMaximumSize (100,20);
	return bouton;
}


QDial *Window::createVaria()
{
    QDial *slider = new QDial();
    slider->setRange(1*10,2*100);
    slider->setSingleStep(1);
    //slider->setPageStep(15 * 16);
    //slider->setTickInterval(15 * 16);
    //slider->setTickPosition(QSlider::TicksRight);

	//slider->setMaximumSize (100,20);
    return slider;
}

QSlider *Window::createZoomSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(2*16,30*16);
    slider->setSingleStep(1);
	slider->setMaximumSize (100,20);
    return slider;
}

QSlider *Window::createtSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(1,200);
    slider->setSingleStep(10);
	slider->setMaximumSize (100,20);
    return slider;
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    //slider->setPageStep(15 * 16);
    //slider->setTickInterval(15 * 16);
    //slider->setTickPosition(QSlider::TicksRight);
	slider->setMaximumSize (100,20);
    return slider;
}
//! [2]

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
