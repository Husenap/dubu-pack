#include "package.h"

#include <filesystem>

namespace package_internal {

constexpr char* PackageExtension = ".dbp";

}

namespace dubu_pack {

package::package(std::string_view package)
    : mPackageName(package) {
	mPackagePath = mPackageName;
	mPackagePath.replace_extension(package_internal::PackageExtension);

	auto cwd = std::filesystem::current_path();

	if (std::filesystem::exists(mPackagePath)) {
		mPackageMode = package_mode::package;
	} else {
		mPackageMode = package_mode::filesystem;
	}
}

std::string_view package::get_package_name() const {
	return mPackageName;
}

dubu_pack::package_mode package::get_package_mode() const {
	return mPackageMode;
}

}  // namespace dubu_pack
