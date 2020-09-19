#pragma once

namespace dubu_pack {

enum class package_mode {
	package,
	filesystem,
};

class package {
public:
	package(std::string_view package);

	std::string_view get_package_name() const;
	package_mode get_package_mode() const;

private:
	std::string mPackageName;
	std::filesystem::path mPackagePath;

	package_mode mPackageMode;
};

}  // namespace dubu_pack
