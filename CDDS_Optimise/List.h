#pragma once
#include <ostream>
template<typename Value>
class List
{
	//	Nested Node class
	struct Node
	{
	public:
		Value data;
		Node* previous;
		Node* next;
		Node(const Value& d = Value{}, Node* p = nullptr, Node* n = nullptr)
			: data{ d }, previous{ p }, next{ n } {}
		Node(Value&& d, Node* p = nullptr, Node* n = nullptr)
			: data{ std::move(d) }, previous{ p }, next{ n } {}
	};
	int size;
	Node* head;
	Node* tail;
	void init();	//	Initializations

public:
	//	Nested Constant Iterator class
	class ConstIterator
	{
	public:

		ConstIterator(); //	Default zero parameter constructor
		const Value& operator*() const;	//	operator*() to return element

		//	Increment/Decrement operators
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);

		//	Comparison operators
		bool operator==(const ConstIterator& rhs) const;
		bool operator!=(const ConstIterator& rhs) const;
	protected:
		Node* current; // pointer to node in List
		Value& retrieve() const;	//	retrieve the element refers to
		ConstIterator(Node* p);	//	Protected constructor

		friend class List<Value>;
	};

	//	Nested Iterator class
	class Iterator : public ConstIterator
	{
	public:
		Iterator();
		Value& operator*();
		const Value& operator*() const;

		// increment/decrement operators
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);

	protected:
		Iterator(Node* p);
		friend class List<Value>;
	};

	//	Constructor, destructor, copy constructor
	List();	//	Default zero parameter constructor
	List(const List& other);	//	Copy constructor
	List(List&& rhs);	//	Move constructor
	//	Num elements with value of val
	explicit List(int num, const Value& val = Value{});
	List(ConstIterator start, ConstIterator end);
	~List();	//	Destructor

	//	Copy assignment operator
	const List& operator=(const List& other);
	//	Move assignment operator
	List& operator=(List&& other);

	// overloading comparison operators
	bool operator==(const List<Value>& rhs);
	bool operator!=(const List<Value>& rhs);

	// overloading output operator
	std::ostream& operator<<(const List<Value>& l);

	//	Member functions
	int count() const; //	Return how many elements exist in the list
	bool empty() const; //	Return a Boolean, true if the list is empty, false otherwise
	void clear(); //	Remove all elements from the list
	void reverse();	//	Reverse the order of the elements

	Value& first(); //	Return the first element by value, assert if no elements
	const Value& first() const;
	Value& last(); //	Return the last element by value, assert if no elements
	const Value& last()	const;

	void pushFront(const Value& value); //	Add a new value to the front of the list
	void pushFront(Value&& value); //	Move version of insert
	void pushBack(const Value& value); //	Add a new value to the end of the list
	void pushBack(Value&& value); //	Move version of insert
	void popFront(); //	Remove the first element
	void popBack(); //	Remove the last element

	void remove(const Value& value); //	Remove all elements with matching value

	//	Print ouut all elements. ofc is deliminator
	void print(std::ostream& os, char ofc = ' ') const;

	Iterator begin(); //	Return an iterator to the first element
	ConstIterator begin() const;
	Iterator end(); //	Return an iterator to a null element
	ConstIterator end() const;
	Iterator insert(Iterator insertPos, const Value& value); //	Add a new value ahead of specified iterator location
	Iterator insert(Iterator insertPos, Value&& value);	//	Move version of insert
	Iterator erase(Iterator erasePos);	//	Erase one element
	Iterator erase(Iterator start, Iterator end);	//	Erase [start, end)
};

//	Default constructor w/ no parameters
template<typename Value>
List<Value>::ConstIterator::ConstIterator() : current{ nullptr }
{

}

//	operator* returns the element (to be retrieved later)	(protected)
template<typename Value>
const Value& List<Value>::ConstIterator::operator*() const
{
	return retrieve();
}

//	Operators various
template<typename Value>
typename List<Value>::ConstIterator& List<Value>::ConstIterator::operator++()	//	Increment
{
	//	Increment operator, pointer to the next node
	current = current->next;
	return *this;
	//	Returns the derefenced instance of this class
}

template<typename Value>
typename List<Value>::ConstIterator List<Value>::ConstIterator::operator++(int)	//	++(int) postfix increment
{
	//	Return a copy of the original and then increment the original by one.
	auto copy = *this;
	current = current->next;
	return copy;
}

template<typename Value>
typename List<Value>::ConstIterator& List<Value>::ConstIterator::operator--()	// Decrement
{
	current = current->prev;
	return *this;
}

template<typename Value>
typename List<Value>::ConstIterator List<Value>::ConstIterator::operator--(int)	// --(int) postfix decrement
{
	auto copy = *this;
	current = current->next;
	return copy;
}

//	Comparisons
template<typename Value>
bool List<Value>::ConstIterator::operator==(const ConstIterator& rhs) const
{
	return current == rhs.current;	// Refer to the same element? ==
}

template<typename Value>
bool List<Value>::ConstIterator::operator!=(const ConstIterator& rhs) const
{
	return current != rhs.current;	//	They do not refer to the same element? !=
}

// protected constructor
template<typename Value>
List<Value>::ConstIterator::ConstIterator(typename List<Value>::Node* p) : current{ p }
{
}

//	Nested Iterator class begin, will return a modifiable reference of current Node
template<typename Value>
List<Value>::Iterator::Iterator()	//	Constructor of derived iterator class
{
}

template<typename Value>
Value& List<Value>::Iterator::operator*()	//	This operator* is the one will return a modifiable reference of the data in current Node
{
	return this->current->data;
}

//	Retrieve the element refers to current node's data
template<typename Value>
Value& List<Value>::ConstIterator::retrieve() const
{
	return current->data;
}

template<typename Value>
const Value& List<Value>::Iterator::operator*() const
{
	return this->retrieve();
}

//	Operators needed again
template<typename Value>
typename List<Value>::Iterator& List<Value>::Iterator::operator++()
{
	//	this->current to call base's protected data
	this->current = this->current->next;
	return *this;
}

template<typename Value>
typename List<Value>::Iterator List<Value>::Iterator::operator++(int)
{
	auto cpy = *this;
	this->current = this->current->next;
	return cpy;
}

template<typename Value>
typename List<Value>::Iterator& List<Value>::Iterator::operator--()
{
	this->current = this->current->previous;
	return *this;
}

template<typename Value>
typename List<Value>::Iterator List<Value>::Iterator::operator--(int)
{
	auto cpy = *this;
	this->current = this->current->previous;
	return *this;
}

template<typename Value>
List<Value>::Iterator::Iterator(typename List<Value>::Node* p) : List<Value>::ConstIterator{ p }
{

}

template<typename Value>
List<Value>::List()	//	Constructor, no parameter and will call member function
{
	init();	//	Initialization private function
}

template<typename Value>
List<Value>::~List()	//	Destructor
{
	clear();	//	Housekeeping job, delete elements as needed
	delete head;	//	Head node
	delete tail;	//	Tail node
}

template<typename Value>
List<Value>::List(const List<Value>& rhs)	//	Copy constructor
{
	init();	//	Call function to do the copy need it
	for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
	{
		push_back(*itr);	//	Move
	}
}

template<typename Value>	//	Move constructor
List<Value>::List(List<Value>&& rhs) : size(rhs.size), head{ rhs.head }, tail{ rhs.tail }
{
	rhs.size = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template<typename Value>	//	Copy assignment
const List<Value>& List<Value>::operator=(const List<Value>& rhs)
{
	auto copy = rhs;	//	Swap by reference
	std::swap(*this, copy);
	return *this;
}

template<typename Value>	//	Move assignment
List<Value>& List<Value>::operator=(List<Value>&& rhs)
{
	init();
	*this = std::move(rhs);
	return *this;
}

template<typename Value>
List<Value>::List(int num, const Value& val)
{
	init();
	int index;
	for (index = 0; index < num; index++)
	{
		pushBack(val);	//	Note: Insert value ahead of iterator
	}
}

template<typename Value>	//	Constructor w/ element [start, end)
List<Value>::List(typename List<Value>::ConstIterator start, typename List<Value>::ConstIterator end)
{
	init();
	for (auto itr = start; itr != end; ++itr)
	{
		pushBack(*itr);
	}
}

template<typename Value>   // number of elements
int List<Value>::count() const
{
	return size;
}

template<typename Value>
void List<Value>::reverse()	//	To reverse the order of elements if not empty
{
	if (!empty())	//	Check to be valid 
	{
		auto currentPtr = head;
		while (currentPtr != nullptr)
		{
			std::swap(currentPtr->next, currentPtr->previous);
			currentPtr = currentPtr->previous;
		}
	}
	std::swap(head, tail);
}

template<typename Value>	//	First element
Value& List<Value>::first()
{
	return *begin();	//	Refence iterator to first element
}

template<typename Value>
const Value& List<Value>::first() const	//	Now, w/ no permission to modify 1st elem.
{
	return *begin();
}

template<typename Value>	//	Last element
Value& List<Value>::last()
{
	return *(--end());
}

template<typename Value>	//	Now, w/ no permission to modify last elem.
const Value& List<Value>::last() const
{
	return *(--end());
}

template<typename Value>
void List<Value>::pushFront(Value&& val)
{
	insert(begin(), std::move(val));
}

//	Insert to the beginning, aka, insert right after Node* head
template<typename Value>
void List<Value>::pushFront(const Value& val)
{
	insert(begin(), val);	//	Insert after Node head
}

template<typename Value>
void List<Value>::pushBack(Value&& val)	//	Move version insert_back
{
	insert(end(), std::move(val));
}

template<typename Value>
void List<Value>::popFront()	//	Delete first element
{
	erase(begin());
}

template<typename Value>
void List<Value>::clear()
{
	while (!empty())
	{
		popBack();	// to delete all the elements
	}
}

// insert to the end, alias, insert right before Node* tail
template<typename Value>
void List<Value>::pushBack(const Value& val)
{
	insert(end(), val);
}

template<typename Value>
void List<Value>::popBack()
{
	erase(--end()); // erase one element, the last one. 
}

template<typename Value>
bool List<Value>::empty() const
{
	return count() == 0; // ==0  check if list is empty of nodes 
}

template<typename Value>
void List<Value>::remove(const Value& value) // remove all elements with value val
{
	for (auto itr = begin(); itr != end();)
	{
		if (*itr == value)
		{
			itr = erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

template<typename Value>
typename List<Value>::Iterator List<Value>::begin()
{
	if (!empty()) // check first
	{
		typename List<Value>::Iterator itr{ head->next };
		return itr; // begining node (copy)
	}
}

template<typename Value>
typename List<Value>::ConstIterator List<Value>::begin() const
{
	if (!empty())
	{
		typename List<Value>::ConstIterator const_itr{ head->next };
		return const_itr;
	}
}

template<typename Value>
typename List<Value>::Iterator List<Value>::end()
{
	typename List<Value>::Iterator itr{ tail };
	return itr; // return the end node (copy)
}

template<typename Value>
typename List<Value>::ConstIterator List<Value>::end() const
{
	typename List<Value>::ConstIterator const_itr{ tail };
	return const_itr;
}
template<typename Value>
typename List<Value>::Iterator List<Value>::insert(typename List<Value>::Iterator itr, const Value& val)
{ // pointer "p" is copy of current node
	auto* pointer = itr.current;
	size++;
	auto* newPtr = new List<Value>::Node{ val, pointer->previous, pointer };
	pointer->previous->next = newPtr;
	pointer->previous = newPtr;
	typename List<Value>::Iterator iter{ newPtr };
	return iter;
}
template<typename Value>
typename List<Value>::Iterator List<Value>::insert(typename List<Value>::Iterator itr, Value&& val)
{
	auto* pointer = itr.current;
	size++;
	auto* newPtr = new List<Value>::Node{ std::move(val), pointer->previous, pointer };
	pointer->previous->next = newPtr;
	pointer->previous = newPtr;
	typename List<Value>::Iterator iter{ newPtr };
	return iter;
}

template<typename Value>
typename List<Value>::Iterator List<Value>::erase(typename List<Value>::Iterator start, typename List<Value>::Iterator end)
{
	for (auto itr = start; itr != end;) // erase from start to end
	{
		itr = erase(itr); //  not including end. Alias, erase [start, end)
	}

	return end;
}

template<typename Value>
void List<Value>::init()  // init. private function
{
	size = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->previous = head;
}

template<typename Value>
typename List<Value>::Iterator List<Value>::erase(typename List<Value>::Iterator itr)
{
	// erase one element
	auto* p = itr.current;
	typename List<Value>::Iterator value{ p->next };
	p->previous->next = p->next;
	p->next->previous = p->previous;
	delete p;
	size--;
	return value;
}

// overloading comparison
template<typename Value>
bool operator!=(const List<Value>& lhs, const List<Value>& rhs)
{
	return !(lhs == rhs);
}

template<typename Value>
bool List<Value>::operator==(const List<Value>& rhs)
{
	bool flag = true;
	if (count() == rhs.count())
	{
		auto rhs_itr = rhs.begin();
		for (auto lhs_itr = begin(); lhs_itr != end(); ++lhs_itr)
		{
			if (*lhs_itr != *rhs_itr)
				flag = false; break;
			++rhs_itr;
		}
		return flag;
	}
	else
		return false;
}

template<typename Value>
bool List<Value>::operator!=(const List<Value>& rhs)
{
	bool flag = false;
	if (count() == rhs.count())
	{
		auto rhs_itr = rhs.begin();
		for (auto lhs_itr = begin(); lhs_itr != end(); ++lhs_itr)
		{
			if (*lhs_itr != *rhs_itr)
				flag = true; break;
			++rhs_itr;
		}
		return flag;
	}
	else
		return true;
}

//	Overloading output
template<typename Value>
std::ostream& operator<<(std::ostream& os, const List<Value>& l)
{
	l.print(os);
	return os;
}

//	Print out all elements
template<typename Value>
void List<Value>::print(std::ostream& os, char ofc) const
{
	for (auto iterator = begin(); iterator != end(); ++iterator)
	{
		os << *iterator << ofc;	//	ofc is the deliminitor
	}
}