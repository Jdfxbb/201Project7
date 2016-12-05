#pragma once

template <class N>
struct Node
{
public:
	Node() { next = prev = nullptr; }
	Node(const N& item) { data = item; next = prev = nullptr; }
	N data;
	Node<N> *prev, *next;
};

template <class Q>
class Queue
{
public:
	Queue();
	//PRE: None
	//POST: Queue object initialized
	//RETURNS: None
	Queue(const Queue& other);
	//PRE: other Queue object initialized
	//POST: Queue object initialized with attributes of other
	//RETURNS: None
	~Queue();
	//PRE: Queue object in scope
	//POST: Queue object deleted
	//RETURNS: None
	const Queue<Q>& operator=(const Queue<Q>& rhs);
	//PRE: rhs Queue object initialized
	//POST: this object = rhs 
	//RETURNS: this object
	void push_back(const Q& item);
	//PRE: None
	//POST: item is added to end of queue
	//RETURNS: None
	Q pop();
	//PRE: at least one item in queue
	//POST: first item removed from queue
	//RETURNS: first item in Queue (Q type)
	bool isEmpty();
	//PRE: None
	//POST: None
	//RETURNS: true if queue is empty
private:
	Node<Q> *head, *tail;
	int count;
};

template <class Q>
Queue<Q>::Queue()
{
	head = tail = nullptr;
	count = 0;
}

template <class Q>
Queue<Q>::Queue(const Queue& other)
{
	if (!isEmpty())
	{
		//if queue is not empty, clear queue
		for (int i = 0; i < count; i++)
		{
			pop();
		}
	}

	head = tail = nullptr;
	Node<Q> *itr = other.head;
	// iterate through other queu and push_back each item
	while (itr != nullptr)
	{
		push_back(itr->data);
		itr = itr->next;
	}
}

template <class Q>
Queue<Q>::~Queue()
{
	if (!isEmpty())
	{
		for (int i = 0; i < count; i++)
		{
			pop();
		}
	}
}

template <class Q>
const Queue<Q>& Queue<Q>::operator=(const Queue<Q>& rhs)
{
	if (this != &rhs)
	{
		if (!isEmpty())
		{
			for (int i = 0; i < count; i++)
			{
				pop();
			}
			head = tail = nullptr;
		}
		Node<Q> *itr = rhs.head;
		while (itr != nullptr)
		{
			push_back(itr->data);
			itr = itr->next;
		}
	}
	return *this;
}

template <class Q>
void Queue<Q>::push_back(const Q& item)
{
	if (isEmpty())
	{
		// first object in queue, head and tail point to it
		head = new Node<Q>(item); 
		tail = head;
		count++;
	}
	else
	{
		// create new node at end of queue
		tail->next = new Node<Q>(item);
		tail->next->prev = tail;
		tail = tail->next;
		count++;
	}
}

template <class Q>
Q Queue<Q>::pop()
{
	if (isEmpty())
	{
		cerr << "Queue is empty, no item to pop";
	}
	else
	{
		Q temp = head->data;
		Node<Q> *tempP = head;

		if (count > 1)
		{
			head = head->next;
			head->prev = nullptr;
		}
		// check if this is the last item
		if (count == 0)
			head = tail = nullptr;
		delete tempP;
		count--;
		return temp;
	}
}

template <class Q>
bool Queue<Q>::isEmpty()
{
	return count < 1;
}