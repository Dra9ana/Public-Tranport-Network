#ifndef STATION_H
#define STATION_H

#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<string.h>
#include<vector>


using namespace std;

class Station {
public:
	friend class PublicTransportNetwork;

	Station(const Station&) = delete;
	Station& operator = (const Station&) = delete;

	int getCode();
	string getName();
	Station* getNeighbour(string line_label);

	bool BFSStationSearch(int last_code, queue<int>&visit_children, set <int>& visited_stations, map<int, pair<int, string>>& pred);
	void markLines(string label, set<int>&visited_stations, set<string>&visited_lines,queue<pair<string,int>>&visit_children, map<string, pair<string, int>>& pred);
    static string writePath(Station* beg,Station* end,string line);

	string outputLines();
	string outputStationCodeAndName();

	void writeIntersection(map<pair<string,string>,int>&intersections,map<string,int>& max);
	
	static int readCode(const string& text,int& pos);
private:
	Station(const string& text,int& pos);
	
	void readName(const string& text, int& pos);
	void addNeighbour(string label,Station* neighbour);
	
	int code_;
	string name_;
	map<string,Station*>neighbours_;
};
#endif
