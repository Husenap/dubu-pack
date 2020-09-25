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

## Example Usage

The following cmake code will tell dubu-pack to package the `assets` and `shaders` folders into packaged files.

```cmake
dubu_pack_package("${PROJECT_SOURCE_DIR}/bin/assets"
                  "${PROJECT_SOURCE_DIR}/bin/shaders")
```