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

#define WALL_WIDTH 10
#define WALL_HEIGHT 30

vector<GameObject *> bodies;

GameObject *player;
GameObject *ball;
Text *scoreText;
Text *livesText;

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

float BALL_SPEED = 5.0;
float PLAYER_SPEED = 3.0;
float GRAVITY = -0.5;

int level;
int score;
int lives;
int total_bricks;

int BRICK_ROWS = 2;
int BRICK_COLUMNS= 2;


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

static void restartBall() {
    float speed = BALL_SPEED + level;
    ball->body->SetLinearVelocity(b2Vec2(0.0, 1.0 * speed));
    ball->body->SetTransform(player->body->GetPosition()+b2Vec2(0.0, 0.2),0.0f);
}

static void startGame() {

    int rows = BRICK_ROWS + level;
    int columns = BRICK_COLUMNS + level;

    restartBall();
    float gameWidth = screenWidth - (WALL_WIDTH * 2);
    float gameHeight = screenHeight -  WALL_HEIGHT;

    float boxWidth = gameWidth / (columns) - 5; 
    float boxHeight = gameHeight/ 3.0 / (rows) - 5;

    total_bricks = columns * rows;

    for(int i = 0; i < bodies.size() ; i++ ) {
        GameObject *gameObject = bodies[i];
        if(!gameObject->getTag().compare("BRICK")) {
            world->DestroyBody(gameObject->body);
            bodies.erase(bodies.begin() + i);
            renderer->removeRenderable(gameObject->getRenderable());
            i--;

        }
    }

    for(float i = 0.5; i < columns; i++ ) {
        for (float j = 0.5; j < rows; j++ ) {
            GameObject *brick = new GameRect(boxWidth, boxHeight, WALL_WIDTH +  i * gameWidth / columns, gameHeight - j * gameHeight / 3.0 / rows);
            brick->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
            brick->body->SetType(b2_staticBody);
            brick->fixture->SetRestitution(1.0);
            brick->setTag("BRICK");
            bodies.push_back(brick);
            
        }
    }

}


void update(unsigned long time) {
    player->body->SetLinearVelocity(b2Vec2(PLAYER_SPEED * (dir_right - dir_left), 0.0));
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

    if(ball->body->GetPosition().y < 0){
        lives--;
        livesText->setText("LIVES: " + std::to_string(lives));
        if(lives == 0){
            printf("YOU LOSE: SCORE = %d \n",score);
            score = 0;
            lives = 3;
            level = 0;
            startGame();
        }


        restartBall();
        livesText->setText("LIVES: " + std::to_string(lives));
        scoreText->setText("SCORE: " + std::to_string(score));

    }

    for(int i = 0; i < bodies.size() ; i++ ) {
        GameObject *gameObject = bodies[i];
        if(gameObject->toDestroy) {
            world->DestroyBody(gameObject->body);
            bodies.erase(bodies.begin() + i);
            renderer->removeRenderable(gameObject->getRenderable());
            score++;
            total_bricks--;
            i--;
            scoreText->setText("SCORE: " + std::to_string(score));
            if(total_bricks == 0 ) {
                printf("YOU WIN: SCORE = %d \n",score);
                level++;
                startGame();
            }

        } else {
            bodies[i]->update();
        }
    }
}

int main() {
    startTime = prevTime = getTime();
    renderer = new Renderer(400, 800, "Hello world");
    lives = 3;
    score = 0;
    level = 1;

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
        GameObject *leftWall = new GameRect( WALL_WIDTH * 2, screenHeight,0.0, screenHeight/2);
        leftWall->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
        leftWall->body->SetType(b2_staticBody);
        leftWall->fixture->SetRestitution(1.0);
        leftWall->getRenderable()->setColor(0.5, 0.5, 0.5, 1.0);
        bodies.push_back(leftWall);
    }
    {
        GameObject *leftWall = new GameRect( WALL_WIDTH * 2, screenHeight, screenWidth, screenHeight/2);
        leftWall->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
        leftWall->body->SetType(b2_staticBody);
        leftWall->fixture->SetRestitution(1.0);
        leftWall->getRenderable()->setColor(0.5, 0.5, 0.5, 1.0);

        bodies.push_back(leftWall);
    }
    {
        GameObject *leftWall = new GameRect(screenWidth,  WALL_WIDTH * 6, screenWidth/2.0, screenHeight);
        leftWall->getRenderable()->setColor(1.0, 1.0, 1.0, 1.0);
        leftWall->body->SetType(b2_staticBody);
        leftWall->fixture->SetRestitution(1.0);
        leftWall->getRenderable()->setColor(0.5, 0.5, 0.5, 1.0);

        bodies.push_back(leftWall);
    }
    {
        ball = new GameCircle( 10, screenWidth / 2, 500);
        ball->getRenderable()->setColor(0.0, 1.0, 0.0, 1.0);
        std::cout << "fixture addr outside : " << ball->fixture << std::endl;
        ball->fixture->SetRestitution(1.0);
        ball->body->ResetMassData();
        ball->setTag("BALL");
        ball->setFriction(0.0);

        bodies.push_back(ball);
    }
    {
        player = new GameRect( playerWidth, 20, screenWidth / 2, 0);
        player->getRenderable()->setColor(1.0, 0.0, 0.0, 1.0);
        player->fixture->SetRestitution(1.0);
        player->body->ResetMassData();
        player->setTag("PLAYER");
        player->setFriction(0.0);

        bodies.push_back(player);
    }


    startGame();

    PlayerContactListener listener; 

    world->SetContactListener(&listener);

    Font font = LoadFont("assets/OpenSans-Regular.ttf");

    scoreText = new Text("SCORE: " + std::to_string(score), font, WALL_WIDTH + 10, screenHeight - WALL_HEIGHT + 3, WALL_HEIGHT-2);
    scoreText->setColor(0.0, 0.0, 0.0, 1.0);
    renderer->addRenderable(scoreText);


    livesText = new Text("LIVES: " + std::to_string(lives), font, WALL_WIDTH + 200, screenHeight - WALL_HEIGHT + 3, WALL_HEIGHT-2);
    livesText->setColor(0.0, 0.0, 0.0, 1.0);
    renderer->addRenderable(livesText);
    renderer->start();

    return 0;
}

