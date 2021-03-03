#include"Exceptions.h"
#include "FindingPaths.h"

#include<fstream>
#include<set>

void minimumStationsPath::findPath(Station* first, Station* last,  map<string, Line*>& lines, map<int, Station*>& stations)
{
    map<int, pair<int, string>> pred;

    doBFS(first, last, pred, lines, stations);

    int code = last->getCode();
    string output;
    string last_line;

    while (code != -1) {

        if (last_line!=""&&last->getCode() != code && pred[code].second != last_line)
        {
            output = pred[code].second + "->" + last_line + "\n" + to_string(code) + " " + output;
            if (code != first->getCode())output = to_string(code) + "\n" + output;
        }
        else output = to_string(code) + " " + output;

        last_line = pred[code].second;
        code = pred[code].first;

    } 

    FindingPaths::printPath(first->getCode(), last->getCode(), output);
}

int minimumStationsPath::doBFS(Station* first, Station* last, map<int, pair<int, string>>& pred, map<string, Line*>& lines, map<int, Station*>& stations)
{
    queue<int>visit_children;
    set <int> visited_stations;

    //visit first
    visit_children.push(first->getCode());
    visited_stations.insert(first->getCode());
    pred.insert(pair<int, pair<int, string>>(first->getCode(), pair <int, string>(-1, "")));

    while (!visit_children.empty()) {
        int code = visit_children.front();
        visit_children.pop();
        //visit code and check if it is last station
        if (stations[code]->BFSStationSearch(last->getCode(), visit_children,visited_stations, pred)) return code;
    }
    
    throw(SearchError("Path "+ first->outputStationCodeAndName()+"->"+last->outputStationCodeAndName()+ " does not exists"));
}

void MinimumLinesPath::findPath(Station* first, Station* last,  map<string, Line*>& lines,  map<int, Station*>& stations)
{
    map<string, pair<string, int>>pred;
    string output="";

    string label = doBFS(first, last,pred, lines, stations);

    int beg = pred[label].second;
    int end = last->getCode();

    while (label != "") {//while not first line
        output = pred[label].first + "->" + label + "\n"+Station::writePath(stations[beg], stations[end],label)+"\n"+output;//output this line
        end=beg;//go to previous line
        label = pred[label].first;
        beg = pred[label].second;
    }

    FindingPaths::printPath(first->getCode(), last->getCode(),output);
}

string MinimumLinesPath::doBFS(Station* first, Station* last, map<string, pair<string, int>>& pred, map<string, Line*>& lines, map<int, Station*>& stations)
{
    queue<pair<string, int>>visit_children;
    set<string>visited_lines;
    set<int>visited_stations;

    //remember lines in zero level to go through their stations later
    first->markLines("", visited_stations, visited_lines, visit_children, pred);

    while (!visit_children.empty()) {

        string label = visit_children.front().first;
        int code = visit_children.front().second;
        visit_children.pop();
        //check if current child has last station
        if (lines[label]->BFSLineSearch(last->getCode(), stations[code], visited_stations, visited_lines, visit_children, pred))return label;
    }
    return "";
}

void FindingPaths::printPath(int first_code, int last_code, string output)
{
    fstream output_file("putanja_" + to_string(first_code) + "_" + to_string(last_code) + ".txt", ios::out);
    output.pop_back();
    output_file << output;
    output_file.close();
}

