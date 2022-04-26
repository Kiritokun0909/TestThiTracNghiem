#include <iostream>
#pragma once
template <class T>
struct Node
{
	T data;
	Node* next = nullptr;

	Node() : data(NULL) {};
	Node(T _data) : data(_data) {};
};

template<class T>
class LinkedList
{
private:
	Node<T>* head;
	int size = 0;
	int DeleteNode(Node<T>*& prevNode, Node<T>*& currNode)// currNode : Node need to be deleted;
	{
		if (prevNode == currNode && prevNode == head)
		{
			if (head == NULL || size == 0)
				return 0;
			Node<T>* p = head;
			head = p->next;
			delete p;
			size--;

			prevNode = head;
			return 1;
		}
		else
		{
			size--;
			prevNode->next = currNode->next;
			delete currNode;
			return 1;
		}
	}
	// previousNode, deleteNode

#pragma region SortAlgorithm
	Node<T>* midNode(Node<T>* head)
	{
		Node<T>* slow = head;
		Node<T>* fast = head->next;
		while (slow != NULL && (fast != NULL && fast->next != NULL))
		{
			slow = slow->next;
			fast = fast->next->next;
		}
		return slow;
	};

	Node<T>* Merge(Node<T>*& head1, Node<T>*& head2, bool(*cmp)(T, T))
	{
		Node<T>* tempHead;
		Node<T>* loop = new Node<T>(head1 != NULL ? head1->data : head2->data);
		tempHead = loop;
		while (head1 != NULL && head2 != NULL)
		{
			if (cmp(head1->data, head2->data))
			{
				loop->next = head1;
				head1 = head1->next;
			}
			else
			{
				loop->next = head2;
				head2 = head2->next;
			}
			loop = loop->next;
		}
		while (head1 != NULL)
		{
			loop->next = head1;
			head1 = head1->next;
			loop = loop->next;
		}
		while (head2 != NULL)
		{
			loop->next = head2;
			head2 = head2->next;
			loop = loop->next;
		}

		return tempHead->next;
	}

	Node<T>* MergeSort(Node<T>*& head, bool (*cmp)(T, T))
	{
		if (head == NULL || head->next == NULL)
			return head;

		Node<T>* mid = midNode(head);
		Node<T>* head2 = mid->next;
		mid->next = NULL;

		head = MergeSort(head, cmp);
		head2 = MergeSort(head2, cmp);

		Node<T>* finalRes = Merge(head, head2, cmp);
		return finalRes;
	}
#pragma endregion
public:
	LinkedList()
	{
		head = nullptr;
		size = 0;
	}
	LinkedList(T _data)
	{
		head = new Node<T>(_data);
		size = 1;
	}
	~LinkedList() {};

	int getSize() { return size; }

	int AddNode(T _data)
	{
		Node<T>* newNode = new Node<T>(_data);
		newNode->next = head;
		head = newNode;
		size++;
		return 1;
	}

	Node<T>* GetHead()
	{
		return head;
	}

	template<typename S>
	int DeleteBase(S cmp, bool delAll)
	{
		int count = 0;
		Node<T>* loop = head;
		Node<T>* curr = head;
		Node<T>* prev = head;
		while (loop != NULL)
		{
			if (cmp(loop->data))
			{
				if (!delAll)
					return DeleteNode(prev, curr);
				else
				{
					count += DeleteNode(prev, curr);
					loop = prev;
				}
				curr = loop;
			}
			else
			{
				prev = loop;
				loop = loop->next;
				curr = loop;
			}

		}
		return count;
	} // compare condition / delete all same thing ?
	
	template<typename S>
	Node<T>* FindElement(S cmp)
	{
		Node<T>* loop = head;
		for (int i = 0; i < size; i++)
		{
			if (cmp(loop->data)) return loop;
			loop = loop->next;
		}

		return nullptr;
	} // find element base on condition;

	void Sort(bool (*cmp)(T, T))
	{
		head = MergeSort(head, cmp);
	} // sort base on condition
};

