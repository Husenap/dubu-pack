#include <gmock/gmock.h>

#include <dubu_pack/dubu_pack.h>

TEST(PackerTests, pack) {
    dubu_pack::Packer packer("assets");

    packer.Pack();
}
