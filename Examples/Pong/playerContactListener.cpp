#include "playerContactListener.h"
#include "game_rect.h"
#include "core_pong.h"

#include<iostream>

using namespace std;

void PlayerContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {
}

void PlayerContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) { 
}

void PlayerContactListener::BeginContact(b2Contact* contact) {
    b2Body *ball = nullptr;
    b2Body *player = nullptr;
    b2Body *brick = nullptr;

    GameObject *bodyA = (GameObject *)contact->GetFixtureA()->GetBody()->GetUserData();
    const char *bodyAUserData = bodyA->getTag().c_str();
    string dataA(bodyAUserData);

    GameObject *bodyB = (GameObject *)contact->GetFixtureB()->GetBody()->GetUserData();
    const char *bodyBUserData = bodyB->getTag().c_str(); 
    string dataB(bodyBUserData);

    if(!dataA.compare("BALL")) {
        ball = contact->GetFixtureA()->GetBody();
    } else if(!dataB.compare("BALL")) {
        ball = contact->GetFixtureB()->GetBody();
    }

    if(!dataA.compare("PLAYER")) {
        player = contact->GetFixtureA()->GetBody();
    } else if(!dataB.compare("PLAYER")) {
        player = contact->GetFixtureB()->GetBody();
    }

    if(!dataA.compare("BRICK")) {
        brick = contact->GetFixtureA()->GetBody();
    } else if(!dataB.compare("BRICK")) {
        brick = contact->GetFixtureB()->GetBody();
    }
    
    if(ball && player) {
        //printf("SETTING BALL SPEED \n");
        int numPoints = contact->GetManifold()->pointCount;

        //...world manifold is helpful for getting locations
        b2WorldManifold worldManifold;
        contact->GetWorldManifold( &worldManifold );
        
        for (int i = 0; i < numPoints; i++) {
            //printf("PLAYER WIDTH : %f \n " , playerWidth * screenToWorld);
            float dx = worldManifold.points[i].x - player->GetPosition().x;
            
            float angle = 3.14 / 2.0 - dx * 3.14 / 4.0;
            float speed = ball->GetLinearVelocity().Length();
            ball->SetLinearVelocity(b2Vec2(speed * cos(angle), speed * sin (angle)));
        }

    } 
    if(ball && brick) {
        ((GameObject*)(brick->GetUserData()))->destroy();
    }


}
void PlayerContactListener::EndContact(b2Contact* contact) {
}
