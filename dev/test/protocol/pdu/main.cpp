#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/ui/text/TestRunner.h>
#include <stdexcept>

int main(int argc, char* argv[])
{
	std::string testPath = (argc > 1) ? std::string(argv[1]) : std::string("");

	CPPUNIT_NS::TestResult controller;

	CPPUNIT_NS::TestResultCollector result;
	controller.addListener(&result);

	CPPUNIT_NS::BriefTestProgressListener progress;
	controller.addListener(&progress);

	CppUnit::TextUi::TestRunner runner;
	CppUnit::TestFactoryRegistry& registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest(registry.makeTest());

	try
	{
		CPPUNIT_NS::stdCOut() << "Running " << testPath;
		runner.run(controller, testPath);
		CPPUNIT_NS::stdCOut() << "\n";

		CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
		outputter.write();
	}
	catch( std::invalid_argument& e)
	{
		CPPUNIT_NS::stdCOut() << "\n" << "ERROR: " << e.what() << "\n";	
	}

	return result.wasSuccessful() ? 0 : 1;
}
