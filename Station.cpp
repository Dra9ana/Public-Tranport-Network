#include"Exceptions.h"
#include "Station.h"

#include<iostream>
#include<string>
#include<queue>

using namespace std;

int Station::getCode()
{
	return code_;
}

string Station::getName()
{
	return name_;
}

Station* Station::getNeighbour(string line_label)
{
	if (neighbours_.find(line_label) != neighbours_.end())
		return neighbours_[line_label];
	else
		throw(SearchError("Neighbour with label "+line_label+" not found"));
}

//Marks all neighbours in BFS and checks if last stations is its neighbour
bool Station::BFSStationSearch(int last_code, queue<int>&visit_children, set <int>& visited_stations, map<int,pair<int,string>>&pred)
{  
	for (auto i : neighbours_) {
		//go through neighbours
		if (visited_stations.find(i.second->getCode())==visited_stations.end()) {//if neighbour is not visited
			visited_stations.insert(i.second->getCode());//visit neighbour
			pred.insert(pair<int,pair<int,string>>(i.second->getCode(),pair <int,string>(code_, i.first)));//save connection between them
			visit_children.push(i.second->getCode());//visit its children later
		}

		if (i.second->getCode() == last_code)return true;//checking if this node is last
	}
	
	return false;
}

//used in lines BFS
void Station::markLines(string label, set<int>& visited_stations, set<string>& visited_lines, queue<pair<string,int>>& visit_children, map<string, pair<string, int>>& pred)
{
	visited_stations.insert(code_);
	for (auto i : neighbours_) {
		if (visited_lines.find(i.first) == visited_lines.end()) {//if i.first isn't visited
			visited_lines.insert(i.first);//mark it as visited
			visit_children.push(pair<string,int>(i.first,code_));//visit it later
			pred.insert(pair<string, pair<string, int>>(i.first, pair<string, int>(label, code_)));//map predecessor
		}
	}
}

//goes through line with label - label and returns output
string Station::writePath( Station* beg,Station* end, string label)
{
	try {
		string temp_output = "";

		for (auto temp_station = beg; temp_station != end; temp_station = temp_station->getNeighbour(label)) {
			temp_output += to_string(temp_station->getCode()) + " ";
		}

		temp_output += to_string(end->getCode());

		return temp_output;

	}
	catch (ReadingError& e) {//if next neighbour with line label does not exists
		cout << "Line " <<label<<"does not connect stations : "<<beg->getCode()<<" and "<<end->getCode() << endl;
	}
}

//writes all lines which go through this station	
string Station::outputLines()
{
		string output = "";

		for (auto neighbour = neighbours_.begin(); neighbour != neighbours_.end(); ++neighbour) {
			output += neighbour->first;
			output += " ";
		}

		output.pop_back();

		return output;

}

string Station::outputStationCodeAndName()
{
	return to_string(code_ )+ " " + name_ + "\n";
}

//saves all line pairs that goes through this station
void Station::writeIntersection(map<pair<string,string>, int>&intersections,map<string,int>&max)
{
	for (auto i = neighbours_.begin(); i != neighbours_.end(); i++) {//go through pairs of neighbour stations
		for (auto j=neighbours_.begin(); j != neighbours_.end(); j++)
		{
			if (i != j) {
				if (intersections.count(pair<string, string>(i->first, j->first)) == 0) {//if first intersection 
					intersections.insert(pair<pair<string, string>, int>(pair<string, string>(i->first, j->first), 1));
					max[i->first] = 1;
				}
				else {
					int a = ++(intersections[pair<string, string>(i->first, j->first)]);//increase number of intersections
					if (a > max[i->first])max[i->first] = a;//if bigger than max set it to max

				}
			}
		}
	}
}

Station::Station(const string& text, int& pos) {

	code_=readCode(text,pos);
	if (pos < text.length() && text[pos] != ' ')throw(ReadingError("Space not found"));
	else pos++;
	readName(text,pos);
}

int Station::readCode(const string& text, int& pos)
{
	int code=0;

	while( pos < text.length() && isdigit(text[pos])) {
		   code = code * 10 + (text[pos++]-'0');
	}

	return code;
}

void Station::readName(const string& text, int& pos)
{
	while (pos < text.length())name_ += text[pos++];
}

void Station::addNeighbour(string label,Station* neighbour)
{
	neighbours_.insert(pair<string, Station*>(label,neighbour));
}
