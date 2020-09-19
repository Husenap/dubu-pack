#include <gtest/gtest.h>

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
