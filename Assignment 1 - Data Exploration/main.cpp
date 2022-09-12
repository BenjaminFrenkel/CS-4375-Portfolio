/**
 * Name: Benjamin Frenkel
 * Class: CS-4375 Machine Learning
 * Professor: Dr. Karen Mazidi
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <tgmath.h>

using namespace std;

vector<double> print_stats(vector<double> data)
{
    vector<double> stats(4);

    //sum
    double sum = 0;

    for(int i = 0; i < data.size(); i++)
    {
        sum = sum + data.at(i);
    }

    cout << "Sum: " << sum << endl;

    //Mean
    double mean = 0.0;
    mean = sum/data.size();

    cout << "Mean: " << mean << endl;

    //Median
    double median = 0.0;

    sort(data.begin(), data.end());

    //check if the number of elements is odd or even
    if(data.size() % 2 == 0)
    {
        int index1 = data.size()/2;
        int index2 = index1 + 1;

        median = (data.at(index1) + data.at(index2)) / 2;
    }
    else
    {
        median = data.at(data.size()/2);
    }

    cout << "Median: " << median << endl;

    //Range
    double range = data.at(data.size() - 1) - data.at(0);

    cout << "Range: " << range << endl;

    stats.at(0) = sum;
    stats.at(1) = mean;
    stats.at(2) = median;
    stats.at(3) = range;

    return stats;
}

double covar(vector<double> rm, vector<double> medv, double mean_rm, double mean_medv)
{
    double sum = 0.0;

    for(int i = 0; i < rm.size(); i++)
    {
        sum = sum + (rm.at(i) - mean_rm)*(medv.at(i) - mean_medv);
    }

    return sum/(rm.size() - 1);
}

double cor(vector<double> rm, vector<double> medv, double mean_rm, double mean_medv, double covariance)
{
    double std_dev_rm = 0.0;
    double std_dev_medv = 0.0;

    double numerator = 0.0;
    for(int i = 0; i < rm.size(); i++)
    {
        numerator = numerator + pow((rm.at(i) - mean_rm), 2);
    }

    std_dev_rm = sqrt(numerator/rm.size());

    numerator = 0.0;
    for(int i = 0; i < medv.size(); i++)
    {
        numerator = numerator + pow((medv.at(i) - mean_medv), 2);
    }

    std_dev_medv = sqrt(numerator/medv.size());

    double correlation = covariance/(std_dev_rm*std_dev_medv);

    return correlation;
}


int main(int argc, char** argv) {

    ifstream inFS; //input file stream
    string line;
    string rm_in, medv_in;
    const int MAX_LEN = 1000;
    vector<double> rm(MAX_LEN);
    vector<double> medv(MAX_LEN);

    //Try to open file
    cout << "Opening file Boston.csv." << endl;

    inFS.open("Boston.csv");
    if(!inFS.is_open())
    {
        cout << "Could not open file Boston.csv." << endl;
        return 1; // 1 indicates error
    }

    //Can now use inFS stream like cin stream
    //Boston.csv should contain two doubles

    cout << "Reading line 1" << endl;
    getline(inFS, line);

    //echo heading
    cout << "heading" << line << endl;

    int numObservations = 0;
    while(inFS.good())
    {
        getline(inFS, rm_in, ',');
        getline(inFS, medv_in, '\n');

        rm.at(numObservations) = stof(rm_in);
        medv.at(numObservations) = stof(medv_in);

        numObservations++;
    }

    rm.resize(numObservations);
    medv.resize(numObservations);

    cout << "new length" << rm.size() << endl;

    cout << "Closing file Boston.csv." << endl;
    inFS.close(); // Done with file, so close it

    cout << "Number of records: " << numObservations << endl;

    vector<double> stats_rm(4);
    vector<double> stats_medv(4);

    cout << "\nStats for rm" << endl;
    stats_rm = print_stats(rm);

    cout << "\nStats for medv" << endl;
    stats_medv = print_stats(medv);

    double covariance = covar(rm, medv, stats_rm.at(1), stats_medv.at(1));

    cout << "\nCovariance = " << covariance << endl;

    cout << "\nCorrelation = " << cor(rm, medv, stats_rm.at(1), stats_medv.at(1), covariance) << endl;

    //cout << "\nProgram terminated.";

    return 0;
}
