#include "Exceptions.h"

ReadingError::ReadingError(const char* message):exception(message)
{
}

SearchError::SearchError(string message):message_(message)
{
}

string SearchError::what()
{
	return message_;
}

FileError::FileError(const char* message):exception(message)
{
}
