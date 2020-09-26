![Windows](https://github.com/Husenap/dubu-pack/workflows/Windows/badge.svg)
![Ubuntu](https://github.com/Husenap/dubu-pack/workflows/Ubuntu/badge.svg)

```
   _     _                       _   
 _| |_ _| |_ _ _ ___ ___ ___ ___| |_ 
| . | | | . | | |___| . | .'|  _| '_|
|___|___|___|___|   |  _|__,|___|_,_|
                    |_|              
```
File Packer for use in games.

## Features
* Can pack multiple folders from a CMakeLists.txt configuration
* Can pack folders from C++
* Automatically reads from package if it exists, otherwise it reads from the folder at runtime

## Example Usage

The following cmake code will tell dubu-pack to package the `assets` and `shaders` folders into packaged files.

##### **`CMakeLists.txt`**
```cmake
dubu_pack_package("${PROJECT_SOURCE_DIR}/bin/assets"
                  "${PROJECT_SOURCE_DIR}/bin/shaders")
```

##### **`Pack a folder`**
```cpp
#include <dubu_pack/dubu_pack.h>

int main() {
    dubu::pack::Packer packer("path/to/assets");
    packer.Pack(); // Writes a package file at path/to/assets.dbp
}
```

##### **`Read from folder or package`**
```cpp
#include <dubu_pack/dubu_pack.h>

int main() {
	// Opens package file if it exists, otherwise it will read from disk
	dubu::pack::Package package("path/to/assets");

	// returns a blob containing the file data
	auto fileContent = package.GetFileLocator()->ReadFile("test.png");
	if (fileContent) {
		// do cool image stuff with fileContent
	}
}
```