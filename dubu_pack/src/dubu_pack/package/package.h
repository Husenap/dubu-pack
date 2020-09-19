#pragma once

#include "file_locator/file_locator.h"

namespace dubu_pack {

enum class package_mode {
	package,
	filesystem,
};

class package {
public:
	package(std::string_view packageName);

	auto& get_file_locator() { return mFileLocator; }

	std::string_view get_package_name() const;
	package_mode get_package_mode() const;

private:
	std::string mPackageName;
	std::filesystem::path mPackagePath;

	package_mode mPackageMode;

	std::unique_ptr<file_locator> mFileLocator;
};

}  // namespace dubu_pack
