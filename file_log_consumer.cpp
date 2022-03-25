#include "file_log_consumer.h"

gui::FileLogConsummer::FileLogConsummer(const std::string& filePath) :
	fileStream_(filePath)
{
	if (!fileStream_.is_open())
	{
		throw std::logic_error("Can not open file! Expection from FileLogConsummer::FileLogConsummer()");
	}
}

void gui::FileLogConsummer::logMessage(structures::LogType type, const std::string& message)
{
	fileStream_ << structures::logTypeToString(type) << "!" << message << std::endl;
}

void gui::FileLogConsummer::logDuration(size_t size, std::chrono::milliseconds duration, const std::string& message)
{
	fileStream_ << size << "!" << duration.count() << "!" << message << std::endl;
}
