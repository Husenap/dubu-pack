#include "Packer.h"

#include <fstream>

#include "serializer/Serializer.h"

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

	std::ofstream outputPackageFile(outputPackagePath, std::ios_base::binary);

	internal::PackageHeader packageHeader{
	    .magicNumber   = internal::MagicNumber,
	    .versionNumber = internal::VersionNumber,
	    .numberOfFiles = static_cast<uint32_t>(filePaths.size()),
	    .baseOffset    = 0,
	};

	serializer::Write(outputPackageFile, packageHeader.magicNumber);
	serializer::Write(outputPackageFile, packageHeader.versionNumber);
	serializer::Write(outputPackageFile, packageHeader.numberOfFiles);
	const auto baseOffsetPosition = serializer::Write(outputPackageFile, packageHeader.baseOffset);

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

		currentPosition += fileSize;

		serializer::Write(outputPackageFile, fileHeader.filePath.generic_string());
		serializer::Write(outputPackageFile, fileHeader.originalFileSize);
		serializer::Write(outputPackageFile, fileHeader.compressedFileSize);
		serializer::Write(outputPackageFile, fileHeader.position);
	}

	packageHeader.baseOffset = static_cast<int64_t>(outputPackageFile.tellp());

	serializer::Seek(outputPackageFile, baseOffsetPosition);
	serializer::Write(outputPackageFile, packageHeader.baseOffset);
	serializer::Seek(outputPackageFile, static_cast<std::streampos>(packageHeader.baseOffset));

	// Write file data
	for (const auto& filePath : filePaths) {
		std::ifstream fileStream(filePath, std::ios_base::binary);
		outputPackageFile << fileStream.rdbuf();
	}
}

}  // namespace dubu_pack