#include <iostream>
#include <filesystem>

#include <dubu_pack/dubu_pack.h>

constexpr const char* DubuPackLogo = R"(
   _     _                       _   
 _| |_ _| |_ _ _ ___ ___ ___ ___| |_ 
| . | | | . | | |___| . | .'|  _| '_|
|___|___|___|___|   |  _|__,|___|_,_|
                    |_|              
)";

int main(int argc, char** argv) {
	std::cout << DubuPackLogo << std::endl;

	for (int i = 1; i < argc; ++i) {
        std::string packagePath = argv[i];

        if (!std::filesystem::is_directory(packagePath)) {
			std::cerr << "Invalid directory path: " << packagePath << std::endl;
            continue;
        }

        std::cout << "Packing: " << packagePath << std::endl;
        dubu_pack::Packer packer(packagePath);
        packer.Pack();
	}

	return 0;
}