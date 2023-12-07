#include <GL/gl.h>
#include <GL/glut.h>

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "Vec2.h"

struct Boid {
  Vec2  position;
  Vec2  velocity;
  float speed;

public:
  Boid() {
    position.randomize();
    velocity.randomize();
    velocity.normalize();

    // 0.010 - 0.015
    float r = float(rand()) / float(RAND_MAX);
    speed = 0.010f + r * 0.015f;
  }

  void render() const {
    glPushMatrix();
    glTranslatef(position.x, position.y, 0);

    float radians = std::atan2(velocity.y, velocity.x);
    float degrees = radians * 57.2958 - 90;
    glRotatef(degrees, 0, 0, 1);
    glScalef(0.3f, 0.3f, 1.0f);

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
  for(Boid& boid: boids) {
    for(Boid& other: boids) {
      if(&boid == &other) {
        continue;
      }

      Vec2  disp = boid.position - other.position;
      float dist = disp.length();
      disp /= dist;

      float attraction = 0.4f / (dist*dist + 0.1f);
      boid.velocity -= disp * attraction * 0.001f;

      float repulsion = 5.0f / (9*dist*dist + 0.1f);
      boid.velocity += disp * repulsion * 0.001f;

      float cohesion = 1.0f / (dist*dist + 0.1f);
      boid.velocity += other.velocity * cohesion * 0.001f;
    }
  }

  for(Boid& boid: boids) {
    boid.velocity.x -= std::pow(boid.position.x, 5);
    boid.velocity.y -= std::pow(boid.position.y, 5);

    boid.velocity.normalize();
    boid.position += boid.velocity * boid.speed;
  }
}

void render() {
  glClearColor(0.2, 0.2, 0.2, 1.0);
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

  for(int i = 0; i < 100; ++i) {
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
