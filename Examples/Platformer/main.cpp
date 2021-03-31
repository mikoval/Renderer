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
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

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

extern int screenWidth;
extern int screenHeight;

GameObject *ground;
GameObject *player;
Camera *camera;

bool leftKey, rightKey;

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
    if(key == 65 ) {
        if(action == GLFW_PRESS)
            leftKey = true;
        if(action == GLFW_RELEASE)
            leftKey = false;
        printf("LEFT KEY : %d \n", leftKey);

    }
    if(key == 68  ) {
        if(action == GLFW_PRESS)
            rightKey = true;
        if(action == GLFW_RELEASE)
            rightKey = false;
        printf("RIGHT KEY : %d \n", rightKey);
    } 
    if(key == 83) {
//        renderer->setBackgroundColor(0, 0, 1, 0);
    }
    if(key == 70) {
        //addBody();
    }
    if(key == 32) {
        if(action == GLFW_PRESS)
            player->body->ApplyLinearImpulse(b2Vec2(0.0, 0.6), player->body->GetWorldCenter(), true);
    }
}

void update(double time) {
    float FORCE = 0.2;
    float total_force = 0.0;
    if(rightKey) {
        total_force -= FORCE;
    } 
    if(leftKey) {
        total_force += FORCE;
    }

    camera->position.x = player->getPosition().x;
    camera->position.y = player->getPosition().y + 100;


    player->body->ApplyTorque(total_force, true);
    player->body->ApplyLinearImpulse(b2Vec2(-0.1 * total_force, 0.0), player->body->GetWorldCenter(), true);


    world->Step(timeStep, velocityIterations, positionIterations);

    for(int i = 0; i < bodies.size() ; i++ ) {
        bodies[i]->update();
    }
}
#define BLOCK_SIZE 100

#define SCALE 0.1

static inline void createGround(int x, int y) {
    ground = new GameRect( BLOCK_SIZE, BLOCK_SIZE, x * BLOCK_SIZE, -1 * y*BLOCK_SIZE);
    ground->getRenderable()->setColor(0.0, 0.0, 0.0, 1.0);
    ground->body->SetType(b2_staticBody);
    ground->setFriction(0.5);
    ground->setRestitution(0.3);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3((float)x * SCALE, (float)y * SCALE, 0.0f));
    model = glm::scale(model, glm::vec3(SCALE, -1 * SCALE, 0.0));



    ground->getRenderable()->setUVTransform(model);
    ground->getRenderable()->setImage("assets/platformer/marble.jpg");
    bodies.push_back(ground);
}
static inline void createPlayer(int x, int y) {
    player = new GameCircle(20.0, x * BLOCK_SIZE, -1 * y*BLOCK_SIZE);
    player->getRenderable()->setColor(0.0, 0.0, 0.0, 1.0);
    player->setFriction(0.5);
    player->setRestitution(0.3);
    player->getRenderable()->setImage("assets/platformer/marble2.jpg");
    player->body->SetType(b2_dynamicBody);
    player->body->SetAngularDamping(1.0);
    player->body->SetLinearDamping(0.6);
    bodies.push_back(player);
}
static inline void createWorld() {
    string line;
    ifstream myfile ("assets/platformer/map0.txt");
    int number_of_lines = 0;
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            cout << line << '\n';
            for(int i = 0; i < line.size(); i++) {
                char c = line.c_str()[i];
                if(c == 'x'){
                    createGround(i, number_of_lines);
                } else if (c == 'p'){
                    createPlayer(i, number_of_lines);
                }
            }
            number_of_lines++;

        }
        myfile.close();
    }
    else cout << "Unable to open file"; 
    printf("TOTAL LINES: %d \n", number_of_lines);

}
int main() {
     leftKey= false; rightKey = false;
    	// Define the gravity vector.
    srand( (unsigned)time(NULL) );
	b2Vec2 gravity(0.0f, -10.0f);

	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity);

	// Define the ground body.
    renderer = new Renderer(1200, 800, "Platformer");

    camera = new OrthographicCamera(screenWidth/2, screenHeight/2, screenWidth, screenHeight, -1, 100);

    renderer->setCamera(camera);

    createWorld();


    renderer->setUpdateCallback(&update);

    renderer->setKeyboardCallback(&key_press);
    renderer->setMouseButtonCallback(&mouse_button_press);
    renderer->setMouseMoveCallback(&mouse_move);

    renderer->start();

    return 0;
}

