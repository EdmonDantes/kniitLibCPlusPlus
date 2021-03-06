//
// Created by masa_ on 07.03.2021.
//
#include <vector>
#include <iostream>

class TestContext {
 public:
    typedef void (TestContext::*setTagFunc)(std::string);
    typedef void (*testFunc)(TestContext*, setTagFunc);
 private:
    std::vector<testFunc> tests;
    std::string currentTag;
 public:

    void addTest(testFunc func) {
        tests.push_back(func);
    }

    void setTag(std::string tag) {
        this->currentTag = tag;
    }

    int main() {

        for (int i = 0; i < tests.size(); ++i) {

            std::cout << "Start test with id = " << i << '\n';
            try {
                tests[i](this, &TestContext::setTag);
            } catch (std::exception& e) {
                std::cerr << "Can not execute function with name '" << currentTag << "' and with id = " << i << "\n\t" << e.what() << '\n';
            }
        }

        return 0;
    }
};

#define enableTests() TestContext __testContext;
#define startTests() __testContext.main();

#define createTest(name) void name(TestContext* _this, TestContext::setTagFunc _setTag)
#define callSetTag() (_this->*_setTag)(__func__);
#define enableTest(name) __testContext.addTest((name));
