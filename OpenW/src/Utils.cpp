#include "Utils.h"

#include <fstream>

std::string ReadTextFile(const char* filePath)
{
	std::string line = "";
	std::string fileContent;
	std::ifstream stream(filePath, std::ifstream::in);
	while (!stream.eof())
	{
		std::getline(stream, line);
		fileContent.append(line + "\n");
	}
	stream.close();
	return fileContent;
}
