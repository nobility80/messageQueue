#ifndef COMMONPLAT_UNITTEST_H
#define COMMONPLAT_UNITTEST_H

namespace commonplat {

class UnitTest
{
protected:
	std::string m_testName;
	int m_passed;
	int m_failed;

	std::string m_testCaseName;
	int m_errors;
	static const char *CH_UNITTEST;

protected:
	void endTestCase();

public:
	UnitTest();
	void beginTest(const std::string testCaseName);
	int endTest();
	void testCase(const std::string testCaseName);

	template <typename Type>
	void CHECK_NULL(std::shared_ptr<type> p) {
		if (p) {
			commonplat::log::D(CH_UNITTEST, "expected null sharedptr");
			m_errors++;
		}
	}

	void CHECK_NOT_NULL(std::shared_ptr<type> p) {
		if (!p) {
			commonplat::log::D(CH_UNITTEST, "expected non null sharedptr");
			m_errors++;
		}
	}

	void CHECK(const bool expected, const bool actual);
	void CHECK(const double expected, const double actual, const double epsilon);
	void CHECK(const int64_t expected, const int64_t actual);
	void CHECK(const std::string expected, const std::string actual);
	void CHECK(const std::chrono::milliseconds expected, const std::chrono::milliseconds actual);
	void CHECK_NULL(const void* const p);
	void CHECK_NOT_NULL(const void* const p);
};

}

#endif	//COMMONPLAT_UNITTEST_H
