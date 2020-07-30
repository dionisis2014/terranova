#include "engine/io/file/loader.hpp"
#include <fstream>

bool ioFileLoad(std::string filename, std::vector<GLchar> &buffer, bool binary) {
	std::ifstream fileStream;
	if (binary)
		fileStream.open(filename, std::ios::binary);
	else
		fileStream.open(filename);
	if (!fileStream.is_open())
		return false;

	fileStream.seekg(0, std::ios::end);
	std::size_t fileSize = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);
	if (!fileStream.good()) {
		fileStream.close();
		return false;
	}

	if (fileSize) {
		buffer.clear();
		buffer.resize(fileSize + (binary ? 0 : 1));
		fileStream.read(buffer.data(), fileSize);
		if (!fileStream.good()) {
			fileStream.close();
			return false;
		}
	}

	fileStream.close();
	if (!binary)
		buffer.push_back('\0');
	return true;
}
