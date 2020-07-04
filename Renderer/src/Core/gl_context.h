#pragma once
#include <Renderer/renderer.h>

using namespace std;

GLFWwindow *makeWindow (int width, int height, string name);

int renderLoop(Renderer *renderer, int width, int height, string name);
