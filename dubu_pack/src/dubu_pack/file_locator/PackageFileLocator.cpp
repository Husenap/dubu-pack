#include "PackageFileLocator.h"

namespace dubu::pack {

PackageFileLocator::PackageFileLocator(std::filesystem::path packagePath)
    : mUnpacker(packagePath) {}

std::optional<blob> PackageFileLocator::ReadFile(std::string_view filePath) {
	return mUnpacker.ReadFile(filePath);
}

}  // namespace dubu::pack
