#include "FilesystemFileLocator.h"

#include <fstream>

namespace dubu_pack {

FilesystemFileLocator::FilesystemFileLocator(std::string_view packageName)
    : mPackagePath(packageName) {}

std::optional<blob> FilesystemFileLocator::ReadFile(std::string_view filePath) {
	std::filesystem::path path = mPackagePath / filePath;

	if (!std::filesystem::exists(path)) {
		return std::nullopt;
	}

	std::ifstream fileStream(path, std::ios_base::binary);

	if (fileStream.fail()) {
		return std::nullopt;
	}

	fileStream.seekg(0, fileStream.end);
	auto fileSize = fileStream.tellg();
	fileStream.seekg(0, fileStream.beg);

	blob data;

	data.resize(static_cast<size_t>(fileSize));
	fileStream.read(data.data(), fileSize);

	return data;
}

}  // namespace dubu_pack