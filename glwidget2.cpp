#include <QtGui>
#include <QtOpenGL>

#include <math.h>
#include <iostream>


#include "glwidget2.h"

extern "C" void topogen_ (double (*points)[140*140/2], int *,int *,double *,int *);
extern "C" void delaunay_ (double (*points)[140*140/2],double (*triangles)[2*140*140/2-2-4],double (*voisins)[140*140/2],int *,int *,int *,double *);
//extern "C" void lighter_ (double (*points)[140*140/2],double (*voisins)[140*140/2],double (*polic)[140*140/2],int *,int *,int *, int *);
extern "C" void isoligne_ (double (*points)[140*140/2],double (*voisins)[140*140/2],double *,double *,int *,int *,int *,int *);



GLWidget2::GLWidget2(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	xRot = 0;
	yRot = 0;
	zRot = 0;
	xTra = 100;
	yTra = 100;
	zTra = 100;
	hauteur_cube=0;
	topoBool=false;
	delaBool=false;
	//lightBool=false;
	//topoliBool=false;
	isoligneBool2d=false;
	isoligneBool3d=false;
	azoom = 24;
	aecrase = 100;
	daecrase=aecrase/100.;
	acouleur = 100;
	dacouleur=acouleur/100.;

	qtGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
	qtPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

	int l=4;
	int c=140*140/2;
	p=0.4;
	piso=0.5;

	npoints=140;
	topogen_ (points,&l,&c,&p,&npoints);

	delaunay_ (points,triangles,voisins,&npoints,&l,&c,&gdz);

	//lighter_ (points,voisins,polic,&l,&c,&npoints,&nlighter);

	//delaunay_ (polic,triangles_light,voisins_light,&nlighter,&l,&c,&gdzl);



	for (int i=0;i<8;i++)
	{
		cisolignes=0;
		piso=0.1*(i+1);
		isoligne_ (points,voisins,isolignes,&piso,&l,&c,&npoints,&cisolignes);
		neuf_isolignes[i][0]=cisolignes;
	for (int j=1;j<neuf_isolignes[i][0];j++)
	{
		neuf_isolignes[i][j]=isolignes[j];
	}
	}

	for (int i=0; i<npoints;i++)
	{
		points[0][i]=points[0][i]/140-0.5;
		points[1][i]=points[1][i]/140-0.5;
		points[2][i]=(points[2][i]/gdz-0.5)/3.;
	}

	/*for (int i=0; i<nlighter;i++)
	{
		polic[0][i]=polic[0][i]/140-0.5;
		polic[1][i]=polic[1][i]/140-0.5;
		polic[2][i]=(polic[2][i]/gdzl-0.5)/3.;
	}*/

}

GLWidget2::~GLWidget2()
{
}

/*QSize GLWidget2::minimumSizeHint() const
{
    return QSize(200, 200);
}*/

QSize GLWidget2::sizeHint() const
{
    return QSize(950, 950);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360 * 16)
        angle -= 360 * 16;
}

void GLWidget2::setBooltopo()
{
	if (topoBool==false){
		topoBool=true;}
	else{
		topoBool=false;
	}
	emit boolTopoChanged();
        updateGL();
}

void GLWidget2::setBooldela()
{
	if (delaBool==false){
		delaBool=true;}
	else{
		delaBool=false;
	}
	emit boolDelaChanged();
        updateGL();
}

/*void GLWidget2::setBoollight()
{
	if (lightBool==false){
		lightBool=true;}
	else{
		lightBool=false;
	}
	emit boolLightChanged();
        updateGL();
}*/

/*void GLWidget2::setBooltopoli()
{
	if (topoliBool==false){
		topoliBool=true;}
	else{
		topoliBool=false;
	}
	emit boolTopoliChanged();
        updateGL();
}*/

void GLWidget2::setBoolisoligne2d()
{
	if (isoligneBool2d==false){
		isoligneBool2d=true;}
	else{
		isoligneBool2d=false;
	}
	emit boolIsoligne2dChanged();
        updateGL();
}

void GLWidget2::setBoolisoligne3d()
{
	if (isoligneBool3d==false){
		isoligneBool3d=true;}
	else{
		isoligneBool3d=false;
	}
	emit boolIsoligne3dChanged();
        updateGL();
}

void GLWidget2::setVariaEcrasement(int ecrase)
{
	aecrase=ecrase;
	emit variaEcrasementChanged(ecrase);
        updateGL();
}

void GLWidget2::setVariaCouleur(int couleur)
{
	acouleur=couleur;
	emit variaCouleurChanged(couleur);
        updateGL();
}

void GLWidget2::setZoomRotation(int zoom)
{
	azoom=zoom/16;
	emit zoomRotationChanged(zoom);
        updateGL();
}

void GLWidget2::setXTranslation(int tra)
{
	xTra=tra;
	emit xTranslationChanged(tra);
        updateGL();
}
void GLWidget2::setYTranslation(int tra)
{
	yTra=tra;
	emit yTranslationChanged(tra);
        updateGL();
}
void GLWidget2::setZTranslation(int tra)
{
	zTra=tra;
	emit zTranslationChanged(tra);
        updateGL();
}

void GLWidget2::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != xRot) {
        xRot = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void GLWidget2::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != yRot) {
        yRot = angle;
        emit yRotationChanged(angle);
        updateGL();
    }
}

void GLWidget2::setZRotation(int angle)
{
	qNormalizeAngle(angle);
	if (angle != zRot) {
		zRot = angle;
		emit zRotationChanged(angle);
		updateGL();
	}
}

void GLWidget2::initializeGL()
{
	//qglClearColor(220,220,220);
	qglClearColor(qtPurple.dark());
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//    glEnable(GL_MULTISAMPLE);
	// static GLfloat lightPosition[4] = { 1.5, 1.5, 1.5, 1.0 };
	//  glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

}

void GLWidget2::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();


	if(isoligneBool2d)
	{
		glOrtho(-0.5, +0.5,-0.5, +0.5,-0.5, +0.5 );
		//glFlush();
		setXRotation(0);
		setYRotation(0);
		setZRotation(0);
	}
	else
	{

		glTranslatef(0.0,0.0,1.-zTra/100.);
		glTranslatef(0.0,1.-yTra/100.,0.0);
		glTranslatef(1.-xTra/100.,0.0,0.0);
		glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
		glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
		glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);

		glOrtho(-0.1*azoom, +0.1*azoom, -0.1*azoom, +0.1*azoom, -0.1*azoom, 0.1*azoom);
	}
			glPushMatrix();

			daecrase=aecrase/100.;
			dacouleur=acouleur/100.;


			
			if (delaBool && !isoligneBool2d){
			
			for (int i=0; i<2*npoints-6;i++)
				{
				double h;
				h=((points[2][int(triangles[0][i]-1)]+points[2][int(triangles[1][i]-1)]+points[2][int(triangles[2][i]-1)])*gdz+1.5)/3.;
				h=dacouleur*h*0.2+0.4;
				glColor3f (h,h,h);
					glBegin(GL_LINE_LOOP);
					glVertex3d (points[0][int(triangles[0][i]-1)],points[1][int(triangles[0][i]-1)],points[2][int(triangles[0][i]-1)]*daecrase);
					glVertex3d (points[0][int(triangles[1][i]-1)],points[1][int(triangles[1][i]-1)],points[2][int(triangles[1][i]-1)]*daecrase);
					glVertex3d (points[0][int(triangles[2][i]-1)],points[1][int(triangles[2][i]-1)],points[2][int(triangles[2][i]-1)]*daecrase);
					glEnd();
				}
				hauteur_cube=0.;
			
			}


			if(isoligneBool2d || isoligneBool3d){


				if(isoligneBool2d){
					glColor3f (0.,0.,0.);
					glBegin(GL_LINE_LOOP);
					glVertex3d(points[0][0],points[1][0],-0.4*daecrase);
					glVertex3d(points[0][1],points[1][1],-0.4*daecrase);
					glVertex3d(points[0][3],points[1][3],-0.4*daecrase);
					glVertex3d(points[0][2],points[1][2],-0.4*daecrase);
					glEnd();
					
				}

				glPointSize(5.);
				for (int i=0; i<8;i++)
				{
				//std::cout<<"cisolignes = "<<neuf_isolignes[i][0]<<std::endl;
				//std::cout<<"neuf = "<<neuf_isolignes[i][0]<<std::endl;

								double h;
				h=(points[2][int(neuf_isolignes[i][1]-1)]*gdz+0.5);
				h=dacouleur*h*0.2+0.4;
				
				
				//glBegin(GL_LINE_STRIP);			
				for (int j=1; j<neuf_isolignes[i][0];j++)
				{

										glColor3f (dacouleur*1.,0.,0.);
										//if (i==1){glColor3f (1.,1.,1.);}
										if (i==1){glColor3f (dacouleur*1.,dacouleur*1.,dacouleur*1.);}
										if (i==2){glColor3f (dacouleur*1.,dacouleur*1.,dacouleur*1.);}
										if (i==3){glColor3f (dacouleur*0.5,dacouleur*0.5,dacouleur*0.5);}
										if (i==4){glColor3f (dacouleur*1.,dacouleur*1.,0.);}
										if (i==5){glColor3f (0.,dacouleur*1.,0.);}
										if (i==6){glColor3f (0.,0.,dacouleur*1.);}
										//if (i==8){glColor3f (1.,0.,0.);}

					glBegin(GL_POINTS);
					//glBegin(GL_TRIANGLES);
					if(isoligneBool2d){
						glPointSize(2.);
						glVertex3d(points[0][int(neuf_isolignes[i][j]-1)],points[1][int(neuf_isolignes[i][j]-1)],-0.4*daecrase);
					}

					if(isoligneBool3d && !isoligneBool2d){
						glPointSize(5.);
						glVertex3d(points[0][int(neuf_isolignes[i][j]-1)],points[1][int(neuf_isolignes[i][j]-1)],points[2][int(neuf_isolignes[i][j]-1)]*daecrase);
					}

					glEnd();
					
				}
					
				}
			}			

			/*glBegin(GL_LINE_LOOP);
				glVertex3d(points[0][0],points[1][0],-0.4*daecrase);
				glVertex3d(points[0][1],points[1][1],-0.4*daecrase);
				glVertex3d(points[0][3],points[1][3],-0.4*daecrase);
				glVertex3d(points[0][2],points[1][2],-0.4*daecrase);
			glEnd();

			glBegin(GL_LINE_LOOP);
				glVertex3d(points[0][0],points[1][0],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][1],points[1][1],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][3],points[1][3],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][2],points[1][2],0.2*daecrase+hauteur_cube);
			glEnd();

			glBegin(GL_LINES);
				glVertex3d(points[0][0],points[1][0],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][0],points[1][0],-0.4*daecrase);
			glEnd();

			glBegin(GL_LINES);
				glVertex3d(points[0][1],points[1][1],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][1],points[1][1],-0.4*daecrase);
			glEnd();

			glBegin(GL_LINES);
				glVertex3d(points[0][3],points[1][3],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][3],points[1][3],-0.4*daecrase);
			glEnd();

			glBegin(GL_LINES);
				glVertex3d(points[0][2],points[1][2],0.2*daecrase+hauteur_cube);
				glVertex3d(points[0][2],points[1][2],-0.4*daecrase);
			glEnd();*/

			glFlush();

			glPopMatrix();

}

void GLWidget2::resizeGL(int width, int height)
{
    int side = qMin(width, height);
    glViewport((width - side) / 2, (height - side) / 2, side, side);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
#ifdef QT_OPENGL_ES_1
    glOrthof(-1., +1., -1., +1., -1., 1.);
#else
    //glOrtho(-0.5, +0.5, -0.5, +0.5, 4.0, 15.0);
glOrtho(-1., +1., -1., +1., -1., 1.);
#endif
    glMatrixMode(GL_MODELVIEW);
}

void GLWidget2::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void GLWidget2::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(xRot + 8 * dy);
        setZRotation(zRot + 8 * dx);
    }
    lastPos = event->pos();
}
//! [10]
