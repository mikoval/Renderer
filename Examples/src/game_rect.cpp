#include "game_rect.h"
#include "core.h"

GameRect::GameRect(int width, int height, int x, int y) {
    renderable = new Rectangle(width, height);
    renderer->addRenderable(renderable);

        // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x * screenToWorld, y * screenToWorld);
    body = world->CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(width * screenToWorld / 2.0, height * screenToWorld / 2.0);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
}

void GameRect::update() {
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    renderable->position.x = position.x * 100;
    renderable->position.y = position.y * 100;
    renderable->rotation = angle;
}
