#pragma once
#include "structures/_logger/logger.h"
#include <fstream>

namespace gui
{
	class FileLogConsummer :
		public structures::ILogConsumer
	{
	public:
		// Inherited via ILogConsumer
		FileLogConsummer(const std::string& filePath);
		virtual void logMessage(structures::LogType type, const std::string& message) override;
		virtual void logDuration(size_t size, std::chrono::milliseconds duration, const std::string& message) override;
	private:
		std::ofstream fileStream_;
	};
}