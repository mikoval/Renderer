#include <Renderer/shader.h>
#include <iostream>
#include <Renderer/renderer.h>

#include "gl_utils.h"
#include "gl_core.h"

using namespace std;
int Shader::getProgram() {
    return shaderProgram;
}

