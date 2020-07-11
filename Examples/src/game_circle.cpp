#include "game_circle.h"
#include "core.h"
#include <stdio.h>
#include <iostream>

GameCircle::GameCircle(int radius, int x, int y) {
    renderable = new Circle(radius);
    printf("CREATED GAME CIRCLE \n");
    renderer->addRenderable(renderable);
    renderable->setColor(1.0, 1.0, 0.0, 1.0);
    std::cout << "addr off renderable : " << renderable << std::endl; 

        // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x * screenToWorld, y * screenToWorld);
    body = world->CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape dynamicCircle;
    dynamicCircle.m_radius = radius * screenToWorld;

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicCircle;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.3f;

    // Add the shape to the body.
    body->CreateFixture(&fixtureDef);
}

void GameCircle::update() {
    b2Vec2 position = body->GetPosition();
    float angle = body->GetAngle();

    renderable->position.x = position.x * 100;
    renderable->position.y = position.y * 100;
    renderable->rotation = angle;
}

Renderable *GameCircle::getRenderable() {
    return renderable;
}
