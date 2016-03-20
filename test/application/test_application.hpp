/**
 * \file
 * \brief Execute basic test for application library
 *
 * \author Uilian Ries <uilianries@gmail.com>
 */
#ifndef SMARTAQUARIUM_TEST_APP_HPP_
#define SMARTAQUARIUM_TEST_APP_HPP_

#include <memory>

#include <cppunit/TestCase.h>
#include <cppunit/extensions/HelperMacros.h>

#include <Poco/Process.h>
#include <Poco/AutoPtr.h>

/**
 * \brief Test case for application library
 */
class test_application : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(test_application);
    CPPUNIT_TEST(start_application);
    CPPUNIT_TEST_SUITE_END();

public:
    /**
     * \brief Spawn application process
     */
    void setUp() override;

    /**
     * \brief Kill application process
     */
    void tearDown() override;

protected:
    /**
     * \brief Do nothing
     */
    void start_application();

private:
    std::unique_ptr<Poco::ProcessHandle> process_h_; /**< Process pid */
};

#endif // SMARTAQUARIUM_TEST_APP_HPP_