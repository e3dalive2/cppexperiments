#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

std::string decode_message(const std::string& file_path) {
	std::ifstream file(file_path);
	std::string line, word;
	int number;
	std::map<int, std::string> word_map;

	// Read the file and map the numbers to words
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		if (!(iss >> number >> word)) { break; } // Error
		word_map[number] = word;
	}
	file.close();
	// Decode the message
	std::string decoded_message;
	int pyramid_level = 1; // The current level of the pyramid
	int word_position = 1; // The position in the file, following the pyramid pattern

	while (word_map.find(word_position) != word_map.end()) {
		decoded_message += word_map[word_position] + " ";
		pyramid_level++;
		word_position += pyramid_level;
	}

	// Remove the last space if there is one
	if (!decoded_message.empty() && decoded_message[decoded_message.length() - 1] == ' ') {
		decoded_message.erase(decoded_message.length() - 1);
	}

	return decoded_message;
}

int main() {
	std::string file_path = "coding_qual_input.txt";//coding_qual_input
	std::string message = decode_message(file_path);
	std::cout << "Decoded message: " << message << std::endl;
	return 0;
}