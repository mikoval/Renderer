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
#include "playerContactListener.h"

using namespace std;

long int start_ms;


vector<GameObject *> bodies;

GameObject *player;
GameObject *ball;

Renderer *renderer;
b2World *world;

int velocityIterations = 6;
int positionIterations = 2;
float timeStep = 1.0f / 60.0f;

double mouseX = 0;
double mouseY = 0;

extern int screenWidth;
extern int screenHeight;

int dir_right = 0;
int dir_left = 0;


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
}

void key_press(int key, int scancode, int action, int mods) {
    cout << "Key pressed: " << key << endl;
    if(key == 65) {
        if(action == GLFW_PRESS) 
            dir_left = 1.0;
        else if(action == GLFW_RELEASE)
            dir_left = 0.0;
    }
    if(key == 68) {
        if(action == GLFW_PRESS) 
            dir_right = 1.0;
        else if(action == GLFW_RELEASE)
            dir_right = 0.0;
    }
}

void update(unsigned long time) {
    player->body->SetLinearVelocity(b2Vec2(dir_right - dir_left, 0.0));
    world->Step(timeStep, velocityIterations, positionIterations);

    for(int i = 0; i < bodies.size() ; i++ ) {
        bodies[i]->update();
    }
}

int main() {
    renderer = new Renderer(400, 800, "Hello world");

    renderer->setUpdateCallback(&update);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);
    	// Define the gravity vector.
    srand( (unsigned)time(NULL) );
	b2Vec2 gravity(0.0f, 0.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	// Define the ground body.
    {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(-10.0f, 0.0f);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(10.0f, 50.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }
    {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(screenWidth * screenToWorld + 10.0f, 0.0f);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(10.0f, 50.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }
    {
        b2BodyDef groundBodyDef;
        groundBodyDef.position.Set(screenWidth * screenToWorld /2.0, screenHeight * screenToWorld +10);
        b2Body* groundBody = world->CreateBody(&groundBodyDef);
        b2PolygonShape groundBox;
        groundBox.SetAsBox(50.0f, 10.0f);
        groundBody->CreateFixture(&groundBox, 0.0f);
    }

    
    ball = new GameCircle( 10, screenWidth / 2, 500);
    ball->getRenderable()->setColor(0.0, 1.0, 0.0, 1.0);
    ball->body->SetLinearVelocity(b2Vec2(0.0, -3.0));
    std::cout << "fixture addr outside : " << ball->fixture << std::endl;
    ball->fixture->SetRestitution(1.0);
    ball->fixture->SetDensity(0.1);
    ball->body->ResetMassData();

    bodies.push_back(ball);

    player = new GameRect( 100, 20, screenWidth / 2, 0);
    player->getRenderable()->setColor(1.0, 0.0, 0.0, 1.0);
    player->fixture->SetDensity(10000.0);
    player->body->ResetMassData();
    //player->body->SetType(b2_kinematicBody);

    bodies.push_back(player);

    std::cout << "fixture addr outside : " << ball->fixture << std::endl;

    PlayerContactListener listener; 

    world->SetContactListener(&listener);

    renderer->start();

    return 0;
}

