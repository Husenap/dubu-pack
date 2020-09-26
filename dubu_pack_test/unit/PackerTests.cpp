#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

TEST(PackerTests, pack) {
	dubu::pack::Packer packer("assets");

	packer.Pack();

	dubu::pack::Package package("assets");

	EXPECT_EQ(package.GetPackageMode(), dubu::pack::PackageMode::Package);
}
