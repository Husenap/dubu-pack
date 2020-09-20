#pragma once

namespace dubu_pack {

class Packer {
public:
	Packer(std::string_view packageName);

	void Pack();

private:
	std::string mPackageName;
};

}  // namespace dubu_pack