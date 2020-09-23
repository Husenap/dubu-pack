#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

TEST(PackerTests, pack) {
    dubu_pack::Packer packer("assets");

    packer.Pack();

    dubu_pack::Package package("assets");
    
    EXPECT_EQ(package.GetPackageMode(), dubu_pack::PackageMode::Package);
}
