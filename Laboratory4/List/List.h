/* LAB ¹4, Second semestr
Creator: Maria Korol, K-11 */

#pragma once
#include <iostream>
#include "Racer.h"

using namespace std;

template <class T> class D_List {
private:
	struct D_Node {
		D_Node(T node_val) : val(node_val) { }
		D_Node() {}
		~D_Node() {}
		D_Node *next;   
		D_Node *prev;   
		T val;                                       
	};
public:
	class iterator
	{
	private:
		friend class D_List<T>;
		D_Node * the_node;
	public:
		iterator() : the_node(0) { }
		iterator(D_Node * dn) : the_node(dn) { }	
		bool operator==(const iterator& other) const
		{
			return (the_node == other.the_node);
		}
		bool operator!=(const iterator& other) const
		{
			return !(other == *this);
		}
		iterator& operator++()
		{
			if (the_node == 0)
				throw "incremented an empty iterator";
			if (the_node->next == 0)
				throw "incremented out of list";
			the_node = the_node->next;
			return *this;
		}
		iterator& operator--()
		{
			if (the_node == 0)
				throw "decremented an empty iterator";
			if (the_node->prev == 0)
				throw "decremented out of list";
			the_node = the_node->prev;
			return *this;
		}
		T& operator*() const
		{
			if (the_node == 0)
				throw "empty iterator";
			return the_node->val;
		}
	};

private:
	D_Node *head;    
	D_Node *tail; //element out of list
	iterator head_iterator;
	iterator tail_iterator;
public:
	D_List()
	{
		head = tail = new D_Node;
		tail->next = 0;
		tail->prev = 0;
		head_iterator = iterator(head);
		tail_iterator = iterator(tail);
	}

	~D_List()
	{
		D_Node *node_to_delete = head;
		for (D_Node *sn = head; sn != tail;)
		{
			sn = sn->next;
			delete node_to_delete;
			node_to_delete = sn;
		}
		delete node_to_delete;
	}
	bool is_empty() { return head == tail; }
	iterator front() { return head_iterator; }
	iterator rear() { return tail_iterator; }

	//adding new element before head
	void add_front(T node_val)
	{
		D_Node *node_to_add = new D_Node(node_val);
		node_to_add->next = head;
		node_to_add->prev = 0;
		head->prev = node_to_add;
		head = node_to_add;
		head_iterator = iterator(head);
	}

	// adding new element after head
	void add_rear(T node_val)
	{
		if (is_empty()) add_front(node_val);
		else
			/* not for empty list, cause, tail->prev = nullptr,
			 so tail->prev->next has no sence */
		{
			D_Node *node_to_add = new D_Node(node_val);
			node_to_add->next = tail;
			node_to_add->prev = tail->prev;
			tail->prev->next = node_to_add;
			tail->prev = node_to_add;
			tail_iterator = iterator(tail);

		}
	}
	bool delete_node(iterator & key_i)
	{
		for (D_Node *dn = head; dn != tail; dn = dn->next)
			if (dn == key_i.the_node)    //find node to delete
			{
				dn->prev->next = dn->next;
				dn->next->prev = dn->prev;
				delete dn;                            
				key_i.the_node = 0;
				return true;
			}
		return false;
	}
	// searching iterator by node data
	iterator findFirst(T node_val) const
	{
		for (D_Node *dn = head; dn != tail; dn = dn->next)
			if (dn->val == node_val) return iterator(dn);
		return tail_iterator;
	}
	int size() const
	{
		int count = 0;
		for (D_Node *dn = head; dn != tail; dn = dn->next) ++count;
		return count;
	} 
	// fuction of buble ascending sorting 
	void bubbleSorting()
	{
		for (D_Node *node = head; node!=tail; node = node->next)
			for (D_Node *node1 = head; node1!=tail; node1 = node1->next)
				if (node->val < node1->val) { 
					T x = node->val;
					node->val = node1->val;
					node1->val = x;
				}

	}

};

/* Container of Racing, using class Racing from Racer.h 
** added an utility function to find object in container 
** and a fuction, which shows object's data */

class RacingContainer :public D_List <Racing> {
public:
	void addToContainer(int stage_, int startNumber_, int place_, string name_, string surname_, double timeOfDistance_,
		double firstFrontierIn_, double firstFrontierOut_, double secondFrontierIn_, double secondFrontierOut_, int missingShots_) {
		Racing *race_ = nullptr;
		race_ = new Racing(stage_, startNumber_, place_, name_, surname_, timeOfDistance_, firstFrontierIn_, firstFrontierOut_, secondFrontierIn_,
			secondFrontierOut_, missingShots_);
		D_List<Racing>::add_rear(*race_);
		delete race_;
	}
	//searching first racing in the list from specified position
	iterator& findRacing(const iterator it, const string name_, const string surname_) {
		for (iterator i = it; i != rear(); ++i)
			if (i.operator*().getName() == name_ && i.operator*().getSurname() == surname_) return i;
	}
	void show() {
		for (iterator i = front(); i != rear(); ++i)
			cout << i.operator*().info() << endl;
	}

};