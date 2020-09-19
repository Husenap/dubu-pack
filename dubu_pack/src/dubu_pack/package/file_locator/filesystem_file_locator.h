#pragma once

#include "file_locator.h"

namespace dubu_pack {

class filesystem_file_locator : public file_locator {
public:
	std::optional<blob> read_file(std::string_view filePath) override;
};

}  // namespace dubu_pack