#pragma once
#include <Renderer/renderer.h>
#include <box2d/box2d.h>
#include <Renderer/2d_shapes.h>

static int screenWidth = 1200;
static int screenHeight = 800;
static float worldToScreen = 100.0f;
static float screenToWorld = 1.0f/worldToScreen;
extern Renderer *renderer;
extern b2World *world;
