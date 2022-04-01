#include "file_log_consumer.h"

gui::FileLogConsummer::FileLogConsummer(const std::string& filePath) :
	fileStream_(filePath)
{
	if (!fileStream_.is_open())
	{
		throw std::logic_error("Can not open file! Expection from FileLogConsummer::FileLogConsummer()");
	}
	fileStream_ << "sep=," << std::endl; // excel pre správen otváranie potrebuje toto na zaèiatku csv súboru.
}

void gui::FileLogConsummer::logMessage(structures::LogType type, const std::string& message)
{
	fileStream_ << structures::logTypeToString(type) << "!," << message << std::endl;
}

void gui::FileLogConsummer::logDuration(size_t size, structures::DurationType duration, const std::string& message)
{
	fileStream_ << size << "!,"  << message << "," << duration.count() << std::endl;
}

