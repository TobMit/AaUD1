#include "ui_keeper.h"
#include "console.h"
#include "../structures/_logger/logger.h"
#include <algorithm>
#include <cctype>
#include <exception>
#include <iostream>
#include <sstream>
#include <string>

namespace ui
{
// Utils:

	Color logTypeToColor(structures::LogType type)
	{
		switch (type)
		{
		case structures::LogType::Info:
			return Color::Blue;

		case structures::LogType::Warning:
			return Color::Yellow;

		case structures::LogType::Error:
			return Color::Red;

		default:
			return Color::Default;
		}
	}

	Color testLogTypeToColor(tests::TestLogType type)
	{
		switch (type)
		{
		case tests::TestLogType::Error:
			return Color::Red;

		case tests::TestLogType::Warning:
			return Color::Yellow;

		case tests::TestLogType::Pass:
			return Color::Green;

		case tests::TestLogType::Info:
			return Color::Blue;

		case tests::TestLogType::Elapsed:
			return Color::Default;

		default:
			return Color::Default;
		}
	}

	Color testResultToColor(tests::TestResult type)
	{
		switch (type)
		{
		case tests::TestResult::Passed:
			return Color::Green;

		case tests::TestResult::Failed:
			return Color::Red;

		case tests::TestResult::Partial:
			return Color::Yellow;

		case tests::TestResult::NotEvaluated:
			return Color::Default;

		default:
			return Color::Default;
		}
	}

	std::string makeTestName(TestWrap* wrap)
	{
		if (wrap->getParent())
		{
			return makeTestName(wrap->getParent()) + "." + wrap->getTest()->getName();
		}
		else
		{
			return wrap->getTest()->getName();
		}
	}

// TestWrap:

	TestWrap::TestWrap(int id, tests::Test* test) :
		TestWrap(id, test, nullptr)
	{
	}

	TestWrap::TestWrap(int id, tests::Test* test, TestWrap* parent) :
		isChecked_(false),
		id_(id),
		test_(test),
		parent_(parent)
	{
	}

	TestWrap::~TestWrap()
	{
		for (TestWrap* wrap : sons_)
		{
			delete wrap;
		}
	}

	void TestWrap::addSon(TestWrap* son)
	{
		sons_.push_back(son);
	}

	tests::Test* TestWrap::getTest() const
	{
		return test_;
	}

	const std::vector<TestWrap*>& TestWrap::getSons() const
	{
		return sons_;
	}

	int TestWrap::getId() const
	{
		return id_;
	}

	TestWrap* TestWrap::getParent() const
	{
		return parent_;
	}

	bool TestWrap::isChecked() const
	{
		return isChecked_;
	}

	bool TestWrap::isLeaf() const
	{
		return sons_.empty();
	}

	void TestWrap::setChecked(bool value)
	{
		isChecked_ = value;
	}

// UiKeeper:

	UiKeeper::UiKeeper() :
		nextTestId_(0)
	{
	}

	UiKeeper::~UiKeeper()
	{
		for (TestWrap* wrap : tests_)
		{
			delete wrap->getTest();
			delete wrap;
		}
	}

	void UiKeeper::registerTest(tests::Test* test)
	{
		tests_.push_back(this->dfsMakeWrap(test, nullptr));
	}

	void UiKeeper::printTestMenu()
	{
		ui::Console& out = ui::Console::getInstance();
		out.println("Registered tests:");
		this->forEachTestWrap([&](TestWrap* wrap, std::size_t depth)
		{
			std::string indent(depth * 2, ' ');
			if (depth == 0)
			{
				out.println("");
			}

			out.print("  [");
			out.setNextTokenWidth(nextTestId_ <= 100 ? 2 : 3);
			out.print(std::to_string(wrap->getId()));
			out.print("]");
			out.print(indent + " ");
			switch (depth)
			{
			case 0:
				out.println(wrap->getTest()->getName(), ui::Color::Yellow);
				break;

			case 1:
				if (wrap->isLeaf())
				{
					out.println(wrap->getTest()->getName(), ui::Color::Default);
				}
				else
				{
					out.println(wrap->getTest()->getName(), ui::Color::Green);
				}
				break;

			default:
				out.println(wrap->getTest()->getName());
				break;
			}
			return true;
		});
	}

	std::vector<int> UiKeeper::readTestChoice() const
	{
		Console::getInstance().println("Please select tests you want to run (e.g. \"1 7 12\") or press ENTER to run all : ");
		std::string line;
		std::getline(std::cin, line);
		std::vector<int> ids;
		std::istringstream istr(line);
		std::string idStr;
		while (istr >> idStr)
		{
			try
			{
				std::size_t countProcessed = 0;
				int id = std::stoi(idStr, &countProcessed);
				if (id < 1 || id > nextTestId_)
				{
					structures::Logger::getInstance().logWarning("Ignoring test id " + idStr);
				}
				if (countProcessed == idStr.length())
				{
					ids.push_back(id);
				}
				else
				{
					structures::Logger::getInstance().logWarning("Ignoring test id " + idStr);
				}
			}
			catch (const std::exception&)
			{
				structures::Logger::getInstance().logWarning("Ignoring test id " + idStr);
			}
		}
		return ids;
	}

	void UiKeeper::markTests(const std::vector<int>& ids)
	{
		if (ids.empty())
		{
			this->forEachTestWrap([](TestWrap* wrap, std::size_t)
			{
				wrap->setChecked(true);
				return true;
			});
			return;
		}

		this->forEachTestWrap([](TestWrap* wrap, std::size_t)
		{
			wrap->setChecked(false);
			return true;
		});

		this->forEachTestWrap([this, &ids](TestWrap* wrap, std::size_t)
		{
			bool isChecked = std::find(ids.begin(), ids.end(), wrap->getId()) != ids.end();
			if (isChecked)
			{
				this->dfsForEachTestWrap(wrap, 0, [](TestWrap* son, std::size_t)
				{
					son->setChecked(true);
					return true;
				});
				return false;
			}
			else
			{
				return true;
			}
		});
	}

	void UiKeeper::resetTests()
	{
		this->forEachTestWrap([](TestWrap* wrap, std::size_t)
		{
			wrap->getTest()->reset();
			return true;
		});
	}

	void UiKeeper::runTests()
	{
		this->forEachTestWrap([](TestWrap* wrap, std::size_t)
		{
			if (wrap->isChecked())
			{
				wrap->getTest()->run();
				return false;
			}
			else
			{
				return true;
			}
		});
	}

	void UiKeeper::showTestResults()
	{
		this->forEachTestWrap([](TestWrap* wrap, std::size_t)
		{
			Console& out = Console::getInstance();
			tests::SimpleTest* test = dynamic_cast<tests::SimpleTest*>(wrap->getTest());
			if (test != nullptr && test->getResult() != tests::TestResult::NotEvaluated)
			{
				out.println("");
				out.println(makeTestName(wrap), testResultToColor(test->getResult()));
				for (const tests::TestLog& log : test->getOutput())
				{
					out.print("  [");
					out.print(testLogTypeToString(log.getType()), testLogTypeToColor(log.getType()));
					out.print("] ");
					out.println(log.getMessage());
				}
			}
			return true;
		});
	}

	void UiKeeper::showLog() const
	{
		if (log_.empty())
		{
			return;
		}
		Console& out = Console::getInstance();
		out.println("");
		out.println("Log:");
		for (const LogMessage& msg : log_)
		{
			Color color = logTypeToColor(msg.type_);
			out.print("  [");
			out.print(structures::logTypeToString(msg.type_), color, 9);
			out.print("] ");
			out.println(msg.message_);
		}
	}

	void UiKeeper::clearLog()
	{
		log_.clear();
	}

	bool UiKeeper::readShouldContinue() const
	{
		Console::getInstance().println("");
		Console::getInstance().println("Do you want to run tests again? (Y/n)");
		std::string line;
		std::getline(std::cin, line);
		auto it = line.begin();
		auto last = line.end();
		while (it != last && std::isspace(*it))
		{
			++it;
		}
		while (it != last && std::isspace(*it))
		{
			--last;
		}
		std::string token(it, last);
		return !(token == "n" || token == "no" || token == "No" || token == "NO" || token == "nO");
	}

	void UiKeeper::logMessage(structures::LogType type, const std::string& message)
	{
		log_.push_back(LogMessage{type, message});
	}

	void UiKeeper::logDuration(size_t size, structures::DurationType duration, const std::string& message)
	{
		std::string msg = "Size " + std::to_string(size) + ", duration " + std::to_string(duration.count()) + " microseconds, " + message;
		log_.push_back(LogMessage{structures::LogType::Duration, msg});
	}

	TestWrap* UiKeeper::dfsMakeWrap(tests::Test* test, TestWrap* parent)
	{
		TestWrap* wrap = new TestWrap(++nextTestId_, test, parent);

		tests::ComplexTest* complex = dynamic_cast<tests::ComplexTest*>(test);
		if (complex != nullptr)
		{
			for (tests::Test* son : complex->getSubTests())
			{
				wrap->addSon(this->dfsMakeWrap(son, wrap));
			}
		}

		return wrap;
	}
}