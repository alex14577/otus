
#include <iostream>
#include <string>
#include <gtest/gtest.h>

class TestResult
{
public:
    TestResult() = default;

    void AddRes(const std::string& res)
    {
        res_ += res;
    }

    void AddRes(const char res)
    {
        res_ += res;
    }

    std::string& GetRes()
    {
        return res_;
    }

    void Reset()
    {
        res_.clear();
    }

private:
    std::string res_;
} testResult;

std::ostream&  operator << (std::ostream &os, const std::basic_string<char> &s)
{
    testResult.AddRes(s);
    return os;
}
std::ostream&  operator << (std::ostream &os, const char s)
{
    testResult.AddRes(s);
    return os;
}

std::ostream&  operator << (std::ostream &os, const unsigned int s)
{
    std::string str{std::to_string( s )};
    testResult.AddRes(str);
    return os;
}

class PrintIpTest : public ::testing::Test
{
protected:
	void SetUp()
	{
        testResult.Reset();
	}
	void TearDown()
	{

	}
};

#include <print_ip/print_ip.h>

TEST_F(PrintIpTest, TestipInt8)
{
    int8_t ipInt8 = -1;
    PrintIp(ipInt8);

    EXPECT_EQ(testResult.GetRes(), std::string("255"));    
}

TEST_F(PrintIpTest, TestipInt16)
{
    int16_t ipInt16 = 0;
    PrintIp(ipInt16);

    EXPECT_EQ(testResult.GetRes(), std::string("0.0"));    
}

TEST_F(PrintIpTest, TestipInt32)
{
    int32_t ipInt32 = 2130706433;
    PrintIp(ipInt32);

    EXPECT_EQ(testResult.GetRes(), std::string("127.0.0.1"));    
}

TEST_F(PrintIpTest, TestipInt64)
{
    int64_t ipInt64 = 8875824491850138409;
    PrintIp(ipInt64);

    EXPECT_EQ(testResult.GetRes(), std::string("123.45.67.89.101.112.131.41"));    
}

TEST_F(PrintIpTest, TestipString)
{
    constexpr auto ipVal = "Hello World";
    std::string ipString {ipVal};
    PrintIp(ipString);

    EXPECT_EQ(testResult.GetRes(), std::string( ipVal ));    
}

TEST_F(PrintIpTest, TestipIntVec)
{
    std::vector<int> ipVec = {400, 300, 200, 100};
    PrintIp(ipVec);

    EXPECT_EQ(testResult.GetRes(), std::string("400.300.200.100"));    
}

TEST_F(PrintIpTest, TestipInt)
{
    std::list<short> ipList = {400, 300, 200, 100};
    PrintIp(ipList);

    EXPECT_EQ(testResult.GetRes(), std::string("400.300.200.100"));    
}