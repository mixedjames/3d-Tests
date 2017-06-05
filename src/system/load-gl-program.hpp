#pragma once

#include <istream>
#include "unique-gl-resources.hpp"

UniqueGLProgram LoadGLProgram(std::istream& vShaderSource, std::istream& fShaderSource);

UniqueGLProgram LoadGLProgram(const std::string& vShaderSource, const std::string& fShaderSource);