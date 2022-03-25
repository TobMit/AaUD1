#pragma once
#include "structures/_logger/logger.h"
#include <fstream>
#include "structures/types.h"

namespace gui
{
	class FileLogConsummer :
		public structures::ILogConsumer
	{
	public:
		// Inherited via ILogConsumer
		FileLogConsummer(const std::string& filePath);
		virtual void logMessage(structures::LogType type, const std::string& message) override;
		virtual void logDuration(size_t size, structures::DurationType duration, const std::string& message) override;
		
	private:
		std::ofstream fileStream_;

		// Inherited via ILogConsumer
	};
}