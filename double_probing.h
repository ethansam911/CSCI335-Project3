/**
    Name: Ethan Sam 
	Date: 3/28/2019
	Professor: Ioannis Stamos
	Class: CSCI 335
	
	Header file: double_probing.h
	
	This Hashing Class uses the double probing technique to search 
	for available positions on a hash table
	
	
 Few comments describing the class HashTableDouble
**/
#ifndef DOUBLE_PROBING_H
#define DOUBLE_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>


// We use namespace so that there isn't a naming conflict,
// But I still got naming conflicts anyway?
//Resolve each namespace to a different name or create a file that resolves all the namespaces.
namespace {
// Internal method to test if a positive number is prime.
bool IsPrimeDouble(size_t n) {
  if( n == 2 || n == 3 )
    return true;
  
  if( n == 1 || n % 2 == 0 )
    return false;
  
  for( size_t i = 3; i * i <= n; i += 2 )
    if( n % i == 0 )
      return false;
  
  return true;
}


// Internal method to return a prime number at least as large as n.
int NextPrimeDouble(size_t n) {
  if (n % 2 == 0)
    ++n;  
  while (!IsPrimeDouble(n))
  {	  n += 2;}  
  return n;
}
}

// Quadratic probing implementation.
template <typename HashedObj>
class HashTableDouble 
{
 public:
  enum EntryType {ACTIVE, EMPTY, DELETED};

  explicit HashTableDouble(size_t size = 101) : array_(NextPrimeDouble(size))
    { MakeEmpty(); }
  
  bool Contains(const HashedObj & x) const {
    return IsActive(FindPos(x));
  }
  
  void MakeEmpty() {
    current_size_ = 0;
    for (auto &entry : array_)
      entry.info_ = EMPTY;
  }

  bool Insert(const HashedObj & x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos].element_ = x;
    array_[current_pos].info_ = ACTIVE;
    
    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();    
    return true;
  }
    
  bool Insert(HashedObj && x) {
    // Insert x as active
    size_t current_pos = FindPos(x);
    if (IsActive(current_pos))
      return false;
    
    array_[current_pos] = std::move(x);
    array_[current_pos].info_ = ACTIVE;

    // Rehash; see Section 5.5
    if (++current_size_ > array_.size() / 2)
      Rehash();

    return true;
  }

  bool Remove(const HashedObj & x) {
    size_t current_pos = FindPos(x);
    if (!IsActive(current_pos))
      return false;

    array_[current_pos].info_ = DELETED;
    return true;
  }
  
  void resetNumOfCollisions() 
  {
    number_of_collisions_ = 0;
  }	
  int getNumOfCollisions() 
  {
    return number_of_collisions_;
  }
  int getNumOfElements() 
  {
    return current_size_;
  }
  int getSize() 
  {
    return array_.size();
  }


//PRIVATE VARIABLES HERE
 private:        
  struct HashEntry {
    HashedObj element_;
    EntryType info_;
    
    HashEntry(const HashedObj& e = HashedObj{}, EntryType i = EMPTY)
    :element_{e}, info_{i} { }
    
    HashEntry(HashedObj && e, EntryType i = EMPTY)
    :element_{std::move(e)}, info_{ i } {}
  };
    

  std::vector<HashEntry> array_;
  size_t current_size_;
  
  //In this assignment we are allowed to add mutable
  // That means that the value of number_of_collisions_ can change even in const functions
  // of the class.
  mutable size_t number_of_collisions_;


  bool IsActive(size_t current_pos) const
  { return array_[current_pos].info_ == ACTIVE; }

  size_t FindPos(const HashedObj & x) const {
    //size_t offset = 1;
	//Offset is no longer 1, the new offset is the internalHashSecond (function)
    size_t offset = InternalSecondHash(x);
	size_t current_pos = InternalHash(x);  
    while (array_[current_pos].info_ != EMPTY && array_[current_pos].element_ != x) 
	{
	  //Entering this while loop means that a collision has occured
	  //Therefore we increment the number of the collisions (Mutable)
	  number_of_collisions_++;
      current_pos += offset; 
	  //Previous Implementation for quadratic, but we care about double hashing
      //offset += 2;
      if (current_pos >= array_.size())
	current_pos -= array_.size();
    }
    return current_pos;
  }

  void Rehash() {
    std::vector<HashEntry> old_array = array_;

    // Create new double-sized, empty table.
    array_.resize(NextPrimeDouble(2 * old_array.size()));
    for (auto & entry : array_)
      entry.info_ = EMPTY;
    
    // Copy table over.
    current_size_ = 0;
    for (auto & entry :old_array)
      if (entry.info_ == ACTIVE)
	Insert(std::move(entry.element_));
  }
  
  size_t InternalHash(const HashedObj & x) const 
  {
    static std::hash<HashedObj > hf;
    return hf(x) % array_.size();
  }
  //This is a reproduction of the Internal Hash 
  size_t InternalSecondHash(const HashedObj & x) const 
  {
    //  static local variable is initialized only once 
    // no matter how many times the function in which it resides 
	//is called and its value is retained and accessible through 
	// many calls to the function 
    static std::hash<HashedObj> hf;
	//The number 191 was chosen with rehashing in mind,
	//the initial size of the hash table was 101; 202 would be even
    //Therefore, the closest prime below 202 is 199 to gurantee a unique position
    return (199 - ( hf(x) )  % 199) % array_.size();
  }
};

#endif  // DOUBLE_PROBING_H
