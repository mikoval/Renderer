#pragma once
#include <Renderer/renderer.h>
#include <box2d/box2d.h>
#include <Renderer/2d_shapes.h>

extern int screenWidth;
extern int screenHeight;

static float worldToScreen = 100.0f;
static float screenToWorld = 1.0f/worldToScreen;
extern Renderer *renderer;
extern b2World *world;
