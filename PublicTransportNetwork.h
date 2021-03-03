#ifndef PUBLIC_TRANSPORT_NETWORK
#define PUBLIC_TRANSPORT_NETWORK

#include"FindingPaths.h"
#include"Line.h"
#include"OutputNetwork.h"
#include"Station.h"

#include<fstream>
#include<iostream>
#include<map>
#include<string>

class PublicTransportNetwork{
public:
	PublicTransportNetwork(const PublicTransportNetwork&) = delete;
	PublicTransportNetwork& operator=(const PublicTransportNetwork&) = delete;
	~PublicTransportNetwork();

	static PublicTransportNetwork& getNetwork();

	void readStations(const string& path);
	void readLines(const string& path);
	void readLineStations(int& code, const string& label, const string& path, int& pos);

	void setStationsOutputStrategy(StationsOutput*);
	void setLinesOutputStrategy(LinesOutput*);
	void setStatisticsOutputStrategy(StatisticsOutput*);
	void setFindingPathsStrategy(FindingPaths*);

	void outputStations();
	void outputLines();
	void outputStatistics();

	void findPath(int first_station_code,int last_station_code);


private:
	PublicTransportNetwork()=default;

	map<string, Line*> lines_;
	map<int,Station*>stations_;

	StationsOutput* stations_output_strategy_;
	LinesOutput* lines_output_strategy_;
	StatisticsOutput* statistics_output_strategy_;
	FindingPaths* finding_paths_strategy_;

};
#endif
