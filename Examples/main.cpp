#include <Renderer/renderer.h>
#include <Renderer/2d_shapes.h>
#include <iostream>  
#include <math.h>
#include <box2d/box2d.h>


#include <sys/time.h>

using namespace std;

Renderer *renderer;

struct timeval start;
long int start_ms;

Rectangle *rect;

b2World *world;
b2Body* body;

	float timeStep = 1.0f / 60.0f;
	int velocityIterations = 6;
	int positionIterations = 2;

#define RAD(deg) ((3.14 * deg)/180.f)
#define min(X, Y)


void test(int key, int scancode, int action, int mods) {
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
}

void update(unsigned long time) {
    struct timeval current;
    gettimeofday(&current, NULL);
    long int current_ms = current.tv_sec * 1000 + current.tv_usec / 1000;
    long int total_time = current_ms - start_ms;

    world->Step(timeStep, velocityIterations, positionIterations);

    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    rect->position.x = position.x * 100;
    rect->position.y = position.y * 100;
    rect->rotation = angle;
}

int main() {
    	// Define the gravity vector.
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

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(10.0f, 10.0f);
    bodyDef.angle = 1.9f;
	body = world->CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 1.0f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	// Add the shape to the body.
	body->CreateFixture(&fixtureDef);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.

	// This is our little game loop.
/*
	for (int32 i = 0; i < 60; ++i)
	{
		// Instruct the world to perform a single step of simulation.
		// It is generally best to keep the time step and iterations fixed.
		world.Step(timeStep, velocityIterations, positionIterations);

		// Now print the position and angle of the body.
		b2Vec2 position = body->GetPosition();
		float angle = body->GetAngle();

		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
	}
    */


    renderer = new Renderer(1200, 800, "Hello world");

    gettimeofday(&start, NULL);
    start_ms = start.tv_sec * 1000 + start.tv_usec / 1000;

    renderer->setUpdateCallback(&update);

    renderer->setKeyboardCallback(&test);

    rect = new Rectangle(300, 200);
    rect->position.x = 200.0;
    rect->position.y = 200.0;
    renderer->addRenderable(rect);

    renderer->start();

    return 0;
}

