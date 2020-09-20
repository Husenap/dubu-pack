#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

void read_test_file(dubu_pack::Package& package) {
	{
		auto fileContent = package.GetFileLocator()->ReadFile("test.txt");
		ASSERT_TRUE(fileContent.has_value());
		EXPECT_THAT(*fileContent,
		            testing::ElementsAreArray({'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'}));
	}

	{
		auto fileContent = package.GetFileLocator()->ReadFile("this_file_does_not_exist.txt");
		ASSERT_FALSE(fileContent.has_value());
	}
}

TEST(PackageTests, package_name) {
	dubu_pack::Package Package("assets");

	EXPECT_STREQ("assets", Package.GetPackageName().data());
	EXPECT_STRNE("random name", Package.GetPackageName().data());
}

TEST(PackageTests, packed) {
	dubu_pack::Package Package("packed");

	EXPECT_EQ(Package.GetPackageMode(), dubu_pack::PackageMode::Package);
}

TEST(PackageTests, unpacked) {
	dubu_pack::Package Package("unpacked");

	EXPECT_EQ(Package.GetPackageMode(), dubu_pack::PackageMode::Filesystem);
}

TEST(PackageTests, read_packed_test_file) {
	dubu_pack::Package Package("packed");

	EXPECT_EQ(Package.GetPackageMode(), dubu_pack::PackageMode::Package);

	read_test_file(Package);
}

TEST(PackageTests, read_unpacked_test_file) {
	dubu_pack::Package Package("unpacked");

	EXPECT_EQ(Package.GetPackageMode(), dubu_pack::PackageMode::Filesystem);

	read_test_file(Package);
}
