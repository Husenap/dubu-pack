#pragma once

#include "IFileLocator.h"

namespace dubu_pack {

class FilesystemFileLocator : public IFileLocator {
public:
	FilesystemFileLocator(std::string_view packageName);

	std::optional<blob> ReadFile(std::string_view filePath) override;

private:
	std::filesystem::path mPackagePath;
};

}  // namespace dubu_pack