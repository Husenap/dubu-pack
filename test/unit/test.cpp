#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

void read_test_files(dubu_pack::package& package) {
	{
		auto fileContent = package.get_file_locator()->read_file("test.txt");
		EXPECT_TRUE(fileContent.has_value());
		EXPECT_THAT(*fileContent,
		            testing::ElementsAreArray({'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'}));
	}

	{
		auto fileContent = package.get_file_locator()->read_file("this_file_does_not_exist.txt");
		EXPECT_FALSE(fileContent.has_value());
	}
}

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

	read_test_files(package);
}

TEST(dubu_pack, read_unpacked_file) {
	dubu_pack::package package("unpacked");

	EXPECT_EQ(package.get_package_mode(), dubu_pack::package_mode::filesystem);

	read_test_files(package);
}
