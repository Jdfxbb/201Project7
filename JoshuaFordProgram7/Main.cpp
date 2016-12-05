/*********************************************

Name: Joshua Ford
Course: CS 201R
Program: Program 7 Programming Tournament
Due Date: 6 May 2016
Description: Process team results chronologically and report winner
Inputs:	Data_01.csv
Outputs: rankings.txt, Teams.txt
Algorithm:
1. Add each submission to the teams' corresponding queue
2. Process each queue to determine score and problems solved
3. Output list of teams and results
4. Output ranked list of teams and results

*********************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"

using namespace std;

// team struct
struct TeamData
{
	int time, teamNum, solved, score;
	char problem;
	bool wasSolved;
	TeamData()
	{
		solved = score = 0;
	}
	// overloaded input stream for struct
	friend void operator >> (istream& in, TeamData& rhs)
	{
		string language, judgement;
		in >> rhs.time >> rhs.teamNum >> rhs.problem >> language >> judgement;
		rhs.wasSolved = (judgement == "Yes" || judgement == "yes");
		getline(in, language); // clear rest of line
	}

};

void main()
{
	// array of queues of TeamData and array of TeamData for sorting later
	Queue<TeamData> TeamArray[30];
	TeamData Rankings[30];
	TeamData temp;
	
	// input/output
	ifstream fin("Data_01.csv");
	ofstream outTeams("Teams.txt");
	ofstream outRankings("rankings.txt");

	int count = 0; // used for all array iterating

	// read in data
	while (fin.good())
	{
		fin >> temp;

		// if it's a new team, increment count
		if (TeamArray[temp.teamNum - 1].isEmpty())
			count++;
		TeamArray[temp.teamNum - 1].push_back(temp);
	}

	// process scores
	for (int i = 0; i < count; i++)
	{
		// keeps track of penalties based on ascii value of letter (A-H)
		int penaltyTracker[8] = { 0 };
		Rankings[i].teamNum = i + 1;

		while (!TeamArray[i].isEmpty())
		{
			temp = TeamArray[i].pop();
			if (temp.wasSolved)
			{
				// if the problem was solved, add the time plus any penalties and increment solved
				Rankings[i].score += temp.time + penaltyTracker[int(temp.problem) - 65];
				Rankings[i].solved += 1;
			}
			else penaltyTracker[int(temp.problem) - 65] += 20;
		}
	}

	// output before sorting
	for (int i = 0; i < count; i++)
	{
		outTeams << "Team " << Rankings[i].teamNum << " solved " << Rankings[i].solved << " in " << Rankings[i].score << " minutes." << endl;
	}

	
	// rank teams, simple selection sort 
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < count; j++)
		{
			// check equality of solved, if equal check score
			if ((Rankings[i].solved > Rankings[j].solved) || (Rankings[i].solved == Rankings[j].solved && Rankings[i].score < Rankings[j].score))
			{
				swap(Rankings[i], Rankings[j]);
			}
		}
	}

	// output after sorting
	for (int i = 0; i < count; i++)
	{
		outRankings << "Team " << Rankings[i].teamNum << " solved " << Rankings[i].solved << " in " << Rankings[i].score << " minutes." << endl;
	}


	// close files
	fin.close();
	outTeams.close();
	outRankings.close();
}