#include "Packer.h"

#include <dubu_serialize/dubu_serialize.h>
#include <zlib/zlib.h>

namespace dubu::pack {

Packer::Packer(std::string_view packageName, bool useCompression)
    : mPackageName(packageName)
    , mUseCompression(useCompression) {}

void Packer::Pack() {
	std::filesystem::path inputDirectoryPath = mPackageName;
	if (!std::filesystem::is_directory(inputDirectoryPath)) {
		throw std::runtime_error("Input path is not a directory!");
	}

	std::filesystem::path outputPackagePath;
	outputPackagePath = mPackageName;
	outputPackagePath.replace_extension(internal::PackageExtension);
	std::filesystem::path temporaryPackagePath = outputPackagePath;
	temporaryPackagePath.replace_extension(".tmp");

	std::vector<std::filesystem::path> filePaths;

	for (auto& p :
	     std::filesystem::recursive_directory_iterator(inputDirectoryPath)) {
		auto path = p.path();
		if (std::filesystem::is_directory(path)) {
			continue;
		}

		filePaths.push_back(path);
	}

	dubu::serialize::FileBuffer packageFileBuffer(
	    outputPackagePath, dubu::serialize::FileBuffer::Mode::Write);

	internal::PackageHeader packageHeader{
	    .magicNumber   = internal::MagicNumber,
	    .versionNumber = internal::VersionNumber,
	    .numberOfFiles = static_cast<uint32_t>(filePaths.size()),
	    .baseOffset    = 0,
	};

	packageFileBuffer << packageHeader.magicNumber;
	packageFileBuffer << packageHeader.versionNumber;
	packageFileBuffer << packageHeader.numberOfFiles;
	const auto baseOffsetPosition = packageFileBuffer.Tell<int64_t>();
	packageFileBuffer << packageHeader.baseOffset;

	int64_t currentPosition = 0;

	// Write file headers and file contents
	{
		dubu::serialize::FileBuffer temporaryFileBuffer(
		    temporaryPackagePath, dubu::serialize::FileBuffer::Mode::Write);
		for (const auto& filePath : filePaths) {
			auto fileSize = std::filesystem::file_size(filePath);

			internal::FileHeader fileHeader{
			    .filePath =
			        std::filesystem::relative(filePath, inputDirectoryPath),
			    .originalFileSize   = static_cast<uint32_t>(fileSize),
			    .compressedFileSize = 0,
			    .position           = currentPosition,
			};

			if (mUseCompression) {
				uLong bufferBound = compressBound(fileHeader.originalFileSize);

				if (mCompressionBuffer.size() < bufferBound) {
					mCompressionBuffer.resize(bufferBound);
				}

				std::ifstream sourceFileStream(filePath, std::ios_base::binary);
				blob          sourceFile;
				sourceFile.resize(fileHeader.originalFileSize);
				sourceFileStream.read(sourceFile.data(),
				                      fileHeader.originalFileSize);

				uLongf sourceLength = bufferBound;
				compress((Bytef*)mCompressionBuffer.data(),
				         &sourceLength,
				         (Bytef*)sourceFile.data(),
				         (uLong)sourceFile.size());

				if (sourceLength < fileHeader.originalFileSize) {
					fileHeader.compressedFileSize =
					    static_cast<uint32_t>(sourceLength);
					temporaryFileBuffer.Write(mCompressionBuffer.data(),
					                          fileHeader.compressedFileSize);
					currentPosition += fileHeader.compressedFileSize;
				} else {
					temporaryFileBuffer.Write(sourceFile.data(),
					                          fileHeader.originalFileSize);
					currentPosition += fileHeader.originalFileSize;
				}
			} else {
				std::ifstream sourceFileStream(filePath, std::ios_base::binary);
				temporaryFileBuffer.Write(sourceFileStream);
				currentPosition += fileHeader.originalFileSize;
			}

			packageFileBuffer << fileHeader;
		}
	}

	packageHeader.baseOffset = packageFileBuffer.Tell<int64_t>();

	packageFileBuffer.Seek(baseOffsetPosition);
	packageFileBuffer << packageHeader.baseOffset;
	packageFileBuffer.Seek(packageHeader.baseOffset);

	// Write file data
	{
		std::ifstream fileStream(temporaryPackagePath, std::ios_base::binary);
		packageFileBuffer.Write(fileStream);
	}

	std::filesystem::remove(temporaryPackagePath);
}

}  // namespace dubu::pack