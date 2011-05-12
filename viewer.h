#include "GL/glut.h"
#include <QKeyEvent>
#include <QGLViewer/qglviewer.h>
#include <cassert>

enum { X, Y, Z };

template<unsigned int n, unsigned int k, typename T>
class Viewer : public QGLViewer
{
  //typedef CComplexe<n,k,T> Complexe; // A modifier
  typedef int Complexe; // temporaire pour que le prog compile sans la classe complexe
  
public:
  Viewer(Complexe& moncomplexe) : m_complexe_cubique(moncomplexe)
  {
    quadrics = gluNewQuadric();
  }

  ~Viewer()
  {
    gluDeleteQuadric(quadrics);
  }
  
protected:
  // Draw a sphere centered in (x,y,z) and with diameter lg
  void draw_sphere(double x, double y, double z, double lg)
  {
    glColor3f(.5f,1.f,.5f); // Color of the spheres
    
    glPushMatrix();
    
    glTranslatef ( x, y, z );
    glutSolidSphere (lg/2, 16, 16);

    glPopMatrix();

    if ( first )
      {
	bbmin.x=x-lg/2; bbmin.y=y-lg/2; bbmin.z=z-lg/2;
	bbmax.x=x+lg/2; bbmax.y=y+lg/2; bbmax.z=z+lg/2;
	first = false;
      }
    else
      {
	if ( x-lg/2<bbmin.x) bbmin.x=x-lg/2;
	if ( y-lg/2<bbmin.y) bbmin.y=y-lg/2;
	if ( z-lg/2<bbmin.z) bbmin.z=z-lg/2;
	
	if ( x+lg/2>bbmax.x) bbmax.x=x+lg/2;
	if ( y+lg/2>bbmax.y) bbmax.y=y+lg/2;
	if ( z+lg/2>bbmax.z) bbmax.z=z+lg/2;
      }
  }
  
  // Draw a cylinder centered in (x,y,z), with length lg, and with given diameter 
  void draw_cylinder(double x, double y, double z, double lg, double diameter, int dir)
  {
    glColor3f(1.f,1.f,.5f); // Color of the cylinders

    double p=lg/2;
    glPushMatrix();
    glTranslatef (x-(dir==X?p:0), y-(dir==Y?p:0), z-(dir==Z?p:0));

    if ( dir==X ) glRotatef( 90, 0, 1, 0);
    else if ( dir==Y ) glRotatef( -90, 1, 0, 0);

    gluCylinder(quadrics, diameter, diameter, lg, 16, 1);
      
    glPopMatrix();

  }
  
  // Draw a square centered in (x,y,z) and with length lg
  void draw_square(double x, double y, double z, double lg, int dir1, int dir2)
  {
    glColor3f(0.5f,0.5f,1.0f); // Color of the squares

    assert( dir1<dir2 );
    double p=lg/2;
    glPushMatrix();
    glTranslatef (x, y, z);

    if ( dir1==X && dir2==Z ) glRotatef( 90, 1, 0, 0);
    else if ( dir1==Y && dir2==Z ) glRotatef( 90, 0, 1, 0);

    glBegin(GL_QUADS);

    glVertex3f(-p, -p, 0);
    glVertex3f(+p, -p, 0);
    glVertex3f(+p, +p, 0);
    glVertex3f(-p, +p, 0);
    glEnd();

    glPopMatrix();
  }


  // Draw a cube centered in (x,y,z) and with length lg
  void draw_cube(double x, double y, double z, double lg)
  {
    glColor3f(1.0f,.5f,.5f); // Color of the cubes

    double p=lg/2;
    glPushMatrix();
    glTranslatef (x, y, z);

    glBegin(GL_QUADS);
    glVertex3f(-p,-p,-p); glVertex3f(+p,-p,-p); glVertex3f(+p,+p,-p); glVertex3f(-p,+p,-p);
    glVertex3f(-p,-p,-p); glVertex3f(+p,-p,-p); glVertex3f(+p,-p,+p); glVertex3f(-p,-p,+p);
    glVertex3f(-p,-p,-p); glVertex3f(-p,-p,+p); glVertex3f(-p,+p,+p); glVertex3f(-p,+p,-p);

    glVertex3f(+p,+p,+p); glVertex3f(-p,+p,+p); glVertex3f(-p,-p,+p); glVertex3f(+p,-p,+p);
    glVertex3f(+p,+p,+p); glVertex3f(-p,+p,+p); glVertex3f(-p,+p,-p); glVertex3f(+p,+p,-p);
    glVertex3f(+p,+p,+p); glVertex3f(+p,+p,-p); glVertex3f(+p,-p,-p); glVertex3f(+p,-p,+p);
    glEnd();

    glPopMatrix();
  }

  void draw0Cell( /* prend une 0-cellule en paramètre */ )
  {
    // On peut par exemple choisir de dessiner chaque 0-cellule par une sphère.
    draw_sphere( 0, 0, 0, .2 ); // A modifier
    draw_sphere( 4, 0, 0, .2 ); // A modifier
  }

  void draw1Cell( /* prend une 1-cellule en paramètre */ )
  {
    // On peut par exemple choisir de dessiner chaque 1-cellule par un cylindre.
    draw_cylinder( 1, 0, 0, .6, .08, X ); // A modifier
  }

  void draw2Cell( /* prend une 2-cellule en paramètre */ )
  {
    // On peut par exemple choisir de dessiner chaque 2-cellule par un carré.
    draw_square(2, 0, 0, 0.5, Y, Z); // A modifier
  }
  
  void draw3Cell( /* prend une 3-cellule en paramètre */ )
  {
    // On peut par exemple choisir de dessiner chaque 3-cellule par un cube.
    draw_cube(3, 0, 0,  0.5); // A modifier
  }

  virtual void draw()
  {
    first = true; // A garder (pour mettre à jour la boundix box d'affichage.
    
    // A modifier obligatoirement pour faire votre affichage.
    // afficher toutes les cellules de toutes les dimensions
    // parcourir les cellules et pour chaque appeler la méthode drawCell.
    // Afficher chaque cellule avec une couleur différente et les points et line avec
    // des tailles "suffisamment" grosses.
    /* ... */
    draw0Cell();
    draw1Cell();
    draw2Cell();
    draw3Cell();
    // fin à modifier.
    
    // A garder (pour mettre à jour la boundix box d'affichage.
    setSceneBoundingBox(bbmin,bbmax);
  }

  virtual void init()
  {
    restoreStateFromFile();

    // Define 'Control+Q' as the new exit shortcut (default was 'Escape')
    setShortcut(EXIT_VIEWER, Qt::CTRL+Qt::Key_Q);

    setKeyDescription(Qt::Key_S, "Simplify the cubical complex");
  }

  // A utiliser/modifier si vous voulez ajouter une action associé à un racourci clavier.
  void keyPressEvent(QKeyEvent *e)
  {
    const Qt::KeyboardModifiers modifiers = e->modifiers();    
    bool handled = false;
    if ((e->key()==Qt::Key_S) && (modifiers==Qt::NoButton))
      {
	// Traitement de l'action associé à la touche s
	handled = true;
	// m_complexe_cubique.simplify(); // a modifier si on veut simplifier le complexe
	updateGL();
      }
    if ( !handled ) QGLViewer::keyPressEvent(e);
  }

  virtual QString helpString() const
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

private:
  Complexe& m_complexe_cubique; // A modifier éventuellement.
  GLUquadric* quadrics;
  qglviewer::Vec bbmin, bbmax;
  bool first;
};
