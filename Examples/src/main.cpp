#include <iostream>  
#include <math.h>

#include "core.h"

#include <vector>
#include "game_object.h"
#include "game_rect.h"
#include "game_circle.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

using namespace std;

long int start_ms;


vector<GameObject *> bodies;

Renderer *renderer;
b2World *world;

int velocityIterations = 6;
int positionIterations = 2;
float timeStep = 1.0f / 60.0f;

double mouseX = 0;
double mouseY = 0;


#define RAD(deg) ((3.14 * deg)/180.f)
#define min(X, Y)


float randFloat() {
    return (float)rand() / (float)RAND_MAX;
}

void addBody(double mouseX, double mouseY) {
    GameObject *obj;
    if(rand() % 2 == 0) {
        obj = new GameRect( 1 + rand() % 200, 1 + rand() % 200, (int)mouseX, (int)mouseY);
    } else {
        obj = new GameCircle(rand() % 100, (int)mouseX, (int)mouseY);
    }
    obj ->getRenderable()-> setColor(randFloat(), randFloat(), randFloat(), 1.0f);
    bodies.push_back(obj);
}

void mouse_button_press(int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        addBody(mouseX, mouseY);
    }
}

void mouse_move(double x, double y)
{
    mouseX = x;
    mouseY = screenHeight-y;
    //printf("%f, %f \n", x, y);
}

void key_press(int key, int scancode, int action, int mods) {
    cout << "Key pressed: " << key << endl;
    if(key == 65) {
        renderer->setBackgroundColor(1, 0, 0, 0);
    }
    if(key == 68) {
        renderer->setBackgroundColor(0, 1, 0, 0);
    }
    if(key == 83) {
        renderer->setBackgroundColor(0, 0, 1, 0);
    }
    if(key == 70) {
        //addBody();
    }
}

void update(unsigned long time) {

    world->Step(timeStep, velocityIterations, positionIterations);

    for(int i = 0; i < bodies.size() ; i++ ) {
        bodies[i]->update();
    }
}

int main() {
    	// Define the gravity vector.
    srand( (unsigned)time(NULL) );
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);

	// Define the ground box shape.
	b2PolygonShape groundBox;

	// The extents are the half-widths of the box.
	groundBox.SetAsBox(50.0f, 10.0f);

	// Add the ground fixture to the ground body.
	groundBody->CreateFixture(&groundBox, 0.0f);



    renderer = new Renderer(screenWidth, screenHeight, "Hello world");

    renderer->setUpdateCallback(&update);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);

    renderer->start();

    return 0;
}

