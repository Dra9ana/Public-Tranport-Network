#ifndef PATHS_H
#define PATHS_H

#include<iostream>
#include<string>
#include<map>

#include"Station.h"
#include"Line.h"

using namespace std;

class FindingPaths {

public: 
	   virtual void findPath(Station* first, Station* last,  map<string, Line*>& lines,  map<int, Station*>& stations) = 0;
protected:	 
	    static void printPath(int first_code,int last_code,string output);
};
class minimumStationsPath :public FindingPaths {
public: void findPath(Station* first,Station* last,map<string,Line*>&lines,  map<int,Station*>&stations)override;
private:
	int doBFS(Station* first, Station* last, map<int, pair<int, string>>& pred,  map<string, Line*>& lines, map<int, Station*>& stations);
};
class MinimumLinesPath : public FindingPaths {
public: void findPath(Station* first, Station* last,  map<string, Line*>& lines,  map<int, Station*>& stations)override;
private:
	string doBFS(Station* first, Station* last, map<string, pair<string, int>>& pred,  map<string, Line*>& lines, map<int, Station*>& stations);
};
#endif
