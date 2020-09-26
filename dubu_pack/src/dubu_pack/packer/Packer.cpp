#include "Packer.h"

#include <dubu_serialize/dubu_serialize.h>

namespace dubu_pack {

Packer::Packer(std::string_view packageName)
    : mPackageName(packageName) {}

void Packer::Pack() {
	std::filesystem::path inputDirectoryPath = mPackageName;
	if (!std::filesystem::is_directory(inputDirectoryPath)) {
		throw std::runtime_error("Input path is not a directory!");
	}

	std::filesystem::path outputPackagePath;
	outputPackagePath = mPackageName;
	outputPackagePath.replace_extension(internal::PackageExtension);

	std::vector<std::filesystem::path> filePaths;

	for (auto& p : std::filesystem::recursive_directory_iterator(inputDirectoryPath)) {
		auto path = p.path();
		if (std::filesystem::is_directory(path)) {
			continue;
		}

		filePaths.push_back(path);
	}

	dubu::serialize::FileBuffer fileBuffer(outputPackagePath, dubu::serialize::FileBuffer::Mode::Write);

	internal::PackageHeader packageHeader{
	    .magicNumber   = internal::MagicNumber,
	    .versionNumber = internal::VersionNumber,
	    .numberOfFiles = static_cast<uint32_t>(filePaths.size()),
	    .baseOffset    = 0,
	};

	fileBuffer << packageHeader.magicNumber;
	fileBuffer << packageHeader.versionNumber;
	fileBuffer << packageHeader.numberOfFiles;
	const auto baseOffsetPosition = fileBuffer.Tell<int64_t>();
	fileBuffer << packageHeader.baseOffset;

	int64_t currentPosition = 0;

	// Write file headers
	for (const auto& filePath : filePaths) {
		auto fileSize = std::filesystem::file_size(filePath);

		internal::FileHeader fileHeader{
		    .filePath           = std::filesystem::relative(filePath, inputDirectoryPath),
		    .originalFileSize   = static_cast<uint32_t>(fileSize),
		    .compressedFileSize = 0,
		    .position           = currentPosition,
		};

		currentPosition += static_cast<int64_t>(fileSize);

		fileBuffer << fileHeader;
	}

	packageHeader.baseOffset = fileBuffer.Tell<int64_t>();

	fileBuffer.Seek(baseOffsetPosition);
	fileBuffer << packageHeader.baseOffset;
	fileBuffer.Seek(packageHeader.baseOffset);

	std::ofstream offf;
	// Write file data
	for (const auto& filePath : filePaths) {
		std::ifstream fileStream(filePath, std::ios_base::binary);
		fileBuffer.Write(fileStream);
	}
}

}  // namespace dubu_pack