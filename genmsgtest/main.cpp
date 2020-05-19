#include <iostream>
#include <../generate_messages/simulation.h>
#include "gtest/gtest.h"

using namespace std;

TEST(Simulation, DecimalToBinary)
{
    Simulation* s1 = new Simulation();

    string s = "00001001";
    ASSERT_TRUE(s.compare(s1->dec_to_bin(9))==0);

     s = "01000101";
     ASSERT_TRUE(s.compare(s1->dec_to_bin(69))==0);


     s = "10000000";
     ASSERT_TRUE(s.compare(s1->dec_to_bin(128))==0);


     s = "00100101";
     ASSERT_TRUE(s.compare(s1->dec_to_bin(37))==0);


     s = "00000011";
     ASSERT_TRUE(s.compare(s1->dec_to_bin(3))==0);

}

TEST(Simulation, BinaryToDecimal)
{
    Simulation* s1 = new Simulation();

    ASSERT_TRUE(s1->bin_to_dec("11") == 3);

    ASSERT_TRUE(s1->bin_to_dec("100101")==37);

    ASSERT_TRUE(s1->bin_to_dec("10000000")==128);

    ASSERT_TRUE(s1->bin_to_dec("10111001011")==1483);

    ASSERT_TRUE(s1->bin_to_dec("1001")==9);

}

TEST(Simulation, FlipBinary)
{
    Simulation* s1 = new Simulation();

    string s = "11";
    ASSERT_TRUE(s.compare(s1->flip_bin("11"))==0);

    s = "11001";
    ASSERT_TRUE(s.compare(s1->flip_bin("10011"))==0);

    s = "0011";
    ASSERT_TRUE(s.compare(s1->flip_bin("1100"))==0);

    s = "11010011101";
    ASSERT_TRUE(s.compare(s1->flip_bin("10111001011"))==0);

    s = "00000001";
    ASSERT_TRUE(s.compare(s1->flip_bin("10000000"))==0);

}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
