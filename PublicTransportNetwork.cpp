#include"Exceptions.h"
#include "PublicTransportNetwork.h"

PublicTransportNetwork::~PublicTransportNetwork()
{
    for (pair<int, Station* >station : stations_)delete station.second;
    for (pair<string, Line*>line : lines_)delete line.second;
    
    delete finding_paths_strategy_;
    delete lines_output_strategy_;
    delete stations_output_strategy_;
    delete statistics_output_strategy_;

}
PublicTransportNetwork& PublicTransportNetwork::getNetwork()
{
    static PublicTransportNetwork unique_network;
    return unique_network;
}

void PublicTransportNetwork::readStations(const string& path)
{
    Station* station = nullptr;
    try {
        fstream input_file(path, ios::in);
        if (!input_file.is_open())throw(FileError("Error opening the file"));

        string line = "";
        int pos = 0;

        while (input_file.peek() != EOF) {
            pos = 0;
            getline(input_file, line);
            station = new Station(line, pos);

            if (stations_.find(station->getCode()) == stations_.end())
                stations_.insert(pair<int, Station*>(station->getCode(), station));
            else {
                throw(ReadingError("Station already exists"));
            }
        }

        input_file.close();
    }
    catch (ReadingError& e) {
        if(station)delete station;
        throw;
    }
    catch (SearchError& e) {
        if (station)delete station;
        throw;
        }
}

void PublicTransportNetwork::readLines(const string& path)
{
    Line* network_line=nullptr;
    try {
        
        fstream input_file(path, ios::in);
        if (!input_file.is_open())throw(FileError("Error opening the file"));

        string line;
        int pos = 0;

        while (input_file.peek() != EOF) {

            pos = 0;
            getline(input_file, line);
            network_line = new Line(line, pos);

            if (lines_.find(network_line->getLabel()) != lines_.end()) {
                delete network_line;
                throw(ReadingError("Line already exists"));
            }

            if (line[pos++] != ' ')throw(ReadingError("Space not found"));

            //reading first station
            int code = Station::readCode(line, pos);//TODO koristi find da bi proverila dal je uneta stanica-fja check code
            network_line->setFirstStation(stations_[code]);
            readLineStations(code, network_line->getLabel(), line, pos);//reading first direction

            if (pos == line.length())throw(ReadingError("# not found"));
            pos++;

            network_line->setLastStation(stations_[code]);//saving last station and reading its second occurence from string
            Station::readCode(line, pos);
            readLineStations(code, network_line->getLabel(), line, pos);//reading second direction

            //saving map of lines
            lines_.insert(pair<string, Line*>(network_line->getLabel(), network_line));
        }

        input_file.close();
    }
    catch (ReadingError& e) {
        if (network_line)delete network_line;
        throw;
    }
    catch (SearchError&e) {
        if (network_line)delete network_line;
        throw;
        }
}

void  PublicTransportNetwork::readLineStations(int& code,const string& label, const string& line, int& pos)
{
    int prev_code = code;
    //reading direction
    while (pos < line.length() && line[pos] != '#') {

        if (line[pos++] != ' ')throw(ReadingError("Space not found"));

        code = Station::readCode(line, pos);

        //adding this station to previous stations neighbours
        if (stations_.find(code) != stations_.end())
            stations_[prev_code]->addNeighbour(label, stations_[code]);
        else
            throw(SearchError("Station " + to_string(code) + "does not exists"));

        prev_code = code;
    }

}

void PublicTransportNetwork::setStationsOutputStrategy(StationsOutput* stations_output_strategy)
{
    if (stations_output_strategy_ != nullptr)delete stations_output_strategy_;
    stations_output_strategy_ = stations_output_strategy;
}

void PublicTransportNetwork::setLinesOutputStrategy(LinesOutput*lines_output_strategy)
{
    if (lines_output_strategy_ != nullptr)delete lines_output_strategy_;
    lines_output_strategy_ = lines_output_strategy;
}

void PublicTransportNetwork::setStatisticsOutputStrategy(StatisticsOutput*statistics_output_strategy)
{
    if (statistics_output_strategy_ != nullptr)delete statistics_output_strategy_;
    statistics_output_strategy_ = statistics_output_strategy;
}

void PublicTransportNetwork::setFindingPathsStrategy(FindingPaths* finding_paths_strategy)
{
    if (finding_paths_strategy_ != nullptr)delete finding_paths_strategy_;
    finding_paths_strategy_ = finding_paths_strategy;
}

void PublicTransportNetwork::outputStations()
{
    stations_output_strategy_->output(stations_);
}

void PublicTransportNetwork::outputLines()
{
    lines_output_strategy_->output(lines_);
}

void PublicTransportNetwork::outputStatistics()
{
    statistics_output_strategy_->output(lines_, stations_);
}

void PublicTransportNetwork::findPath(int first_station_code, int last_station_code)
{
    finding_paths_strategy_->findPath(stations_[first_station_code], stations_[last_station_code],lines_,stations_);
}
