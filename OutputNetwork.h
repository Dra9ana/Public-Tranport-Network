#ifndef OUTPUT_H
#define OUTPUT_H

#include"Line.h"
#include"Station.h"

#include<fstream>
#include<map>
#include<string>

class StationsOutput {
public:	
	   virtual ~StationsOutput();
	   virtual void output(map<int, Station*>stations_)=0;
};
class BasicStationsOutput :public StationsOutput {
public: 
	    void output(map<int, Station*>stations_)override;
};
class LinesOutput  {
public:virtual ~LinesOutput();
	   virtual void output(map<string, Line*> lines)=0;
};
class BasicLinesOutput:public LinesOutput {
public: void output(map<string, Line*> lines)override;
};
class StatisticsOutput {
public:virtual ~StatisticsOutput();
	    virtual void output(map<string, Line*> lines, map<int, Station*> stations)=0;
};
class BasicStatisticsOutput:public StatisticsOutput {
public: void output(map<string, Line*> lines,map<int,Station*> stations)override;
};
#endif
