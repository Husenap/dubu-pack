#include "package.h"

#include "file_locator/filesystem_file_locator.h"
#include "file_locator/package_file_locator.h"

namespace package_internal {
constexpr char* PackageExtension = ".dbp";
}

namespace dubu_pack {

package::package(std::string_view packageName)
    : mPackageName(packageName) {

	mPackagePath = mPackageName;
	mPackagePath.replace_extension(package_internal::PackageExtension);

	auto cwd = std::filesystem::current_path();

	if (std::filesystem::exists(mPackagePath)) {
		mPackageMode = package_mode::package;
		mFileLocator = std::make_unique<package_file_locator>();
	} else {
		mPackageMode = package_mode::filesystem;
		mFileLocator = std::make_unique<filesystem_file_locator>();
	}
}

std::string_view package::get_package_name() const {
	return mPackageName;
}

dubu_pack::package_mode package::get_package_mode() const {
	return mPackageMode;
}

}  // namespace dubu_pack
