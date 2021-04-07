#include <dubu_pack/dubu_pack.h>
#include <gmock/gmock.h>

TEST(PackerTests, pack_without_compression) {
	dubu::pack::Packer packer("assets");

	packer.Pack();

	dubu::pack::Package package("assets");

	EXPECT_EQ(package.GetPackageMode(), dubu::pack::PackageMode::Package);
}

TEST(PackerTests, pack_with_compression) {
	dubu::pack::Packer packer("assets_with_compression", true);

	packer.Pack();

	dubu::pack::Package package("assets_with_compression");

	EXPECT_EQ(package.GetPackageMode(), dubu::pack::PackageMode::Package);
}
