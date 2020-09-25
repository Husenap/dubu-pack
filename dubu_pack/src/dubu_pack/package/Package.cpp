#include "Package.h"

#include "file_locator/FilesystemFileLocator.h"
#include "file_locator/PackageFileLocator.h"

namespace dubu_pack {

Package::Package(std::string_view packageName)
    : mPackageName(packageName) {

	std::filesystem::path packagePath = mPackageName;
	packagePath.replace_extension(internal::PackageExtension);

	if (std::filesystem::exists(packagePath)) {
		mPackageMode = PackageMode::Package;
		mFileLocator = std::make_unique<PackageFileLocator>(packagePath);
	} else {
		mPackageMode = PackageMode::Filesystem;
		mFileLocator = std::make_unique<FilesystemFileLocator>(mPackageName);
	}
}

std::string_view Package::GetPackageName() const {
	return mPackageName;
}

dubu_pack::PackageMode Package::GetPackageMode() const {
	return mPackageMode;
}

}  // namespace dubu_pack
