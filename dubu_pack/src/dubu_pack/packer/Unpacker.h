#pragma once

#include <dubu_serialize/dubu_serialize.h>

namespace dubu::pack {

class Unpacker {
public:
	Unpacker(std::filesystem::path packagePath);

	std::optional<blob> ReadFile(std::filesystem::path filePath);

private:
	dubu::serialize::FileBuffer mFileBuffer;

	internal::PackageHeader mPackageHeader;

	std::map<std::filesystem::path, internal::FileHeader> mFileIndex;

	blob mCompressionBuffer;
};

}  // namespace dubu::pack