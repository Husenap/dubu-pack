#pragma once

namespace dubu::pack {

class Packer {
public:
	Packer(std::string_view packageName, bool useCompression = false);

	void Pack();

private:
	std::string mPackageName;
	bool        mUseCompression;
	blob        mCompressionBuffer;
};

}  // namespace dubu::pack