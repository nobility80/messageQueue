#include <UnitTest/unittest.h>
#include <Log/log.h>

#include <cmath>

namespace commonplat {

const char* UnitTest::CH_UNITTEST = "UnitTest";

UnitTest::UnitTest() : m_passed(0), m_failed(0), m_errors(0)
{
}

void UnitTest::beginTest(const std::string testCaseName) {
	m_testName = testCaseName;
	m_passed = 0;
	m_failed = 0;
}

int UnitTest::endTest() {
	endTestCase();
	int retval = 0;
	const int total = m_passed + m_failed;
	if (m_failed == 0) {
		commonplat::log::D(CH_UNITTEST, "
