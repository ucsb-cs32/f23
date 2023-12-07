#include <GL/gl.h>
#include <GL/glut.h>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>

#include "Vec2.h"

struct Boid {
  Vec2 position;
  Vec2 velocity;

public:
  Boid() {
    position.randomize();

    velocity.randomize();
    velocity *= 0.05;
  }

  void render() const {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);

    float radians = std::atan2(velocity.y, velocity.x);
    float degrees = radians * 57.2958 - 90;
    glRotatef(degrees, 0, 0, 1);

    glBegin(GL_TRIANGLES);
    glVertex2f( 0.0,  0.2);
    glVertex2f( 0.1, -0.1);
    glVertex2f(-0.1, -0.1);
    glEnd();

    glPopMatrix();
  }
};

std::vector<Boid> boids;

void update() {
  // INTERACTIONS (work in progress)
  // for(Boid& boid: boids) {
  //   boid.velocity = Vec2(0, 0);

  //   for(Boid& other: boids) {
  //     Vec2 disp = boid.position - other.position;
  //     boid.velocity -= disp * 0.001f;
  //   }
  // }

  for(Boid& boid: boids) {
    boid.velocity.x -= 0.01 * std::pow(boid.position.x, 3);
    boid.velocity.y -= 0.01 * std::pow(boid.position.y, 3);
    boid.position += boid.velocity;
  }
}

void render() {
  glClearColor(0.1, 0.2, 0.1, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);

  for(const Boid& boid: boids) {
    boid.render();
  }

  glutSwapBuffers();
}

void timer(int) {
  update();
  glutPostRedisplay();
  glutTimerFunc(33, timer, 0);
}

int main(int argc, char** argv) {
  srand(time(0));

  for(int i = 0; i < 10; ++i) {
    boids.push_back(Boid());
  }

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Boids");

  glutDisplayFunc(render);
  glutTimerFunc(33, timer, 0);
  glutMainLoop();
  return 0;
}
