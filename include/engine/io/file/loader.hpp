#ifndef INCLUDE_ENGINE_IO_FILE_LOADER_HPP_
#define INCLUDE_ENGINE_IO_FILE_LOADER_HPP_

#include <string>
#include <GL/glew.h>
#include <vector>

bool ioFileLoad(std::string filename, std::vector<GLchar> &buffer, bool binary = false);

#endif
