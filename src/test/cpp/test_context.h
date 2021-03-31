/*
 *    Copyright (c). 2020. Loginov Ilya Vladislavovich. All rights reserved.
 *    You must get permission for all action with this code or part of code from email dantes2104@gmail.com.
 */

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
                std::cout << "ERROR: Can not execute function with name '" << currentTag << "' and with id = " << i << "\n\t" << e.what() << '\n';
            }
        }

        return 0;
    }
};

#define enableTests() TestContext __testContext;
#define startTests() __testContext.main();

#define createTest(name) void name(TestContext* _this, TestContext::setTagFunc _setTag) { callSetTag()
#define endTest }
#define callSetTag() (_this->*_setTag)(__func__);
#define sendMessage std::cout << '\t' <<

#define enableTest(name) __testContext.addTest((name));
