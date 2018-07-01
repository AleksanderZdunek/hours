#include <iostream>
#include <fstream>

const char* filepath  = "default.txt";

int main(int argc, char* argv[])
{
	std::cout << "Hours" << std::endl;

	if(1 < argc) filepath = argv[1];
	std::cout << "Open file " << filepath << std::endl;
	std::ifstream file(filepath);

	char line[512];

	while(file.good())
	{
		file.getline(line, 512);
		std::cout << line << "Meep!";
	}

	return 0;
}