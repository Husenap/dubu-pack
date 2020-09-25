#pragma once

#include "dubu_pack/file_locator/IFileLocator.h"

namespace dubu_pack {

enum class PackageMode {
	Package,
	Filesystem,
};

class Package {
public:
	Package(std::string_view packageName);

	auto& GetFileLocator() { return mFileLocator; }

	std::string_view GetPackageName() const;
	PackageMode GetPackageMode() const;

private:
	std::string mPackageName;

	PackageMode mPackageMode;

	std::unique_ptr<IFileLocator> mFileLocator;
};

}  // namespace dubu_pack
