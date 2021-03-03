#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include<iostream>
#include<exception>

using namespace std;

class ReadingError:public exception {
public: ReadingError(const char* message);
};
class SearchError :public exception {
public:SearchError(string message);
	   string what();
private:
	string message_;
};
class FileError :public exception {
public: FileError(const char* message);
	    
};
#endif

