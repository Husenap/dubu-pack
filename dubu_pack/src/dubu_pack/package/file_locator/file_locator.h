#pragma once

namespace dubu_pack {

using blob = std::vector<char>;

class file_locator {
public:
	virtual blob read_file(std::string_view filePath) throw() = 0;

protected:
private:
};

}  // namespace dubu_pack