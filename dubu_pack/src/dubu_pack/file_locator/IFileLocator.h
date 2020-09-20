#pragma once

namespace dubu_pack {

class IFileLocator {
public:
	virtual ~IFileLocator() = default;

	virtual std::optional<blob> ReadFile(std::string_view filePath) = 0;
};

}  // namespace dubu_pack