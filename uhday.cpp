#include <iostream>
#include <cstring>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[])
{
  //read file in
  string file_to_read = static_cast <string> (argv[1]);
  string inputfile = file_to_read.erase(0,6);
  //cout << endl << "inputfile = " << inputfile << endl;
  ifstream file(inputfile);
  long sum_minutes = 0;
  long sum_hours = 0; 
  long sum_days = 0;
  //if file is invalid abort
  if (!file) 
  {
    cout << "error check input file, file doesn't exist or is invalid.... aborting" << endl;
    return 1;
  }
  //copy file to stringtream for better manipulation and close file
  stringstream sstream;
  sstream << file.rdbuf();    
  file.close();
  //copy words in file to a vector of strings with delimiters " ,;()" and newline
  std::vector<string> wordVector;
  string line;
  while(getline(sstream, line)) 
  {
    //the following line trims white space from the beginning of the string
    line.erase(line.begin(), find_if(line.begin(), line.end(), not1(ptr_fun<int, int>(isspace)))); 
    //ignore lines that start with '#'' comment sign
    if(line[0] != '#') 
    {
      // TODO: adjust prev word for new line cases where there are comments inbetween
      size_t prev = 0, pos;
      while ((pos = line.find_first_of(" ,;()", prev)) != string::npos)
      {
        if (pos > prev)
            wordVector.push_back(line.substr(prev, pos-prev));
        prev = pos+1;
      }
      if (prev < line.length())
      {
        wordVector.push_back(line.substr(prev, string::npos));
      }
    }
  }  
  //for each word in vector
  for( int i = 0; i < wordVector.size(); i++ ) 
  {
    //convert word to lower case
    for (int j=0; j<wordVector[i].length(); j++)
    {
        wordVector[i][j]=tolower(wordVector[i][j]);
    }
    //cout << wordVector[i]<< " ----------------- " << wordVector[i-1];
    //check if word is minute
    if (wordVector[i] =="minutes" || wordVector[i] == "minute")
    {
      //cout << "<-------------------this is minute";
      //check if the previous word is number
      if (wordVector[i-1].find_first_not_of( "0123456789" ) == string::npos)
      {
        sum_minutes += atol(wordVector[i-1].c_str());
      }
    }
    else if (wordVector[i] =="hours" || wordVector[i] == "hour")
    {
      //cout << "<-------------------this is hours";
      //check if the previous word is string
      if (wordVector[i-1].find_first_not_of( "0123456789" ) == string::npos)
      {
        sum_hours += atol(wordVector[i-1].c_str());
      }
    }
    if (wordVector[i] =="days" || wordVector[i] == "day")
    {
      //cout << "<-------------------this is day";
      //check if the previous word is string
      if (wordVector[i-1].find_first_not_of( "0123456789" ) == string::npos)
      {
        sum_days += atol(wordVector[i-1].c_str());
      }
    } 
    //cout << "        Minutes:" << sum_minutes << " Hours:" << sum_hours << "days:" << sum_days << endl;
  }
  //cout << endl << endl ;
  cout << "Minutes:" << sum_minutes << endl << "Hours:" << sum_hours << endl << "days:" << sum_days << endl;
  return 0;
}


