/**
    Name: Ethan Sam 
	Date: 3/28/2019
	Professor: Ioannis Stamos
	Class: CSCI 335
	
	Header file: spell_check.cc
	
	This spell_check program checks for three cases:
	
	Removed chaarcters (in every position)
	Added characters( from a-z) in every position
	Swapped characters (from index = 0 to the total 
	of the string)
	
	
 Few comments describing the Spell Check Program
**/ 


#include "linear_probing.h"  
#include "quadratic_probing.h"  
#include "double_probing.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
using namespace std;


// ./SpellCheck document1_short.txt wordsEn.txt
// ./SpellCheck document1_1.txt wordsEn.txt

template <typename HashTableType> 
void FindAndPrintMisspelled(HashTableType &hash_table, const string &document_file, const string &dictionary_file) 
{

  cout << "TestFunctionForHashTables..." << endl;
  cout << "Dictionary Filename: " << dictionary_file << endl;
  cout << "Document Filename: " << document_file << endl;

  //Since num_of_collisions is a mutatable variable 
  //And "static std::hash<HashedObj> hf;" retains the value no matter the amoutn fo calls,
  //We must make the hash_table empty and reset the amount of collisions
  hash_table.MakeEmpty();
  hash_table.resetNumOfCollisions();
  
  //Standard method of opening and reading a file
  ifstream document_stream;
  document_stream.open(document_file);
  //Check for error flags
  if (document_stream.fail())
  {
    cerr << "Error opening document file\n";
  }
  ifstream dictionary_stream;
  dictionary_stream.open(dictionary_file);
  //Check for error flags
  if (dictionary_stream.fail()) 
  {
    cerr << "Error opening dictionary file\n";
  }
//________________________________________________
  bool skipApostropheWord;
  string line_input;
  //Store each line from the distionary into line_input
  while(dictionary_stream.good()) 
  {
    getline(dictionary_stream, line_input);
    hash_table.Insert(line_input);
  }
  //Skip words with apostrophes
  skipApostropheWord = false; 

  //Parse the document  
  while(document_stream >> line_input)
  {
    string letterOfWord = "";
    string wordOfLine = "";
    // Obtain each wordOfLine
    for (size_t i = 0; i < line_input.length(); ++i) 
	{
      letterOfWord = tolower(line_input[i]);
      if(letterOfWord == "\'") 
	  { 
	   //Skip words with apostrophes
       skipApostropheWord = true; 
      }//END IF
      if( letterOfWord>= "a" && letterOfWord <= "z") 
	  {
       wordOfLine += letterOfWord;
      }//END IF
    }//END For loop
   
 /**We must check for our cases:
 
  A). Add a character in every possible position and see if it matches
  
  B). Remove a character from the word then see if it matches
 
  C). Swap adjacent letters (Permute the word) and check if it matches
 
    3i).

		Case-C("word"): 
			- owrd
			- wrod
			- wodr
		Case-C("lwa") 
			-law
 
 These cases are all "Naive" brute force methods
 **/ 

//Case A
// Add a character in every possible position of the word and check for a match
 string changedWord = wordOfLine;
   if ( !skipApostropheWord && !hash_table.Contains(changedWord)) 
   {
       // 1) Add one character in each possible position
       for(size_t i = 0; i < wordOfLine.length() + 1; ++i) 
	   {
			//An interesting way of iterating found online
			//Since a char represents an ascii value, we can
			//just iterate from a through z by iterating
            for (char ch = 'a';ch <= 'z'; ch++) 
			{
				//This function is from the string standard library
				//void insert (iterator i, size_t n, char c);
				//inserts n consecutive copies of character c.
				//Ex:  word -> waord -> wbord -> wcord
                changedWord.insert(i, 1, ch);
                
                if(hash_table.Contains(changedWord)) 
				{
                 cout << wordOfLine << " -> " << changedWord << endl;
                }
				//Reset the changed word so we can continue in the "for loop"
                changedWord = wordOfLine;     
            }
		}
//Case B
// Remove a character in every possible position of the word and check for a match
       for(size_t i = 0; i < wordOfLine.length(); ++i) 
	   {
            //We begin from index 0 and iterate (Deleting a string of size len)
			// string& erase (size_t pos = 0, size_t len = npos);
            changedWord.erase(i,1);
            if(hash_table.Contains(changedWord)) 
			{
              cout << wordOfLine << " -> " << changedWord << endl;
            }
			//Reset the changedWord so we can continue in the "for loop"
            changedWord = wordOfLine; 
		}
//Case C
//Swap a chaarcter from a giiven character in index "i" with "i+1"
       for(size_t i = 0; i < wordOfLine.length() - 1; ++i) 
	   {
            //We begin from index 0 and swap between index "i" and "i+1"
			//Example:
			//std::string s = "03/02";
			//std::swap(s[1], s[4]);
			//This returns s = "02/03"
            swap(changedWord[i], changedWord[i+1]);
            if(hash_table.Contains(changedWord)) 
			{
               cout << wordOfLine << " -> " << changedWord << endl;
            }
			//Reset the changed word so we can continue in the "for loop"
            changedWord = wordOfLine; 
	   }//END For Loop
   }//END if statement
	
   skipApostropheWord = false; 
   
  }//END While loop  (AKA END the checking of each word)
 
 
 document_stream.close();
 dictionary_stream.close();
 
}



// Sample main for program spell_check
int main(int argc, char **argv) 
{
  if (argc != 3) 
  {
	//No flag is used here, so I chose doubleHashing because there are less collisions
    cout << "Usage: " << argv[0] << " <document-file> <dictionary-file>" << endl;
    return 0;
  }
  
  const string document_filename(argv[1]);
  const string dictionary_filename(argv[2]);
  
  cout << "Input document filename is " << document_filename << endl;
  cout << "Input dictionary filename is " << dictionary_filename << endl;

  // Call functions implementing the assignment requirements.
  
  HashTableDouble<string> doubleProbeTable;
  FindAndPrintMisspelled(doubleProbeTable, document_filename, dictionary_filename);    

  return 0;
}
