#ifndef VIEWER_H_
#define VIEWER_H_

#include <cassert>
#include <vector>

#include <GL/glut.h>
#include <QKeyEvent>
#include <QGLViewer/qglviewer.h>

#include "Cellule.h"

template <int n, int k, typename T>
class Viewer;

/***************************************************************
 *
 **************************************************************/
/*
template <int Start, int End>
class ViewLoop
{
     public:
          template <int n, int k, typename T>
          static void loop(Viewer<n, k, T> *v, ComplexeCubique<n, k, T> *cc)
          {
               ContainerPtr *ptr = cc->cells();

               for (unsigned int i = 0; i < End - Start; i++)
                    ptr = ptr->GetNext();

               std::vector<Cellule<Start> *> &cells = static_cast<Container<Start> *>(ptr)->GetCells();
               typename std::vector<Cellule<Start> *>::iterator it;
               for (it = cells.begin(); it != cells.end(); ++it)
                    v->template drawCellule<Start>(*it);

               ViewLoop<Start + 1, End>::template loop<n, k, T>(v, cc);
          }
};

template <int End>
class ViewLoop<End, End>
{
     public:
          template <int n, int k, typename T>
          static void loop(Viewer<n, k, T> *v, ComplexeCubique<n, k, T> *cc)
          {
               ContainerPtr *ptr = cc->cells();

               std::vector<Cellule<End> *> &cells = static_cast<Container<End> *>(ptr)->GetCells();
               typename std::vector<Cellule<End> *>::iterator it;
               for (it = cells.begin(); it != cells.end(); ++it)
                    v->template drawCellule<End>(*it);
          }
};*/

enum { X, Y, Z };

/***************************************************************
 *
 **************************************************************/
template <int n, int k, typename T>
class Viewer : public QGLViewer
{
     public:
          Viewer(ComplexeCubique<n, k, T> *cc);
          ~Viewer();

          template <int dim>
          void drawCell(CelluleVirtuelle* cellule);

     protected:
          // Draw a sphere centered in (x,y,z) and with diameter lg
          void draw_sphere(double x, double y, double z, double lg);

          // Draw a cylinder centered in (x,y,z), with length lg, and with given diameter
          void draw_cylinder(double x, double y, double z, double lg, double diameter, int dir);

          // Draw a square centered in (x,y,z) and with length lg
          void draw_square(double x, double y, double z, double lg, int dir1, int dir2);

          // Draw a cube centered in (x,y,z) and with length lg
          void draw_cube(double x, double y, double z, double lg);

          void drawCell(CelluleVirtuelle* cellule);
          void draw0Cell(Cellule<0>* cellule);
          void draw1Cell(Cellule<1>* cellule);
          void draw2Cell(Cellule<2>* cellule);
          void draw3Cell(Cellule<3>* cellule);
          virtual void draw();

          virtual void init();

          // A utiliser/modifier si vous voulez ajouter une action associé à un racourci clavier.
          void keyPressEvent(QKeyEvent *e);
          virtual QString helpString() const;

     private:
          GLUquadric *quadrics;
          qglviewer::Vec bbmin, bbmax;
          bool first;
          ComplexeCubique<n, k, T> *complexe;
};

template <int n, int k, typename T>
Viewer<n, k, T>::Viewer(ComplexeCubique<n, k, T> *cc)
{
     quadrics = gluNewQuadric();
     complexe = cc;
}

template <int n, int k, typename T>
Viewer<n, k, T>::~Viewer()
{
     gluDeleteQuadric(quadrics);
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw_sphere(double x, double y, double z, double lg)
{
     glColor3f(.5f, 1.f, .5f); // Color of the spheres

     glPushMatrix();

     glTranslatef(x, y, z);
     glutSolidSphere(lg / 2, 16, 16);

     glPopMatrix();

     if (first)
     {
          bbmin.x = x - lg / 2;
          bbmin.y = y - lg / 2;
          bbmin.z = z - lg / 2;

          bbmax.x = x + lg / 2;
          bbmax.y = y + lg / 2;
          bbmax.z = z + lg / 2;

          first = false;
     }
     else
     {
          if (x - lg / 2 < bbmin.x)
               bbmin.x = x - lg / 2;
          if (y - lg / 2 < bbmin.y)
               bbmin.y = y - lg / 2;
          if (z - lg / 2 < bbmin.z)
               bbmin.z = z - lg / 2;

          if (x + lg / 2 > bbmax.x)
               bbmax.x = x + lg / 2;
          if (y + lg / 2 > bbmax.y)
               bbmax.y = y + lg / 2;
          if (z + lg / 2 > bbmax.z)
               bbmax.z = z + lg / 2;
     }
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw_cylinder(double x, double y, double z, double lg, double diameter, int dir)
{
     glColor3f(1.f, 1.f, .5f);

     double p = lg / 2;
     glPushMatrix();
     glTranslatef(x - (dir == X ? p : 0), y - (dir == Y ? p : 0), z - (dir == Z ? p : 0));

     if (dir == X)
          glRotatef(90, 0, 1, 0);
     else if (dir == Y)
          glRotatef(-90, 1, 0, 0);

     gluCylinder(quadrics, diameter, diameter, lg, 16, 1);
     glPopMatrix();
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw_square(double x, double y, double z, double lg, int dir1, int dir2)
{
     glColor3f(0.5f, 0.5f, 1.0f);

     assert(dir1 < dir2);

     double p = lg / 2;
     glPushMatrix();
     glTranslatef(x, y, z);

     if (dir1 == X && dir2 == Z)
          glRotatef(90, 1, 0, 0);
     else if (dir1 == Y && dir2 == Z)
          glRotatef(90, 0, 1, 0);

     glBegin(GL_QUADS);
     glVertex3f(-p, -p, 0);
     glVertex3f(+p, -p, 0);
     glVertex3f(+p, +p, 0);
     glVertex3f(-p, +p, 0);
     glEnd();

     glPopMatrix();
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw_cube(double x, double y, double z, double lg)
{
     glColor3f(1.0f, .5f, .5f);

     double p = lg / 2;
     glPushMatrix();
     glTranslatef(x, y, z);

     glBegin(GL_QUADS);
     glVertex3f(-p, -p, -p);
     glVertex3f(+p, -p, -p);
     glVertex3f(+p, +p, -p);
     glVertex3f(-p, +p, -p);

     glVertex3f(-p, -p, -p);
     glVertex3f(+p, -p, -p);
     glVertex3f(+p, -p, +p);
     glVertex3f(-p, -p, +p);

     glVertex3f(-p, -p, -p);
     glVertex3f(-p, -p, +p);
     glVertex3f(-p, +p, +p);
     glVertex3f(-p, +p, -p);

     glVertex3f(+p, +p, +p);
     glVertex3f(-p, +p, +p);
     glVertex3f(-p, -p, +p);
     glVertex3f(+p, -p, +p);

     glVertex3f(+p, +p, +p);
     glVertex3f(-p, +p, +p);
     glVertex3f(-p, +p, -p);
     glVertex3f(+p, +p, -p);

     glVertex3f(+p, +p, +p);
     glVertex3f(+p, +p, -p);
     glVertex3f(+p, -p, -p);
     glVertex3f(+p, -p, +p);
     glEnd();

     glPopMatrix();
}

template <int n, int k, typename T>
void Viewer<n, k, T>::drawCell(CelluleVirtuelle* cellule)
{
     switch(cellule->getDimension())
     {
          case 0:
               draw0Cell(static_cast<Cellule<0>*>(cellule));
               break;
          case 1:
               draw1Cell(static_cast<Cellule<1>*>(cellule));
               break;
          case 2:
               draw2Cell(static_cast<Cellule<2>*>(cellule));
               break;
          case 3:
               draw3Cell(static_cast<Cellule<3>*>(cellule));
               break;
     }
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw0Cell(Cellule<0>* cellule)
{
     // On peut par exemple choisir de dessiner chaque 0-cellule par une sphère.
     draw_sphere(cellule->getSommet()[0], cellule->getSommet()[1], cellule->getSommet()[2], .2);
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw1Cell(Cellule<1>* cellule)
{
     // On peut par exemple choisir de dessiner chaque 1-cellule par un cylindre.
     std::vector<CelluleVirtuelle*>* edges = cellule->getBords();

     assert(edges->size() == 2);

     Cellule<0>* c1 = static_cast<Cellule<0>*>((*edges)[0]);
     Cellule<0>* c2 = static_cast<Cellule<0>*>((*edges)[1]);
     Point<k,T> *p1 = &c1->getSommet();
     Point<k,T> *p2 = &c2->getSommet();
     double lg = sqrt(
                    pow(((*p2)[0] - (*p1)[0]), 2)
                    + pow(((*p2)[1] - (*p1)[1]), 2)
                    + pow(((*p2)[2] - (*p1)[2]), 2)
                 );
     if ((*p2)[0] - (*p1)[0] == 0)
        draw_cylinder((*p1)[0], (*p1)[1], (*p1)[2], lg/2, .08, Y);
     else if ((*p2)[1] - (*p1)[1] == 0)
        draw_cylinder((*p1)[0], (*p1)[1], (*p1)[2], lg/2, .08, X);
     else
        draw_cylinder((*p1)[0], (*p1)[1], (*p1)[2], lg/2, .08, Z);
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw2Cell(Cellule<2>* cellule)
{
     // On peut par exemple choisir de dessiner chaque 2-cellule par un carré.
     std::vector<CelluleVirtuelle*>* edges = cellule->getBords();

     assert(edges->size() == 4);

     Cellule<1> *edge = static_cast<Cellule<1>*>(edges->at(0));
     std::vector<CelluleVirtuelle*>* edges2 = edge->getBords();

     assert(edges2->size() == 2);

     Cellule<1> *edge2 = static_cast<Cellule<1>*>(edges->at(2));
     std::vector<CelluleVirtuelle*>* edges3 = edge2->getBords();

     assert(edges3->size() == 2);


     Cellule<0>* c1 = static_cast<Cellule<0>*>(edges2->at(0));
     Cellule<0>* c2 = static_cast<Cellule<0>*>(edges2->at(1));
     Cellule<0>* c3 = static_cast<Cellule<0>*>(edges3->at(0));
     Point<k,T> *p1 = &c1->getSommet();
     Point<k,T> *p2 = &c2->getSommet();
     Point<k,T> *p3 = &c3->getSommet();

     double lg = sqrt(pow(((*p2)[0] - (*p1)[0]), 2) + pow(((*p2)[1] - (*p1)[1]), 2) + pow(((*p2)[2] - (*p1)[2]), 2));

     if ((*p1)[1] == (*p2)[1] && (*p1)[1] == (*p3)[1]) // les y sont similaires donc on rotate selon x
          draw_square((*p1)[0], (*p1)[1], (*p1)[2], lg, 0, 2);
     else if ((*p1)[0] == (*p2)[0] && (*p1)[0] == (*p3)[0]) // les x sont similaires donc on rotate selon y
          draw_square((*p1)[0], (*p1)[1], (*p1)[2], lg, 1, 2);
     else
          draw_square((*p1)[0], (*p1)[1], (*p1)[2], lg, 0, 1);
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw3Cell(Cellule<3>* cellule)
{
     // On peut par exemple choisir de dessiner chaque 3-cellule par un cube.
     std::vector<CelluleVirtuelle*>* edges = cellule->getBords();

     assert(edges->size() == 6);

     Cellule<2> *c2 = static_cast<Cellule<2>*>(edges->at(0));
     std::vector<CelluleVirtuelle*>* edges2 = c2->getBords();

     assert(edges2->size() == 4);

     Cellule<1> *c3 = static_cast<Cellule<1>*>(edges2->at(0));
     std::vector<CelluleVirtuelle*>* edges3 = c3->getBords();

     assert(edges3->size() == 2);

     Cellule<0>* c4 = static_cast<Cellule<0>*>(edges3->at(0));
     Cellule<0>* c5 = static_cast<Cellule<0>*>(edges3->at(1));
     Point<k,T> *p1 = &c4->getSommet();
     Point<k,T> *p2 = &c5->getSommet();
     double lg = sqrt(pow(((*p2)[0] - (*p1)[0]), 2) + pow(((*p2)[1] - (*p1)[1]), 2) + pow(((*p2)[2] - (*p1)[2]), 2));
     draw_cube((*p1)[0], (*p1)[1], (*p1)[2], lg);
}

template <int n, int k, typename T>
void Viewer<n, k, T>::draw()
{
     first = true; // A garder (pour mettre à jour la boundix box d'affichage.

     for(int i=0; i<=n; i++)
     {
         std::vector<CelluleVirtuelle*>::iterator it;
         for(it = complexe->getCellules(i)->begin(); it != complexe->getCellules(i)->end(); ++it)
         {
            drawCell(*it);
         }
     }

     // A garder (pour mettre à jour la boundix box d'affichage.
     setSceneBoundingBox(bbmin, bbmax);
}

template <int n, int k, typename T>
void Viewer<n, k, T>::init()
{
     restoreStateFromFile();

     // Define 'Control+Q' as the new exit shortcut (default was 'Escape')
     setShortcut(EXIT_VIEWER, Qt::CTRL+Qt::Key_Q);

     setKeyDescription(Qt::Key_S, "Simplify the cubical complex");
}

template <int n, int k, typename T>
void Viewer<n, k, T>::keyPressEvent(QKeyEvent *e)
{
     const Qt::KeyboardModifiers modifiers = e->modifiers();
     bool handled = false;
     if ((e->key() == Qt::Key_S) && (modifiers == Qt::NoButton))
     {
          // Traitement de l'action associé à la touche s
          handled = true;
          complexe->simplification();
          std::cout << "Simplification" << std::endl;
          updateGL();
     }
     if (!handled)
          QGLViewer::keyPressEvent(e);
}

template <int n, int k, typename T>
QString Viewer<n, k, T>::helpString() const
{
     QString text("<h2>S i m p l e V i e w e r</h2>");
     text += "Use the mouse to move the camera around the object. ";
     text += "You can respectively revolve around, zoom and translate with the three mouse buttons. ";
     text += "Left and middle buttons pressed together rotate around the camera view direction axis<br><br>";
     text += "Pressing <b>Alt</b> and one of the function keys (<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
     text += "Simply press the function key again to restore it. Several keyFrames define a ";
     text += "camera path. Paths are saved when you quit the application and restored at next start.<br><br>";
     text += "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
     text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save a snapshot. ";
     text += "See the <b>Keyboard</b> tab in this window for a complete shortcut list.<br><br>";
     text += "Double clicks automates single click actions: A left button double click aligns the closer axis with the camera (if close enough). ";
     text += "A middle button double click fits the zoom of the camera and the right button re-centers the scene.<br><br>";
     text += "A left button double click while holding right button pressed defines the camera <i>Revolve Around Point</i>. ";
     text += "See the <b>Mouse</b> tab and the documentation web pages for details.<br><br>";
     text += "Press <b>Escape</b> to exit the viewer.";
     return text;
}

#endif
