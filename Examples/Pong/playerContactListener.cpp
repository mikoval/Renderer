#include "playerContactListener.h"
#include "game_rect.h"
#include "core_pong.h"

using namespace std;

void PlayerContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold) {

}

void PlayerContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse) { 
    
}

void PlayerContactListener::BeginContact(b2Contact* contact) {
    b2Body *ball = nullptr;
    b2Body *player = nullptr;
     const char *bodyAUserData = (const char *)contact->GetFixtureA()->GetBody()->GetUserData();
     const char *bodyBUserData = (const char *)contact->GetFixtureB()->GetBody()->GetUserData();
    string dataA(bodyAUserData);
    string dataB(bodyBUserData);
    printf("BODY A USER DATA : %s \n", bodyAUserData);
    printf("BODY B USER DATA : %s \n", bodyBUserData);
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
    
    if(ball && player) {
        printf("SETTING BALL SPEED \n");
        int numPoints = contact->GetManifold()->pointCount;

        //...world manifold is helpful for getting locations
        b2WorldManifold worldManifold;
        contact->GetWorldManifold( &worldManifold );
        
        for (int i = 0; i < numPoints; i++) {
            printf("X: %f, Y: %f \n", worldManifold.points[i].x, worldManifold.points[i].y);
            printf("PLAYER WIDTH : %f \n " , playerWidth * screenToWorld);
            float dx = worldManifold.points[i].x - player->GetPosition().x;
            
            float angle = 3.14 / 2.0 - dx * 3.14 / 4.0;
            printf("FINDME: ==================== X VAL = %f \n", dx);
            ball->SetLinearVelocity(b2Vec2(3.0 * cos(angle), 3.0 * sin (angle)));
        }

    }

//    printf("FINDME: CONTACT STARTED \n");

}
void PlayerContactListener::EndContact(b2Contact* contact) {
//    printf("FINDME: CONTACT FINISHED \n");
}
