#ifndef SHADER_HPP
#define SHADER_HPP

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

GLuint LoadShaders(const char* vertex_file_path, const char* fragment_file_path);

#endif