#include "filesystem_file_locator.h"

#include <fstream>

namespace dubu_pack {

dubu_pack::blob filesystem_file_locator::read_file(std::string_view filePath) throw() {
	if (!std::filesystem::exists(filePath)) {
		throw std::runtime_error("File doesn't exist!");
	}

	std::ifstream fileStream(filePath, std::ios_base::binary);

	if (fileStream.fail()) {
		throw std::runtime_error("Failed to open file!");
	}

	fileStream.seekg(0, fileStream.end);
	auto fileSize = static_cast<std::size_t>(fileStream.tellg());
	fileStream.seekg(0, fileStream.beg);

	blob data;

	data.resize(static_cast<std::size_t>(fileSize));
	fileStream.read(data.data(), fileSize);

	return data;
}

}  // namespace dubu_pack