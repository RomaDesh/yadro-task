#include "../globals.h"
#include "../time.h"
#include "../desk.h"
#include "../utils.h"
#include "../events.h"

#include <gtest/gtest.h>

// Фикстура для тестирования Desk::clientLeft
class DeskClientLeftTest : public ::testing::Test {
protected:

    void SetUp() override {
        _ossRes.str("");
        _ossRes.clear();
        _clients.clear();
        while (!_queue.empty())
            _queue.pop();
        _n = 1;
        _price = 10;
        _occupiedDesks = 1;
    }

    

    void TearDown() override {
        _ossRes.str("");
        _ossRes.clear();
        _clients.clear();
        while (!_queue.empty())
            _queue.pop();
        _n = 1;
        _price = 10;
        _occupiedDesks = 0;
    }
};


// Тестирование custom_stoi
TEST(StoiTest, PositiveNumber) {
    EXPECT_EQ(custom_stoi("4"), 4);
}

TEST(StoiTest, NegativeNumber) {
    EXPECT_EQ(custom_stoi("-4"), -4);
}

TEST(StoiTest, PositiveNumberWithSpace) {
    EXPECT_THROW({
        custom_stoi("4 ");
        }, std::runtime_error);
}

TEST(StoiTest, FloatNumber) {
    EXPECT_THROW({ 
        custom_stoi("4.2"); 
        }, std::runtime_error);
}

TEST(StoiTest, EmptyString) {
    EXPECT_THROW({
        custom_stoi("");
        }, std::invalid_argument);
}

// Тестирование goodName
TEST(GoodNameTest, GoodAlphabet) {
    EXPECT_EQ(goodName("client123-_"), true);
    EXPECT_EQ(goodName("---___"), true);
    EXPECT_EQ(goodName("234"), true);
    EXPECT_EQ(goodName("word"), true);
}

TEST(GoodNameTest, BadAlphabet) {
    EXPECT_EQ(goodName("Client"), false);
    EXPECT_EQ(goodName("client 1"), false);
    EXPECT_EQ(goodName("client$2"), false);
    EXPECT_EQ(goodName(" client"), false);
}

TEST(GoodNameTest, EmptyString) {
    EXPECT_EQ(goodName(""), false);
}

// Тестирование конструктора Time для инициализации через строку
TEST(TimeTest, GoodTime) {
    EXPECT_EQ(Time("23:59"), Time(23, 59));
    EXPECT_EQ(Time("00:00"), Time(0, 0));
}

TEST(TimeTest, BadTime) {
    EXPECT_THROW({
        Time("9:22");
        }, std::runtime_error);
    EXPECT_THROW({
        Time("24:00");
        }, std::runtime_error);
    EXPECT_THROW({
        Time("08:60");
        }, std::runtime_error);
    EXPECT_THROW({
        Time("-9:22");
        }, std::runtime_error);
    EXPECT_THROW({
        Time("09-22");
        }, std::runtime_error);
}

// Тестирование Desk::placeClient
TEST(DeskPlaceClientTest, DeskWithClient) {
    Desk testDesk(1, true, "test_client", Time(0, 0), Time(0, 0), 0);
    testDesk.placeClient(Time(12, 0), "test_client2");
    EXPECT_EQ(_ossRes.str(), "12:00 13 PlaceIsBusy\n");
    _ossRes.str("");
    _ossRes.clear();
}

TEST(DeskPlaceClientTest, DeskWithoutClient) {
    Desk testDesk(1);
    testDesk.placeClient(Time(12, 0), "test_client");
    EXPECT_EQ(testDesk.getState(), true);
    EXPECT_EQ(testDesk.getClientName(), "test_client");
    EXPECT_EQ(testDesk.getCurrentClientTime(), Time(12, 0));
    EXPECT_EQ(testDesk.getOccupiedTime(), Time(0, 0));
    EXPECT_EQ(testDesk.getSum(), 0);
    EXPECT_EQ(_occupiedDesks, 1);
    EXPECT_EQ(_clients["test_client"], 1);
    EXPECT_EQ(_ossRes.str(), "");
    _occupiedDesks = 0;
    _clients.clear();
    _ossRes.str("");
    _ossRes.clear();
}

// Тестирование Desk::clientLeft
TEST_F(DeskClientLeftTest, ClientLeftByHimselfEmptyQueue) {
    Desk testDesk(1, true, "test_client", Time(9, 0), Time(0, 0), 0);
    _clients["test_client"] = 1;
    testDesk.clientLeft(Time(12, 0), false);
    EXPECT_EQ(testDesk.getState(), false);
    EXPECT_EQ(testDesk.getClientName(), "");
    EXPECT_EQ(testDesk.getCurrentClientTime(), Time(9, 0));
    EXPECT_EQ(testDesk.getOccupiedTime(), Time(3, 0));
    EXPECT_EQ(testDesk.getSum(), 30);
    EXPECT_EQ(_occupiedDesks, 0);
    EXPECT_EQ(_clients["test_client"], 0);
    EXPECT_EQ(_ossRes.str(), "");
}

TEST_F(DeskClientLeftTest, ClientLeftByHimselfFullQueue) {
    Desk testDesk(1, true, "test_client", Time(9, 0), Time(0, 0), 0);
    _clients["test_client"] = 1;
    _clients["test_client2"] = -2;
    _queue.push("test_client2");
    testDesk.clientLeft(Time(12, 0), false);
    EXPECT_EQ(testDesk.getState(), true);
    EXPECT_EQ(testDesk.getClientName(), "test_client2");
    EXPECT_EQ(testDesk.getCurrentClientTime(), Time(12, 0));
    EXPECT_EQ(testDesk.getOccupiedTime(), Time(3, 0));
    EXPECT_EQ(testDesk.getSum(), 30);
    EXPECT_EQ(_occupiedDesks, 1);
    EXPECT_EQ(_clients["test_client"], 0);
    EXPECT_EQ(_clients["test_client2"], 1);
    EXPECT_EQ(_ossRes.str(), "12:00 12 test_client2 1\n");
}

TEST_F(DeskClientLeftTest, ClientLeftAutomaticallyEmptyQueue) {
    Desk testDesk(1, true, "test_client", Time(9, 0), Time(0, 0), 0);
    _clients["test_client"] = 1;
    testDesk.clientLeft(Time(12, 0), true);
    EXPECT_EQ(testDesk.getState(), false);
    EXPECT_EQ(testDesk.getClientName(), "");
    EXPECT_EQ(testDesk.getCurrentClientTime(), Time(9, 0));
    EXPECT_EQ(testDesk.getOccupiedTime(), Time(3, 0));
    EXPECT_EQ(testDesk.getSum(), 30);
    EXPECT_EQ(_occupiedDesks, 0);
    EXPECT_EQ(_clients["test_client"], 0);
    EXPECT_EQ(_ossRes.str(), "12:00 11 test_client\n");
}

TEST_F(DeskClientLeftTest, ClientLeftAutomaticallyFullQueue) {
    Desk testDesk(1, true, "test_client", Time(9, 0), Time(0, 0), 0);
    _clients["test_client"] = 1;
    _clients["test_client2"] = -2;
    _queue.push("test_client2");
    testDesk.clientLeft(Time(12, 0), true);
    EXPECT_EQ(testDesk.getState(), true);
    EXPECT_EQ(testDesk.getClientName(), "test_client2");
    EXPECT_EQ(testDesk.getCurrentClientTime(), Time(12, 0));
    EXPECT_EQ(testDesk.getOccupiedTime(), Time(3, 0));
    EXPECT_EQ(testDesk.getSum(), 30);
    EXPECT_EQ(_occupiedDesks, 1);
    EXPECT_EQ(_clients["test_client"], 0);
    EXPECT_EQ(_clients["test_client2"], 1);
    EXPECT_EQ(_ossRes.str(), "12:00 11 test_client\n"
        "12:00 12 test_client2 1\n");
}