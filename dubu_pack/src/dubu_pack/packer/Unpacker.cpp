#include "Unpacker.h"

namespace dubu_pack {

Unpacker::Unpacker(std::filesystem::path packagePath)
    : mFileBuffer(packagePath, dubu::serialize::FileBuffer::Mode::Read) {
	mFileBuffer >> mPackageHeader;
	if (mPackageHeader.magicNumber != internal::MagicNumber) {
		throw std::runtime_error("Package file format is unknown!");
	}
	if (mPackageHeader.versionNumber != internal::VersionNumber) {
		throw std::runtime_error("Package version doesn't match the library version used!");
	}

	for (uint32_t i = 0; i < mPackageHeader.numberOfFiles; ++i) {
		internal::FileHeader fileHeader;

		mFileBuffer >> fileHeader;

		mFileIndex[fileHeader.filePath] = fileHeader;
	}
}

std::optional<blob> Unpacker::ReadFile(std::filesystem::path filePath) {
	auto it = mFileIndex.find(filePath);
	if (it == mFileIndex.end()) {
		return std::nullopt;
	}

	mFileBuffer.Seek(mPackageHeader.baseOffset + it->second.position);

	blob data;

	data.resize(it->second.originalFileSize);
	mFileBuffer.Read(&data[0], it->second.originalFileSize);

	return data;
}

}  // namespace dubu_pack