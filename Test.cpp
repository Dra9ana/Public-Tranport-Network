#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include"Exceptions.h"
#include"OutputNetwork.h"
#include"PublicTransportNetwork.h"


#include<iostream>

using namespace std;

int main() {
	//_crtBreakAlloc = 398;
    int i = 1;

	try {
		string path;
		
		cout << "Please input path to the file with information about stations" << endl;
		getline(cin, path);
		PublicTransportNetwork::getNetwork().readStations(path);
		cout << "Stations are successfully created" << endl;

		cout << "Please input path to the file with information about lines" << endl;
		getline(cin, path);
		PublicTransportNetwork::getNetwork().readLines(path);
		cout << "Lines are successfully created" << endl;
	}
	catch (FileError& e) {
		cout << "INPUT ERROR: " << e.what() << endl;
		i = 0;
	}
	catch (ReadingError& e) {
		cout << "INPUT ERROR: " << e.what() << endl;
		i = 0;
	}
	catch (SearchError& e) {
		cout << "INPUT ERROR: " << e.what() << endl;
		i = 0;
	}


	while(i!=0){
		cout << "Choose action:" << endl;
		cout << "0.End program" << endl;
		cout << "1.Output" << endl;
		cout << "2.Finding path" << endl;
		cin >> i;
		  switch (i) {
			      int j;
		       case 1: {
			      cout << "Choose output:" << endl;
			      cout << "0.End program" << endl;
			      cout << "1.Output stations" << endl;
			      cout << "2.Output lines" << endl;
			      cout << "3.Output lines statistic" << endl;
				  try {
					  cin >> j;
					  switch (j) {
					  case 0: i = 0;
						  break;
					  case 1: PublicTransportNetwork::getNetwork().setStationsOutputStrategy(new BasicStationsOutput());
						  PublicTransportNetwork::getNetwork().outputStations();
						  break;
					  case 2:PublicTransportNetwork::getNetwork().setLinesOutputStrategy(new BasicLinesOutput());
						  PublicTransportNetwork::getNetwork().outputLines();
						  break;
					  case 3:PublicTransportNetwork::getNetwork().setStatisticsOutputStrategy(new BasicStatisticsOutput());
						  PublicTransportNetwork::getNetwork().outputStatistics();
						  break;
					  default:cout << "Option " << j << " does not exists";
					  }
				  }
				  catch (FileError& e) {
					  cout << "OUTPUT ERROR: " << e.what() <<" Try again!"<<endl;
				  }
				  catch (SearchError& e) {
					  cout << "OUTPUT ERROR: " << e.what() << " Try again!" << endl;
				  }
			     
		        }break;
		      case 2: {
			       int first, last;
			       cout << "Please enter first station code and last station code:" << endl;
			       cin >> first;
			       cin >> last;
			       cout << "Choose path:" << endl;
			       cout << "0.End program" << endl;
			       cout << "1.Any path" << endl;
			       cout << "2.Path with minimum stations" << endl;
			       cout << "3.Path with minimum lines" << endl;
			       cin >> j;
				   try {
					   switch (j) {
					   case 0:i = 0;
					   case 1:case 2:PublicTransportNetwork::getNetwork().setFindingPathsStrategy(new minimumStationsPath());
						   PublicTransportNetwork::getNetwork().findPath(first, last);
						   break;
					   case 3:PublicTransportNetwork::getNetwork().setFindingPathsStrategy(new MinimumLinesPath());
						   PublicTransportNetwork::getNetwork().findPath(first, last);
						   break;
					   }
				   }
				   catch (SearchError& e) {
					   cout << "SEARCH ERROR: " << e.what() << endl;
				   }
				   catch (FileError& e) {
					   cout << "SEARCH ERROR: " << e.what() << endl;
				   }
		       }
			  break;
			  default:
				  cout << "Option " << i << "does not exists" << endl;
		   }
     }

	
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	
	
	return 0;
}