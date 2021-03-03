#include "Line.h"

#include"Exceptions.h"

string Line::getLabel()
{
    return label_;
}

Station* Line::getFirstStation()
{
    return first_station_;
}

Station* Line::getLastStation()
{
    return last_station_;
}

string Line::outputStations()
{
    try {
        string output;
        Station* station = first_station_;

        do {
            output += station->outputStationCodeAndName();
            if (station == last_station_) {//output last station two times
                output += station->outputStationCodeAndName();
            }
            station = station->getNeighbour(label_);
        } while (station != first_station_);

        output += station->outputStationCodeAndName();//output first station second time
        output.pop_back();

        return output;
    }
    catch (SearchError& e) {
        cout << "Line: " << label_ << " is not cyclic";
    }
}

bool Line::BFSLineSearch(int last_code,Station* first_station,set<int>&visited_stations,set<string>& visited_lines, queue<pair<string,int>>& visit_children, map<string, pair<string, int>>& pred)
{
    visited_lines.insert(label_);//this line is visited
    Station* temp_station = first_station;  

    do {
         //if station isn't visited save its lines to visit them later
         if (visited_stations.find(temp_station->getCode()) == visited_stations.end()) {
              temp_station->markLines(label_, visited_stations, visited_lines, visit_children, pred);
          }
         //if you come to last station for the first time finish search
         if (temp_station->getCode() == last_code) {
            return true;
          }
         //go to next station on this line
         temp_station = temp_station->getNeighbour(label_);
      
     }while(temp_station != first_station );//go while loop is not finished

    return false;
}

Line::Line(const string& text, int& pos):first_station_(nullptr),last_station_(nullptr){
      while (pos < text.length() && text[pos] != ' ')label_ += text[pos++];//read label from text
}

void Line::setFirstStation(Station* station)
{
    first_station_ = station;
}

void Line::setLastStation(Station* station)
{
    last_station_ = station;
}


