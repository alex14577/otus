#include <print_ip/print_ip.h>

#include <iostream>
#include <string>
#include <gtest/gtest.h>

class PrintIpTest : public ::testing::Test
{
protected:
    void SetUp() {
        prev = std::cout.rdbuf(buffer.rdbuf());
    }
    void TearDown() {
        std::cout.rdbuf(prev);
        std::stringstream{}.swap(buffer); // reset buffer state with flags and etc.
    }
    std::string output() const {
        return buffer.str();
    }
private:
    std::streambuf* prev{};
    std::stringstream buffer;
};


TEST_F(PrintIpTest, TestipInt8)
{
    int8_t ipInt8 = -1;
    PrintIp(ipInt8);

    EXPECT_EQ(output(), "255");    
}

TEST_F(PrintIpTest, TestipInt16)
{
    int16_t ipInt16 = 0;
    PrintIp(ipInt16);

    EXPECT_EQ(output(), "0.0");    
}

TEST_F(PrintIpTest, TestipInt32)
{
    int32_t ipInt32 = 2130706433;
    PrintIp(ipInt32);

    EXPECT_EQ(output(), "127.0.0.1");    
}

TEST_F(PrintIpTest, TestipInt64)
{
    int64_t ipInt64 = 8875824491850138409;
    PrintIp(ipInt64);

    EXPECT_EQ(output(), "123.45.67.89.101.112.131.41");
}

TEST_F(PrintIpTest, TestipString)
{
    constexpr auto ipVal = "Hello World";
    std::string ipString {ipVal};
    PrintIp(ipString);

    EXPECT_EQ(output(), ipVal);  
}

TEST_F(PrintIpTest, TestipIntVec)
{
    std::vector<int> ipVec = {400, 300, 200, 100};
    PrintIp(ipVec);

    EXPECT_EQ(output(), "400.300.200.100");
}

TEST_F(PrintIpTest, TestipInt)
{
    std::list<short> ipList = {400, 300, 200, 100};
    PrintIp(ipList);

    EXPECT_EQ(output(), "400.300.200.100");
}