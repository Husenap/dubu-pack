#include "Unpacker.h"

#include "dubu_pack/serializer/Serializer.h"

namespace dubu_pack {

Unpacker::Unpacker(std::filesystem::path packagePath)
    : mStream(packagePath, std::ios_base::binary) {
	mPackageHeader.magicNumber = serializer::Read<uint32_t>(mStream);
	if (mPackageHeader.magicNumber != internal::MagicNumber) {
		throw std::runtime_error("Package file format is unknown!");
	}

	mPackageHeader.versionNumber = serializer::Read<uint32_t>(mStream);
	if (mPackageHeader.versionNumber != internal::VersionNumber) {
		throw std::runtime_error("Package version doesn't match the library version used!");
	}

	mPackageHeader.numberOfFiles = serializer::Read<uint32_t>(mStream);
	mPackageHeader.baseOffset    = serializer::Read<uint64_t>(mStream);

	for (uint32_t i = 0; i < mPackageHeader.numberOfFiles; ++i) {
		internal::FileHeader fileHeader;

		fileHeader.filePath           = serializer::Read<std::string>(mStream);
		fileHeader.originalFileSize   = serializer::Read<uint32_t>(mStream);
		fileHeader.compressedFileSize = serializer::Read<uint32_t>(mStream);
		fileHeader.position           = serializer::Read<uint64_t>(mStream);

		mFileIndex[fileHeader.filePath] = fileHeader;
	}
}

std::optional<blob> Unpacker::ReadFile(std::filesystem::path filePath) {
	auto it = mFileIndex.find(filePath);
	if (it == mFileIndex.end()) {
		return std::nullopt;
	}

	serializer::Seek(mStream, static_cast<std::streamoff>(mPackageHeader.baseOffset + it->second.position));

	blob data;

	data.resize(it->second.originalFileSize);
	mStream.read(&data[0], it->second.originalFileSize);

	return data;
}

}  // namespace dubu_pack