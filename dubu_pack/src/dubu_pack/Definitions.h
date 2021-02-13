#pragma once

#include <dubu_serialize/dubu_serialize.h>

namespace dubu::pack::internal {

template <char a, char b, char c, char d>
struct FourCC {
	static const uint32_t value = (uint32_t(d) << 24) | (uint32_t(c) << 16) | (uint32_t(b) << 8) | uint32_t(a);
};

constexpr uint32_t MagicNumber   = FourCC<'D', 'U', 'B', 'U'>::value;
constexpr uint32_t VersionNumber = FourCC<0, 3, 0, 0>::value;

struct PackageHeader {
	uint32_t magicNumber;
	uint32_t versionNumber;
	uint32_t numberOfFiles;
	int64_t baseOffset;

	void Serialize(dubu::serialize::ReadBuffer& buffer) {
		buffer >> magicNumber;
		buffer >> versionNumber;
		buffer >> numberOfFiles;
		buffer >> baseOffset;
	}
	void Serialize(dubu::serialize::WriteBuffer& buffer) const {
		buffer << magicNumber;
		buffer << versionNumber;
		buffer << numberOfFiles;
		buffer << baseOffset;
	}
};

struct FileHeader {
	std::filesystem::path filePath;
	uint32_t originalFileSize;
	uint32_t compressedFileSize;
	int64_t position;

	void Serialize(dubu::serialize::ReadBuffer& buffer) {
		buffer >> filePath;
		buffer >> originalFileSize;
		buffer >> compressedFileSize;
		buffer >> position;
	}
	void Serialize(dubu::serialize::WriteBuffer& buffer) const {
		buffer << filePath;
		buffer << originalFileSize;
		buffer << compressedFileSize;
		buffer << position;
	}
};

constexpr const char* PackageExtension = ".dbp";

}  // namespace dubu::pack::internal

namespace dubu::pack {

using blob = std::vector<char>;

}  // namespace dubu::pack