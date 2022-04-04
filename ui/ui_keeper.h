#pragma once

#include "../tests/test.h"
#include <vector>
#include <string>

namespace ui
{
	class TestWrap
	{
	public:
		TestWrap(int id, tests::Test* test);
		TestWrap(int id, tests::Test* test, TestWrap* parent);
		~TestWrap();

		void addSon(TestWrap* son);
		tests::Test* getTest() const;
		const std::vector<TestWrap*>& getSons() const;
		int getId() const;
		bool isChecked() const;
		bool isLeaf() const;
		void setChecked(bool value);
		TestWrap* getParent() const;

	private:
		bool isChecked_;
		int id_;
		tests::Test* test_;
		TestWrap* parent_;
		std::vector<TestWrap*> sons_;
	};

	struct LogMessage
	{
		structures::LogType type_;
		std::string message_;
	};

	class UiKeeper : public structures::ILogConsumer
	{
	public:
		UiKeeper();
		~UiKeeper();

		void registerTest(tests::Test* test);
		void printTestMenu();
		std::vector<int> readTestChoice() const;
		void markTests(const std::vector<int>& ids);
		void resetTests();
		void runTests();
		void showTestResults();
		void showLog() const;
		void clearLog();
		bool readShouldContinue() const;

		void logMessage(structures::LogType type, const std::string& message) override;
		void logDuration(size_t size, structures::DurationType duration, const std::string& message) override;

	private:
		TestWrap* dfsMakeWrap(tests::Test* test, TestWrap* parent);

		template<class F>
		void forEachTestWrap(F f);

		template<class F>
		void dfsForEachTestWrap(TestWrap* wrap, std::size_t depth, F f);

	private:
		int nextTestId_;
		std::vector<TestWrap*> tests_;
		std::vector<LogMessage> log_;
	};

	template<class F>
	inline void UiKeeper::forEachTestWrap(F f)
	{
		for (TestWrap* test : tests_)
		{
			this->dfsForEachTestWrap(test, 0, f);
		}
	}

	template<class F>
	void UiKeeper::dfsForEachTestWrap(TestWrap* wrap, std::size_t depth, F f)
	{
		if (f(wrap, depth))
		{
			for (TestWrap* son : wrap->getSons())
			{
				this->dfsForEachTestWrap(son, depth + 1, f);
			}
		}
	}
}