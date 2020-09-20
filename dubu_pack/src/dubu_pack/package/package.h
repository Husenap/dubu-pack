#pragma once

#include "file_locator/IFileLocator.h"

namespace dubu_pack {

enum class package_mode {
	package,
	filesystem,
};

class Package {
public:
	Package(std::string_view packageName);

	auto& GetFileLocator() { return mFileLocator; }

	std::string_view GetPackageName() const;
	package_mode GetPackageMode() const;

private:
	std::string mPackageName;

	package_mode mPackageMode;

	std::unique_ptr<IFileLocator> mFileLocator;
};

}  // namespace dubu_pack
