#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

bool ULListStr::empty() const
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}

void ULListStr::push_back(const std::string& val)
{
	// CASE #1: list is empty
  if (size_ == 0) {
		// dynamically allocate new Item to begin list 
    Item* newItem = new Item;
		// set head pointer to new Item
    head_ = newItem;
		// set tail pointer to new Item
    tail_ = newItem;
		// increment list size by 1
    size_++;
		// set new Item's "first" variable to 0 
		newItem->first = 0;
		// set new Item's "last" variable to one after first 
    newItem->last = 1;
		// place given string value in new Item's array at index 0 
    newItem->val[newItem->first] = val; 
		// set new Item's next pointer to NULL (because 1 item in list)
		newItem->next = NULL;
		// set new Item's prev pointer to NULL (because 1 item in list)
		newItem->prev = NULL;
  }
	
  else {
    // CASE #2: last Item is full
    if (tail_->last == ARRSIZE) {
			// dynamically allocate new Item to expand list 
      Item* newItem = new Item;
			// set new Item's "first" variable to 0
			newItem->first = 0;
			// set new Item's "last" variable to one after first 
			newItem->last = 1;
			// place given string value in new Item's array at index 0
			newItem->val[newItem->first] = val;
			// set new Item's prev pointer to tail's current address
      newItem->prev = tail_;
			// set previous Item's next pointer to the new Item's address
			tail_->next = newItem;
      // set tail to point at new Item's address (now last Item of the list)
			tail_ = newItem;
			// increment list size by 1
      size_++;
			// set new Item's next pointer to NULL (now last Item of the list)
      newItem->next = NULL;
    }
		// CASE #3: conventional push_back
    else {
			// indexes into tail pointer's Item's last array position and sets value equal to given val
      tail_->val[tail_->last] = val;
			// increments last Item's "last" variable by 1
      tail_->last++;
			// increments list size by 1
      size_++;
    }
  }
}

void ULListStr::push_front(const std::string& val)
{
	// CASE #1: list is empty 
  if (size_ == 0) {
		// dynamically allocate new Item to begin list 
    Item* newItem = new Item;
		// set head pointer to new Item 
    head_ = newItem;
		// set tail pointer to new Item 
    tail_ = newItem;
		// increment list size by 1
    size_++;
		// set new Item's array to val at 0th index
    newItem->val[newItem->first] = val;
		// increment new Item's last variable by 1 
    newItem->last++;
		// set new Item's prev pointer to NULL (only Item in list)
    newItem->prev = NULL;
		// set new Item's next pointer to NULL (only Item in list)
    newItem->next = NULL;
  }
	
  else {
		// CASE #2: zero-th array of head Item is occupied 
    if (head_->first == 0) {
			// dynamically allocate new array to extend list 
      Item* newItem = new Item;
			// set new Item's next pointer to current address stored in head pointer
      newItem->next = head_;
			// set prev pointer of head's current Item to the new Item  
      head_->prev = newItem;
			// set head pointer to new Item's address which is not the front of the list 
      head_ = newItem;
			// inserting the val at the LAST POSITION of new front Item, 
			//thus new Item's last variable set to size of array
      newItem->last = ARRSIZE;
			// inserting the val at the LAST POSITION of new front Item, 
			//thus new Item's first variable set to size of array minus 1
      newItem->first = ARRSIZE - 1;
			// set last array position of new front Item to val
      newItem->val[newItem->first] = val;
			// increment size list by 1
      size_++;
    }
		// CASE #3: conventional push front 
    else {
      head_->val[head_->first - 1] = val;
      head_->first -= 1;
      size_++;
    }
  }
}

void ULListStr::pop_back()
{
	// returns if list is empty and nothing to pop back 
  if (tail_ == NULL) {
    return;
  }
  
	// creates temporary pointer to point to last Item in list
  Item* temp = tail_;
	
	// CASE #1: when there is a single string in the list 
	if (size_ == 1) {
		// set head and tail pointers to NULL since list is empty 
		head_ = tail_ = NULL;
		// delete dynamically-allocated object which no stores no strings 
		delete temp;
	}
	

	// CASE #2: when popping last element leaves an Item empty 
	else if (temp->last == 1) {
		// set second-to-last Item's next pointer to NULL (now last Item in list)
		temp->prev->next = NULL;
		// set tail pointer to current second-to-last Item (because deleting last empty Item)
		tail_ = temp->prev;
		// delete last item in last that is now empty after popping back 
		delete temp;
	}

	// CASE #3: conventional pop back 
	else {
		// decrement last Item of list's "last" variable by 1 (a.k.a. will overwrite value that popping back)
		tail_->last--;
	}
	
	// decrement list size by 1
  size_--;
}

void ULListStr::pop_front()
{
	// if list is empty, thus nothing to pop, return
  if (size_ == 0) {
    return;
  }

	// create temp Item pointer and point to front of list
  Item* temp = head_;
	
	// CASE #1: popping the one element in list 
	if (size_ == 1) {
		// set head and tail pointers to NULL (since now empty list)
		head_ = tail_ = NULL;
		// delete Item holding no elements 
		delete temp;
	}

	// CASE #2: when deleting front most element leaves an Item empty 
  else if (temp->first == ARRSIZE - 1) {
    // set head pointer to second Item in list (since first is empty now)
		head_ = temp->next;
		// set second Item's previous pointer to NULL (because will now be first Item)
    temp->next->prev = NULL;
		// delete temp a.k.a. now empty Item in front 
    delete temp;
  }

	// CASE#3: conventional pop front 
  else {
		// increase front Item's "first" variable by 1 (essentially to lose/overwrite first string)
    head_->first++;
  }
	
	// decrement list size by 1 since you're popping 
  size_--;
}

std::string const & ULListStr::back() const
{
	// return last Item's value at 1 minus "last" variable index 
   return tail_->val[tail_->last - 1];
}

std::string const & ULListStr::front() const
{
	// return first Item's value at "first" variable index
   return head_->val[head_->first];
}

std::string* ULListStr::getValAtLoc(size_t loc) const
{
	// create new variable for location and set equal to passed-in "loc"
	int newLoc = loc;
	// create new Item pointer that points to front of list
  Item* temp = head_;
	// run while temp is pointing at valid Item in list 
  while (temp != NULL) {
		// calculate difference between temp's first and last values and 
		// check if its less than or equal to newLoc variable 
		if (temp->last - temp->first <= newLoc) {
			// if difference is less than or equal to newLoc variable, subtract
			// difference from newLoc
			newLoc -= (temp->last - temp->first);
			// move temp to point to next Item in list 
			temp = temp->next;
		}
		else {
			// return pointer to value at current temp's array 
			// of index = temp's first variable plus current newLoc variable 
			return &(temp->val[temp->first + newLoc]);
		}
	}
}