// Ethan Sam

#include "quadratic_probing.h"
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
  hash_table.MakeEmpty();  
  //..Insert your own code
  
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
  cout << "Collisions: " << hash_table.getNumOfCollisions() << endl;
  cout << "Number of items: " << hash_table.getNumOfElements() << endl;
  cout << "Size of hash table: " << hash_table.getSize() << endl;
  cout << "Load factor: "<< (hash_table.getNumOfElements() / (float)hash_table.getSize()) << endl;
  cout << "Avg. number of collisions: " << (hash_table.getNumOfCollisions()/(float)hash_table.getNumOfElements()) << endl;
  
  ifstream queryFile;
  queryFile.open(query_filename);
  if (queryFile.fail())
  {
    cerr << "Cannot open query_filename\n";
  }
  string queryLine;
  //Hashing Implementation Testing Part B
  while(queryFile.good())
	  getline(queryFile, queryLine);
      if(hash_table.Contains(queryLine)) 
	  {
		 // The "number of collisions + 1" determines the number of probes used
		 //You must find a new position in the hashtable, so you collide until you find a position
        cout << queryLine << "Found " << hash_table.getNumOfCollisions()+1 << endl;
		//Reset the collisions because we want to find the number of probes only
        hash_table.resetNumOfCollisions();
      } 
	  else 
	  {
        cout << queryLine << " Not Found " << hash_table.getNumOfCollisions()+1 << endl;
        hash_table.resetNumOfCollisions();
      }
  
  
wordsFile.clear();
wordsFile.close();
queryFile.clear(); 
queryFile.close();  
  
}


// Sample main for program create_and_test_hash
int
main(int argc, char **argv) 
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
    // HashTableLinear<string> linear_probing_table;
    // TestFunctionForHashTable(linear_probing_table, words_filename, query_filename);    
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
    cout << "Uknown tree type " << param_flag << " (User should provide linear, quadratic, or double)" << endl;
  }
  return 0;
}







