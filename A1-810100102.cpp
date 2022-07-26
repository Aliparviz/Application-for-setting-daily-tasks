#include<iostream>
#include<vector>
#include<string>
using namespace std;
struct Overall_Time
{
	int start_hour;
	int start_minute;
	int end_hour;
	int end_minute;
};
struct Plan
{
	int start_hour;
	int start_minute;
	int end_hour;
	int end_minute;
	int needed_time;
	int id;
};
vector <string> tokenize(string input, string donoghte_space)
{
	int start = 0;
	int end = input.find(donoghte_space);
	vector<string>temporary;
	while (end != -1)
	{
		temporary.push_back(input.substr(start, end - start));
		start = end + donoghte_space.size();
		end = input.find(donoghte_space, start);
	}
	temporary.push_back(input.substr(start, end - start));
	return temporary;

}
void get_busy_times_hashtag(vector<Overall_Time>*busy_times, int *check_hashtag, string input)
{
	struct Overall_Time* temp = (Overall_Time*)malloc(2 * sizeof(Overall_Time));
	vector<string> temporary;
	if (input == "#")
	{
		*check_hashtag = 1;
		return;
	}
	else
	{
		string donoghte = ":";
		input.replace(5, 1, donoghte);
		int start_hour;
		int start_minute;
		int end_hour;
		int end_minute;
		temporary = tokenize(input, donoghte);
		temp->start_hour = stoi(temporary[0]);
		temp->start_minute = stoi(temporary[1]);
		temp->end_hour = stoi(temporary[2]);
		temp->end_minute = stoi(temporary[3]);
		busy_times->push_back(*temp);
	}
	free(temp);
	return;
}

void get_plans_time(vector<Plan>*today_plans, string input)
{
	struct Plan* plan = (Plan*)malloc(2 * sizeof(Plan));
	string space = " ";
	vector<string>temporary;
	temporary = tokenize(input, space);

	plan->needed_time = stoi(temporary[0]);
	plan->start_hour = 12;
	plan->start_minute = 00;
	plan->end_hour = 12 + (stoi(temporary[0]) / 60);
	plan->end_minute = stoi(temporary[0]) % 60;
	plan->id = stoi(temporary[1]);

	today_plans->push_back(*plan);
}
void initial_falses(vector<bool>&Time, vector<Overall_Time>busy_times)
{
	for (int i = 0; i < busy_times.size(); i++)
	{
		int start_index = ((busy_times[i].start_hour - 12) * 60) + busy_times[i].start_minute;
		int end_index = ((busy_times[i].end_hour - 12) * 60) + busy_times[i].end_minute;
		for (int j = start_index; j < end_index; j++)
		{
			Time[j] = false;
		}
	}
}

void sort(vector<Plan>&today_plans, vector<Overall_Time>&busy_times, vector<Plan>&print,vector<bool>&Time)
{
	struct Plan temp ;
	int check_trues = 0;
	initial_falses(Time, busy_times);
	for (int i = 0; i < Time.size(); i++)
	{
		if (Time[i] == true)
		{
			for (int j = i; j < i + today_plans[0].needed_time; j++)
			{
				if (Time[j] == true)
					check_trues++;
			}

			if (check_trues >= today_plans[0].needed_time)
			{
				temp.start_hour = 12 + (i / 60);
				temp.start_minute = i % 60;
				temp.end_hour = 12 + ((i + today_plans[0].needed_time) / 60);
				temp.end_minute = (i + today_plans[0].needed_time) % 60;
				temp.id = today_plans[0].id;

				for (int j = i; j < i + today_plans[0].needed_time; j++)
				{
					Time[j] = false;
				}
				break;
			}
		}
		check_trues = 0;
	}
	today_plans.erase(today_plans.begin());
	print.push_back(temp);
}

int main()
{
	int busy_time_hour;
	int busy_time_minute;
	int check_hashtag = 0;
	vector <Overall_Time>busy_times;
	vector <Plan>today_plans;
	vector <Plan> print;
	vector<bool>Time(480, true);
	string input;
	while (getline(cin, input))
	{

		if (check_hashtag == 0)
		{
			get_busy_times_hashtag(&busy_times, &check_hashtag, input);
		}
		else
		{
			get_plans_time(&today_plans, input);

			sort(today_plans, busy_times, print,Time);
		}
	}

	for (int i = 0; i < print.size(); i++)
	{
		printf("%d %02d:%02d-%02d:%02d %d\n", (print)[i].id, (print)[i].start_hour, (print)[i].start_minute,
			(print)[i].end_hour, (print)[i].end_minute);
	}
	return 0;
}