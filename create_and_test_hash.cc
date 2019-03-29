/**
    Name: Ethan Sam 
	Date: 3/28/2019
	Professor: Ioannis Stamos
	Class: CSCI 335
	
	File: create_and_test_hash.cc
	
	This program 
	
	
 Few comments describing the class HashTableLinear
 **/
#include "quadratic_probing.h"
#include "linear_probing.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


template <typename HashTableType>
void TestFunctionForHashTable(HashTableType &hash_table, const string &words_filename, const string &query_filename) 
{
  cout << "TestFunctionForHashTables..." << endl;
  cout << "Words filename: " << words_filename << endl;
  cout << "Query filename: " << query_filename << endl;
  
  //..Insert your own code
  
   hash_table.MakeEmpty();  
   hash_table.resetNumOfCollisions();

  //c_str() is a library function that splits a c-string into tokens
  //A pointer to the c-string representation of the string object's value.
  // std::string should work fine
  ifstream wordsFile;
  wordsFile.open(words_filename);
  
  //Check if able to open
  if(wordsFile.fail())
  {
	  cerr << "Cannot open words_filename\n";
  }
  
  string line_input;
  //Checking error flags
  while(wordsFile.good())
  { 
	getline(wordsFile, line_input);
	hash_table.Insert(line_input);
  }
  
  //Hashing Implementation Testing Part A
  cout << "Part A:\n";
  
  cout << "Number of items: " << hash_table.getNumOfElements() << endl;
  cout << "Size of hash table: " << hash_table.getSize() << endl;
  cout << "Load factor: "<< (hash_table.getNumOfElements() / (double)hash_table.getSize()) << endl;
  cout << "Collisions: " << hash_table.getNumOfCollisions() << endl;
  cout << "Avg. number of collisions: " << (hash_table.getNumOfCollisions()/(double)hash_table.getNumOfElements()) << endl;
  
  ifstream queryFile;
  queryFile.open(query_filename.c_str());
  if (queryFile.fail())
  {
    cerr << "Cannot open query_filename\n";
  }
  cout << "Part B:\n";
  //Hashing Implementation Testing Part B
  while(queryFile.good())
  {
	  getline(queryFile, line_input);
      if(hash_table.Contains(line_input)) 
	  {
		  
		 // The "number of collisions + 1" determines the number of probes used
		 //You must find a new position in the hashtable, so you collide until you find a position
        cout << line_input << " Found " << hash_table.getNumOfCollisions()+1 << endl;
		//Reset the collisions because we want to find the number of probes only
        hash_table.resetNumOfCollisions();
      } 
	  else 
	  {
        cout << line_input << " Not Found " << hash_table.getNumOfCollisions() + 1 << endl;
        hash_table.resetNumOfCollisions();
      }
  }
  
  
//Close both files
wordsFile.clear();
wordsFile.close();
queryFile.clear();
queryFile.close();  
}


// Sample main for program create_and_test_hash
int main(int argc, char **argv) 
{
  if (argc != 4) 
  {
    cout << "Usage: " << argv[0] << " <wordsfilename> <queryfilename> <flag>" << endl;
    return 0;
  }
  
  const string words_filename(argv[1]);
  const string query_filename(argv[2]);
  const string param_flag(argv[3]);

  if (param_flag == "linear") 
  {
     HashTableLinear<string> linear_probing_table;
     TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
  } 
  else if (param_flag == "quadratic") 
  {
    HashTable<string> quadratic_probing_table;
    TestFunctionForHashTable(quadratic_probing_table, words_filename, query_filename);    
  } 
  else if (param_flag == "double") 
  {
    // HashTableDouble<string> double_probing_table;
    // TestFunctionForHashTable(double_probing_table, words_filename, query_filename);    
  } 
  else 
  {
    cout << "Unknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}







