#pragma once
#include <ostream>
template<typename T>
class List
{
	//	Nested Node class
	struct Node
	{
	public:
		T data;
		Node* previous;
		Node* next;
		Node(const T& d = T{}, Node* p = nullptr, Node* n = nullptr)
			: data{ d }, previous{ p }, next{ n } {}
		Node(T&& d, Node* p = nullptr, Node* n = nullptr)
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
		const T& operator*() const;	//	operator*() to return element

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
		T& retrieve() const;	//	retrieve the element refers to
		ConstIterator(Node* p);	//	Protected constructor

		friend class List<T>;
	};
	//	Nested Iterator class
	class Iterator : public ConstIterator
	{
	public:
		Iterator();
		T& operator*();
		const T& operator*() const;

		// increment/decrement operators
		Iterator& operator++();
		Iterator operator++(int);
		Iterator& operator--();
		Iterator operator--(int);

	protected:
		Iterator(Node* p);
		friend class List<T>;
	};

	//	Constructor, destructor, copy constructor
	List();	//	Default zero parameter constructor
	List(const List& other);	//	Copy constructor
	List(List&& rhs);	//	Move constructor
	//	Num elements with value of val
	explicit List(int num, const T& val = T{});
	List(ConstIterator start, ConstIterator end);
	~List();	//	Destructor

	//	Copy assignment operator
	const List& operator=(const List& other);
	//	Move assignment operator
	List& operator=(List&& other);

	// overloading comparison operators
	bool operator==(const List<T>& rhs);
	bool operator!=(const List<T>& rhs);

	// overloading output operator
	std::ostream& operator<<(const List<T>& l);

	//	Member functions
	int count() const; //	Return how many elements exist in the list
	bool empty() const; //	Return a Boolean, true if the list is empty, false otherwise
	void clear(); //	Remove all elements from the list
	void reverse();	//	Reverse the order of the elements

	T& first(); //	Return the first element by value, assert if no elements
	const T& first() const;
	T& last(); //	Return the last element by value, assert if no elements
	const T& last()	const;

	void pushFront(const T& value); //	Add a new value to the front of the list
	void pushFront(T&& value); //	Move version of insert
	void pushBack(const T& value); //	Add a new value to the end of the list
	void pushBack(T&& value); //	Move version of insert
	void popFront(); //	Remove the first element
	void popBack(); //	Remove the last element

	void remove(const T& value); //	Remove all elements with matching value

	//	Print ouut all elements. ofc is deliminator
	void print(std::ostream& os, char ofc = ' ') const;

	Iterator begin(); //	Return an iterator to the first element
	ConstIterator begin() const;
	Iterator end(); //	Return an iterator to a null element
	ConstIterator end() const;
	Iterator insert(Iterator insertPos, const T& value); //	Add a new value ahead of specified iterator location
	Iterator insert(Iterator insertPos, T&& value);	//	Move version of insert
	Iterator erase(Iterator erasePos);	//	Erase one element
	Iterator erase(Iterator start, Iterator end);	//	Erase [start, end)
};

//	Default constructor w/ no parameters
template<typename T>
List<T>::ConstIterator::ConstIterator() : current{ nullptr }
{
}

//	operator* returns the element (to be retrieved later)	(protected)
template<typename T>
const T& List<T>::ConstIterator::operator*() const
{
	return retrieve();
}

//	Operators various
template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()	//	Increment
{
	//	Increment operator, pointer to the next node
	current = current->next;
	return *this;
	//	Returns the derefenced instance of this class
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)	//	++(int) postfix increment
{
	//	Return a copy of the original and then increment the original by one.
	auto copy = *this;
	current = current->next;
	return copy;
}

template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()	// Decrement
{
	current = current->prev;
	return *this;
}

template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)	// --(int) postfix decrement
{
	auto copy = *this;
	current = current->next;
	return copy;
}

//	Comparisons
template<typename T>
bool List<T>::ConstIterator::operator==(const ConstIterator& rhs) const
{
	return current == rhs.current;	// Refer to the same element? ==
}

template<typename T>
bool List<T>::ConstIterator::operator!=(const ConstIterator& rhs) const
{
	return current != rhs.current;	//	They do not refer to the same element? !=
}

// protected constructor
template<typename T>
List<T>::ConstIterator::ConstIterator(typename List<T>::Node* p) : current{ p }
{
}
//friend class List<T>;

//	Nested Iterator class begin, will return a modifiable reference of current Node
template<typename T>
List<T>::Iterator::Iterator()	//	Constructor of derived iterator class
{
}

template<typename T>
T& List<T>::Iterator::operator*()	//	This operator* is the one will return a modifiable reference of the data in current Node
{
	return this->current->data;
}

//	Retrieve the element refers to current node's data
template<typename T>
T& List<T>::ConstIterator::retrieve() const
{
	return current->data;
}

template<typename T>
const T& List<T>::Iterator::operator*() const
{
	return this->retrieve();
}

//	Operators needed again
template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator++()
{
	//	this->current to call base's protected data
	this->current = this->current->next;
	return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator++(int)
{
	auto cpy = *this;
	this->current = this->current->next;
	return cpy;
}

template<typename T>
typename List<T>::Iterator& List<T>::Iterator::operator--()
{
	this->current = this->current->previous;
	return *this;
}

template<typename T>
typename List<T>::Iterator List<T>::Iterator::operator--(int)
{
	auto cpy = *this;
	this->current = this->current->previous;
	return *this;
}

template<typename T>
List<T>::Iterator::Iterator(typename List<T>::Node* p) : List<T>::ConstIterator{ p }
{

}

template<typename T>
List<T>::List()	//	Constructor, no parameter and will call member function
{
	init();	//	Initialization private function
}

template<typename T>
List<T>::~List()	//	Destructor
{
	clear();	//	Housekeeping job, delete elements as needed
	delete head;	//	Head node
	delete tail;	//	Tail node
}

template<typename T>
List<T>::List(const List<T>& rhs)	//	Copy constructor
{
	init();	//	Call function to do the copy need it
	for (auto itr = rhs.begin(); itr != rhs.end(); ++itr)
	{
		push_back(*itr);	//	Move
	}
}

template<typename T>	//	Move constructor
List<T>::List(List<T>&& rhs) : size(rhs.size), head{ rhs.head }, tail{ rhs.tail }
{
	rhs.size = 0;
	rhs.head = nullptr;
	rhs.tail = nullptr;
}

template<typename T>	//	Copy assignment
const List<T>& List<T>::operator=(const List<T>& rhs)
{
	auto copy = rhs;	//	Swap by reference
	std::swap(*this, copy);
	return *this;
}

template<typename T>	//	Move assignment
List<T>& List<T>::operator=(List<T>&& rhs)
{
	init();
	*this = std::move(rhs);
	return *this;
}

template<typename T>
List<T>::List(int num, const T& val)
{
	init();
	int index;
	for (index = 0; index < num; index++)
	{
		pushBack(val);	//	Note: Insert value ahead of iterator
	}
}

template<typename T>	//	Constructor w/ element [start, end)
List<T>::List(typename List<T>::ConstIterator start, typename List<T>::ConstIterator end)
{
	init();
	for (auto itr = start; itr != end; ++itr)
	{
		pushBack(*itr);
	}
}

template<typename T>   // number of elements
int List<T>::count() const
{
	return size;
}

template<typename T>
void List<T>::reverse()	//	To reverse the order of elements if not empty
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

template<typename T>	//	First element
T& List<T>::first()
{
	return *begin();	//	Refence iterator to first element
}

template<typename T>
const T& List<T>::first() const	//	Now, w/ no permission to modify 1st elem.
{
	return *begin();
}

template<typename T>	//	Last element
T& List<T>::last()
{
	return *(--end());
}

template<typename T>	//	Now, w/ no permission to modify last elem.
const T& List<T>::last() const
{
	return *(--end());
}

template<typename T>
void List<T>::pushFront(T&& val)
{
	insert(begin(), std::move(val));
}

//	Insert to the beginning, aka, insert right after Node* head
template<typename T>
void List<T>::pushFront(const T& val)
{
	insert(begin(), val);	//	Insert after Node head
}

template<typename T>
void List<T>::pushBack(T&& val)	//	Move version insert_back
{
	insert(end(), std::move(val));
}

template<typename T>
void List<T>::popFront()	//	Delete first element
{
	erase(begin());
}

template<typename T>
void List<T>::clear()
{
	while (!empty())
	{
		popBack();	// to delete all the elements
	}
}

// insert to the end, alias, insert right before Node* tail
template<typename T>
void List<T>::pushBack(const T& val)
{
	insert(end(), val);
}

template<typename T>
void List<T>::popBack()
{
	erase(--end()); // erase one element, the last one. 
}

template<typename T>
bool List<T>::empty() const
{
	return count() == 0; // ==0  check if list is empty of nodes 
}

template<typename T>
void List<T>::remove(const T& value) // remove all elements with value val
{
	for (auto itr = begin(); itr != end(); )
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

template<typename T>
typename List<T>::Iterator List<T>::begin()
{
	if (!empty()) // check first
	{
		typename List<T>::Iterator itr{ head->next };
		return itr; // begining node (copy)
	}
}

template<typename T>
typename List<T>::ConstIterator List<T>::begin() const
{
	if (!empty())
	{
		typename List<T>::ConstIterator const_itr{ head->next };
		return const_itr;
	}
}

template<typename T>
typename List<T>::Iterator List<T>::end()
{
	typename List<T>::Iterator itr{ tail };
	return itr; // return the end node (copy)
}

template<typename T>
typename List<T>::ConstIterator List<T>::end() const
{
	typename List<T>::ConstIterator const_itr{ tail };
	return const_itr;
}
template<typename T>
typename List<T>::Iterator List<T>::insert(typename List<T>::Iterator itr, const T& val)
{ // pointer "p" is copy of current node
	auto* pointer = itr.current;
	size++;
	auto* newPtr = new List<T>::Node{ val, pointer->previous, pointer };
	pointer->previous->next = newPtr;
	pointer->previous = newPtr;
	typename List<T>::Iterator iter{ newPtr };
	return iter;
}
template<typename T>
typename List<T>::Iterator List<T>::insert(typename List<T>::Iterator itr, T&& val)
{
	auto* pointer = itr.current;
	size++;
	auto* newPtr = new List<T>::Node{ std::move(val), pointer->previous, pointer };
	pointer->previous->next = newPtr;
	pointer->previous = newPtr;
	typename List<T>::Iterator iter{ newPtr };
	return iter;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(typename List<T>::Iterator start, typename List<T>::Iterator end)
{
	for (auto itr = start; itr != end;) // erase from start to end
	{
		itr = erase(itr); //  not including end. Alias, erase [start, end)
	}

	return end;
}

template<typename T>
void List<T>::init()  // init. private function
{
	size = 0;
	head = new Node;
	tail = new Node;
	head->next = tail;
	tail->previous = head;
}

template<typename T>
typename List<T>::Iterator List<T>::erase(typename List<T>::Iterator itr)
{
	// erase one element
	auto* p = itr.current;
	typename List<T>::Iterator value{ p->next };
	p->previous->next = p->next;
	p->next->previous = p->previous;
	delete p;
	size--;
	return value;
}

// overloading comparison
template<typename T>
bool operator!=(const List<T>& lhs, const List<T>& rhs)
{
	return !(lhs == rhs);
}

template<typename T>
bool List<T>::operator==(const List<T>& rhs)
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

template<typename T>
bool List<T>::operator!=(const List<T>& rhs)
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
template<typename T>
std::ostream& operator<<(std::ostream& os, const List<T>& l)
{
	l.print(os);
	return os;
}

//	Print out all elements
template<typename T>
void List<T>::print(std::ostream& os, char ofc) const
{
	for (auto iterator = begin(); iterator != end(); ++iterator)
	{
		os << *iterator << ofc;	//	ofc is the deliminitor
	}
}