#include "filesystem_file_locator.h"

#include <fstream>

namespace dubu_pack {

std::optional<blob> filesystem_file_locator::read_file(std::string_view filePath) {
	if (!std::filesystem::exists(filePath)) {
		return std::nullopt;
	}

	std::ifstream fileStream(filePath, std::ios_base::binary);

	if (fileStream.fail()) {
		return std::nullopt;
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