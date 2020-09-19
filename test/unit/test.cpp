#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

TEST(dubu_pack, package_name) {
	dubu_pack::package package("assets");

	EXPECT_STREQ("assets", package.get_package_name().data());
	EXPECT_STRNE("random name", package.get_package_name().data());
}

TEST(dubu_pack, packed) {
	dubu_pack::package package("packed");

	EXPECT_EQ(package.get_package_mode(), dubu_pack::package_mode::package);
}

TEST(dubu_pack, unpacked) {
	dubu_pack::package package("unpacked");

	EXPECT_EQ(package.get_package_mode(), dubu_pack::package_mode::filesystem);
}

TEST(dubu_pack, read_packed_file) {
	dubu_pack::package package("packed");

	EXPECT_EQ(package.get_package_mode(), dubu_pack::package_mode::package);

	dubu_pack::blob fileContent = package.get_file_locator()->read_file("test.txt");

	EXPECT_THAT(fileContent, testing::ElementsAreArray({'H','e','l','l','o',' ','W','o','r','l','d','!'}));
}

TEST(dubu_pack, read_unpacked_file) {
	dubu_pack::package package("unpacked");

	EXPECT_EQ(package.get_package_mode(), dubu_pack::package_mode::filesystem);

	dubu_pack::blob fileContent = package.get_file_locator()->read_file("test.txt");

	EXPECT_THAT(fileContent, testing::ElementsAreArray({'H','e','l','l','o',' ','W','o','r','l','d','!'}));
}

