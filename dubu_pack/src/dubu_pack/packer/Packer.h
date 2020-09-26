#pragma once

namespace dubu::pack {

class Packer {
public:
	Packer(std::string_view packageName);

	void Pack();

private:
	std::string mPackageName;
};

}  // namespace dubu::pack