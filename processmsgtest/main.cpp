#include <iostream>
#include <../process_messages/event.h>
#include <../process_messages/parse.h>
#include <../process_messages/trigger.h>
#include "gtest/gtest.h"

using namespace std;

TEST(FormatTimeTest, Set_Time)
{
    Event* e1 = new Event();
    e1->set_time(360000);
    string s = "100.00.00000";
    ASSERT_TRUE((s.compare(e1->format_time())==0));


    e1->set_time(450123);
    s = "125.02.03000";
    ASSERT_TRUE((s.compare(e1->format_time())==0));

    e1->set_time(1234);
    s = "00.20.34000";
    ASSERT_TRUE((s.compare(e1->format_time())==0));

    e1->set_time(12345);
    s = "03.25.45000";
    ASSERT_TRUE((s.compare(e1->format_time())==0));

    e1->set_time(39046);
    s = "10.50.46000";
    ASSERT_TRUE((s.compare(e1->format_time())==0));

}

TEST(TriggerCompareTest, Compare)
{
    Trigger* t1 = new Trigger();
    Trigger* t2 = new Trigger();
    t1->set_time(500);
    t2->set_time(6543);
    ASSERT_TRUE(t1<t2);


    t1->set_time(200);
    t2->set_time(500);
    ASSERT_FALSE(t1>t2);

    t1->set_time(3);
    t2->set_time(300);
    ASSERT_TRUE(t1<t2);

    t1->set_time(3004);
    t2->set_time(5000);
    ASSERT_FALSE(t1>t2);

    t1->set_time(24);
    t2->set_time(24);
    ASSERT_FALSE(t1==t2);
}

int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

