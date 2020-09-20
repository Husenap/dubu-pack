#pragma once

namespace dubu_pack {

class Unpacker {
public:
	Unpacker(std::filesystem::path packagePath);

	std::optional<blob> ReadFile(std::filesystem::path filePath);

private:
	std::ifstream mStream;

	internal::PackageHeader mPackageHeader;

	std::map<std::filesystem::path, internal::FileHeader> mFileIndex;
};

}  // namespace dubu_pack