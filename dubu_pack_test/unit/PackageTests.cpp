#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

void read_test_file(dubu::pack::Package& package) {
	for (int i = 0; i < 100; ++i) {
		{
			auto fileContent = package.GetFileLocator()->ReadFile("test.txt");
			ASSERT_TRUE(fileContent.has_value());
			EXPECT_THAT(*fileContent,
			            testing::ElementsAreArray({'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd', '!'}));
		}

		{
			auto fileContent = package.GetFileLocator()->ReadFile("icon.png");
			ASSERT_TRUE(fileContent.has_value());
		}

		{
			auto fileContent = package.GetFileLocator()->ReadFile("this_file_does_not_exist.txt");
			ASSERT_FALSE(fileContent.has_value());
		}
	}
}
TEST(PackageTests, package_name) {
	dubu::pack::Package Package("assets");

	EXPECT_STREQ("assets", Package.GetPackageName().data());
	EXPECT_STRNE("random name", Package.GetPackageName().data());
}

TEST(PackageTests, packed) {
	dubu::pack::Package Package("assets");

	EXPECT_EQ(Package.GetPackageMode(), dubu::pack::PackageMode::Package);
}

TEST(PackageTests, unpacked) {
	dubu::pack::Package Package("unpacked");

	EXPECT_EQ(Package.GetPackageMode(), dubu::pack::PackageMode::Filesystem);
}

TEST(PackageTests, read_packed_test_file) {
	dubu::pack::Package Package("assets");

	EXPECT_EQ(Package.GetPackageMode(), dubu::pack::PackageMode::Package);

	read_test_file(Package);
}

TEST(PackageTests, read_packed_compressed_test_file) {
	dubu::pack::Package Package("assets_with_compression");

	EXPECT_EQ(Package.GetPackageMode(), dubu::pack::PackageMode::Package);

	read_test_file(Package);
}

TEST(PackageTests, read_unpacked_test_file) {
	dubu::pack::Package Package("unpacked");

	EXPECT_EQ(Package.GetPackageMode(), dubu::pack::PackageMode::Filesystem);

	read_test_file(Package);
}
