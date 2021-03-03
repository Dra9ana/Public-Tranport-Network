#ifndef LINE_H
#define LINE_H

#include"Station.h"

#include<iostream>
#include<string>
#include<queue>
#include<vector>


using namespace std;
class Line{

friend class PublicTransportNetwork;

public:	string getLabel();
	    Station* getFirstStation();
	    Station* getLastStation();
		string outputStations();
		bool BFSLineSearch(int last_code, Station* first_station,set<int>& visited_stations, set<string>& visited_lines, queue<pair<string,int>>& visit_children, map<string, pair<string, int>>& pred);
private:
	    Line(const string& text, int& pos);
	    void setFirstStation(Station* station);
	    void setLastStation(Station* station);
	    string label_;
	    Station *first_station_, *last_station_;


};
#endif
