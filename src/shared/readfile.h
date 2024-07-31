#pragma once
#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

static std::string readFile(const std::filesystem::path& filePath) {
	std::ifstream file(filePath);
	if (!file) {
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return "";
	}
	return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}
