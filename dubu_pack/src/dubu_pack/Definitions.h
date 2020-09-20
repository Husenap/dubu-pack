#pragma once

namespace dubu_pack::internal {

template <char a, char b, char c, char d>
struct FourCC {
	static const uint32_t value = (uint32_t(d) << 24) | (uint32_t(c) << 16) | (uint32_t(b) << 8) | uint32_t(a);
};

struct PackageHeader {
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint32_t numberOfFiles;
	uint64_t baseOffset;
};

struct FileHeader {
	std::filesystem::path filePath;
	uint32_t originalFileSize;
	uint32_t compressedFileSize;
	uint64_t position;
};

constexpr uint32_t MagicNumber   = FourCC<'D', 'U', 'B', 'U'>::value;
constexpr uint32_t VersionNumber = FourCC<0, 1, 0, 0>::value;

constexpr char* PackageExtension = ".dbp";

}  // namespace dubu_pack::internal

namespace dubu_pack {

using blob = std::vector<char>;

}  // namespace dubu_pack