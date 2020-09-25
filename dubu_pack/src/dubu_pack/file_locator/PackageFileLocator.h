#pragma once

#include "IFileLocator.h"
#include "dubu_pack/packer/Unpacker.h"

namespace dubu_pack {

class PackageFileLocator : public IFileLocator {
public:
	PackageFileLocator(std::filesystem::path packagePath);

	std::optional<blob> ReadFile(std::string_view filePath) override;

private:
	Unpacker mUnpacker;
};

}  // namespace dubu_pack
