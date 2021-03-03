#include"Exceptions.h"
#include "OutputNetwork.h"

void BasicStationsOutput::output(map<int, Station*> stations_)
{
	
	for (auto station = stations_.begin(); station != stations_.end(); station++) {
		
		fstream output_file("stajaliste_"+to_string(station->second->getCode())+".txt", ios::out);

		if (!output_file.is_open())throw(FileError("Error opening the file"));
		//output station and its lines
		output_file << station->second->getCode() << " " << station->second->getName() << " ["<< station->second->outputLines()<< "]";
       
		output_file.close();
	}
	
}

void BasicLinesOutput::output(map<string, Line*> lines)
{
	for (auto line = lines.begin(); line != lines.end(); line++) {

		fstream output_file("linija_" + line->first+".txt", ios::out);
		if (!output_file.is_open())throw(FileError("Error opening the file"));

		output_file << line->first << " " << line->second->getFirstStation()->getName();
		output_file<< "->" << line->second->getLastStation()->getName() <<endl;
		output_file<<line->second->outputStations();
		
		output_file.close();
	}
}

void BasicStatisticsOutput::output(map<string, Line*> lines, map<int, Station*>stations)
{
	map<pair<string, string>, int>intersections;
	map<string, int>max;

	for (auto station : stations) {//write pairs of all lines that go through this station
		station.second->writeIntersection(intersections, max);
	}

	auto i = intersections.begin();

	while (i != intersections.end()) {

		//first line label
		string line1 = i->first.first;
		string line_of_max = "";
		string line_of_intersection = "";

		//open the file		
		fstream output_file("statistika_" + line1 + ".txt", ios::out);
		if (!output_file.is_open())throw(FileError("Error opening the file"));

		//output first line name
		output_file << line1 << endl;

		while (i!=intersections.end()&&line1 == i->first.first) {//while not end and same line
			
			   string line2 = i->first.second;

			   line_of_intersection += line2 + " ";//write line that intersects with line1

			   if (intersections[pair<string, string>(i->first)] == max[line1]) {//id this is max write it in max
				   line_of_max += line2 + ",";
			    }

			i++;
		}
		//when output of one line is stored
		if (line_of_intersection != "") {
			line_of_intersection.pop_back();//delete last newline
			output_file << line_of_intersection << endl;//write intersections
		}
		if (line_of_max != "") {
			line_of_max.pop_back();
			output_file << line_of_max;
		}

		output_file.close();
	}
}

StationsOutput::~StationsOutput()
{
}

LinesOutput::~LinesOutput()
{
}

StatisticsOutput::~StatisticsOutput()
{
}
