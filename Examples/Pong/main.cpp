#include <iostream>  
#include <math.h>

#include "core.h"

#include <vector>
#include "game_object.h"
#include "game_rect.h"
#include "game_circle.h"

#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include "playerContactListener.h"

#include "core_pong.h"
#include <Renderer/text.h>

using namespace std;



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

float playerWidth = 150;

float BALL_SPEED = 4.0;
float PLAYER_SPEED = 2.0;
float GRAVITY = -1.0;

int score;
int lives;
int total_bricks;

int BRICK_ROWS = 5;
int BRICK_COLUMNS= 3;


#define RAD(deg) ((3.14 * deg)/180.f)
#define min(X, Y)

unsigned long startTime;
unsigned long prevTime;
int fps_count = 0;

float randFloat() {
    return (float)rand() / (float)RAND_MAX;
}

static  long getTime() {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
    return ms;
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
    //cout << "Key pressed: " << key << endl;
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
    player->body->SetLinearVelocity(b2Vec2(PLAYER_SPEED * dir_right - dir_left, 0.0));
    player->body->SetTransform(b2Vec2(player->body->GetPosition().x, 0.0), 0.0);

    world->Step(timeStep, velocityIterations, positionIterations);
    long current = getTime();
    long ellapsedTime = current - startTime; 
    fps_count++;
    if(ellapsedTime > 1000 ) {
        startTime = current;
        printf("fps_count : %d \n", fps_count);
        fps_count = 0;
    }
   // printf("ELLAPSED TIME = %u \n", current - startTime);

    for(int i = 0; i < bodies.size() ; i++ ) {
        GameObject *gameObject = bodies[i];
        if(gameObject->toDestroy) {
            world->DestroyBody(gameObject->body);
            bodies.erase(bodies.begin() + i);
            renderer->removeRenderable(gameObject->getRenderable());
            score++;
            total_bricks--;
            i--;
            if(total_bricks == 0 ) {
                printf("YOU WIN: SCORE = %d \n",score);
            }
        } else {
            bodies[i]->update();
        }
    }
}

static void startGame() {
    lives = 3;
    score = 0;

    float boxWidth = screenWidth / (BRICK_COLUMNS) - 5; 
    float boxHeight = screenHeight/ 3.0 / (BRICK_ROWS) - 5;

    total_bricks = BRICK_COLUMNS * BRICK_ROWS;

    for(float i = 0.5; i < BRICK_COLUMNS; i++ ) {
        for (float j = 0.5; j < BRICK_ROWS; j++ ) {
            GameObject *brick = new GameRect(boxWidth, boxHeight, i * screenWidth / BRICK_COLUMNS, screenHeight - j * screenHeight / 3.0 / BRICK_ROWS);
            brick->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
            brick->body->SetType(b2_staticBody);
            brick->fixture->SetRestitution(1.0);
            brick->setTag("BRICK");
            bodies.push_back(brick);
            
        }
    }
}

int main() {
    startTime = prevTime = getTime();
    renderer = new Renderer(400, 800, "Hello world");

    renderer->setUpdateCallback(&update);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);
    	// Define the gravity vector.
    srand( (unsigned)time(NULL) );
	b2Vec2 gravity(0.0f, GRAVITY);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	// Define the ground body.

    {
        GameObject *leftWall = new GameRect(50, screenHeight,-25, screenHeight/2);
        leftWall->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
        leftWall->body->SetType(b2_staticBody);
        leftWall->fixture->SetRestitution(1.0);
        bodies.push_back(leftWall);
    }
    {
        GameObject *leftWall = new GameRect(50, screenHeight, screenWidth+25, screenHeight/2);
        leftWall->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
        leftWall->body->SetType(b2_staticBody);
        leftWall->fixture->SetRestitution(1.0);
        bodies.push_back(leftWall);
    }
    {
        GameObject *leftWall = new GameRect(screenWidth, 50, screenWidth/2.0, screenHeight+25);
        leftWall->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
        leftWall->body->SetType(b2_staticBody);
        leftWall->fixture->SetRestitution(1.0);
        bodies.push_back(leftWall);
    }
    {
        ball = new GameCircle( 10, screenWidth / 2, 500);
        ball->getRenderable()->setColor(0.0, 1.0, 0.0, 1.0);
        ball->body->SetLinearVelocity(b2Vec2(0.0, -1.0 * BALL_SPEED));
        std::cout << "fixture addr outside : " << ball->fixture << std::endl;
        ball->fixture->SetRestitution(1.0);
        ball->body->ResetMassData();
        ball->setTag("BALL");
        bodies.push_back(ball);
    }
    {
        player = new GameRect( playerWidth, 20, screenWidth / 2, 0);
        player->getRenderable()->setColor(1.0, 0.0, 0.0, 1.0);
        player->fixture->SetRestitution(1.0);
        player->body->ResetMassData();
        player->setTag("PLAYER");
        bodies.push_back(player);
    }


    startGame();

    PlayerContactListener listener; 

    world->SetContactListener(&listener);

    Font font = LoadFont("assets/OpenSans-Regular.ttf");

    Text *text = new Text("HELLO WORLD", font, 100.0, 100.0, 0.5);
    text->setColor(0.0, 1.0, 0.0, 1.0);
    renderer->addRenderable(text);
    //Text text = new Text("HELLO WORLD", font);
    renderer->start();

    return 0;
}

