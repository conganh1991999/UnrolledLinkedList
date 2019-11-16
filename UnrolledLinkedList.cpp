#include"UnrolledLinkedList.h"

void UnrolledLinkedList::add(int val) {
	// TODO
	if (head == NULL && tail == NULL)
	{
		head = new Node(nodeSize); //head->prev = NULL; head->next = NULL; 
		numOfNodes += 1; //increase number of nodes
		head->add(val); //add value; icrease numElements
		size += 1; //increase size of list
		tail = head; //tail also head
	}
	else
	{
		if(!(tail->isFull()))
		{
			tail->add(val); //add value; icrease numElements
			size += 1; //increase size of list
		}
		else
		{
			Node *newnode = new Node(nodeSize);

			for (int i = tail->getHalfNodeSize(); i < nodeSize; i++)
			{
				//move half of tail's elements to next node
				newnode->elements[newnode->numElements] = tail->elements[i];
				//recounting num of elements
				newnode->numElements += 1;
				tail->numElements -= 1;
			}
			//and then, insert val
			newnode->elements[newnode->numElements] = val;
			newnode->numElements += 1; //increase numElements
			size += 1; //increase size of list
			//update tail
			newnode->prev = tail;
			tail->next = newnode;
			tail = newnode;
			//finally, increase number of nodes
			numOfNodes += 1;
		}
	}
}

int UnrolledLinkedList::getAt(int pos) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	else  // TODO
	{
		Node *hold = head;
		int indexer = 0; int value;
		while (head != NULL)
		{
			for (int i = 0; i < head->numElements; i++)
			{
				if (pos == indexer)
				{
					value = head->elements[i];
					head = hold;
					return value;
				}
				else
					indexer++;
			}
			head = head->next;
		}
		head = hold;
	}
	return 1;
}

void UnrolledLinkedList::setAt(int pos, int val) {
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	else // TODO
	{
		Node *hold = head;
		int index = 0;
		while (head != NULL)
		{
			for (int i = 0; i < head->numElements; i++)
			{
				if (pos == index)
				{
					head->elements[i] = val;
					head = hold;
					return;
				}
				else
					index++;
			}
			head = head->next;
		}
		head = hold;
	}
	return;
}


void UnrolledLinkedList::insertAt(int pos, int val) {
	if (pos < 0 || pos > size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not	
	// TODO
	
	Node *hold = head;
	Node *toInsert = NULL;
	int index = 0;
	
	if ((pos == size)||((head == NULL) && (tail == NULL) && (pos == 0)))
	{
		add(val);
		return;
	}
	else
	{
		while (head != NULL)
		{
			for (int i = 0; i < head->numElements; i++)
			{
				if (pos == index)
				{
					toInsert = head;
					pos = i;
					break;
				}
				else
					index++;
			}
			if (toInsert == head)
				break;
			else
				head = head->next;
		}
		head = hold;
	}
	//inserting at position pos
	if (toInsert->isFull() == false)
	{
		toInsert->insertAt(pos, val);
		size += 1;
		return;
	}
	else
	{
		Node *newnode = new Node(nodeSize);

		if ((nodeSize % 2) == 0)
		{
			for (int i = toInsert->getHalfNodeSize(); i < nodeSize; i++)
			{
				//move half of toInsert's elements to next node
				newnode->elements[newnode->numElements] = toInsert->elements[i];
				//recounting num of elements
				newnode->numElements += 1;
				toInsert->numElements -= 1;
			}

			//and then, insert val
			if (pos < toInsert->numElements)
			{
				toInsert->insertAt(pos, val);
			}
			else
			{
				newnode->insertAt((pos - toInsert->numElements), val);
			}
			size += 1; //increase size of list
		}
		else
		{
			if (pos < toInsert->getHalfNodeSize())
			{
				for (int i = (toInsert->getHalfNodeSize() - 1); i < nodeSize; i++)
				{
					//move half of toInsert's elements to next node
					newnode->elements[newnode->numElements] = toInsert->elements[i];
					//recounting num of elements
					newnode->numElements += 1;
					toInsert->numElements -= 1;
				}
				//and then, insert val
				toInsert->insertAt(pos, val);
				size += 1; //increase size of list
			}
			else
			{
				for (int i = toInsert->getHalfNodeSize(); i < nodeSize; i++)
				{
					//move half of toInsert's elements to next node
					newnode->elements[newnode->numElements] = toInsert->elements[i];
					//recounting num of elements
					newnode->numElements += 1;
					toInsert->numElements -= 1;
				}
				//and then, insert val
				newnode->insertAt((pos - toInsert->numElements), val);
				size += 1; //increase size of list
			}
		}

		//update list
		if (toInsert->next != NULL)
		{
			newnode->prev = toInsert;
			newnode->next = toInsert->next;
			toInsert->next->prev = newnode;
			toInsert->next = newnode;
		}
		else if (toInsert->next == NULL)
		{
			newnode->prev = toInsert;
			newnode->next = toInsert->next;
			toInsert->next = newnode;
			tail = newnode;
		}
		//finally, increase number of nodes
		numOfNodes += 1;
		return;
	}
}

void UnrolledLinkedList::deleteAt(int pos)
{
	if (pos < 0 || pos >= size)
		throw "IndexOutOfBoundsException"; // check whether pos is valid or not
	// TODO
	Node *hold = head;
	Node *toDelete = NULL;
	int index = 0;

	if ((head == NULL) && (tail == NULL) && (pos == 0))
	{
		//throw "Can't delete in a NULL list";
	}
	else
	{
		while (head != NULL)
		{
			for (int i = 0; i < head->numElements; i++)
			{
				if (pos == index)
				{
					toDelete = head;
					pos = i;
					break;
				}
				else
					index++;
			}
			if (toDelete == head)
				break;
			else
				head = head->next;
		}
		head = hold;
	}

	//delete at position pos
	toDelete->removeAt(pos);
	size -= 1;

	//check toDelete
	if (toDelete->isUnderHalfFull() == false)
	{
		return;
	}
	else
	{
		if ((toDelete->next == NULL) && (toDelete->prev == NULL))
		{
			if (size == 0)
			{
				tail = NULL;
				head = NULL;
				numOfNodes = 0;
			}
			return;
		}
		else if ((toDelete->next != NULL) && (toDelete->prev == NULL))
		{
			if (toDelete->next->numElements > toDelete->next->getHalfNodeSize())
			{
				toDelete->add(toDelete->next->elements[0]);
				toDelete->next->removeAt(0);
				return;
			}
			else
			{
				for (int i = 0; i < toDelete->next->numElements; i++)
				{
					toDelete->add(toDelete->next->elements[i]);
				}

				if (toDelete->next->next != NULL)
				{
					Node *del = toDelete->next;
					toDelete->next = toDelete->next->next;
					toDelete->next->prev = toDelete;
					delete del; del = NULL;
					numOfNodes -= 1;
					return;
				}
				else
				{
					Node *del = toDelete->next;
					toDelete->next = NULL;
					tail = head;
					delete del; del = NULL;
					numOfNodes -= 1;
					return;
				}
			}
		}
		else if ((toDelete->next == NULL) && (toDelete->prev != NULL))
		{
			if (toDelete->prev->numElements > toDelete->prev->getHalfNodeSize())
			{
				toDelete->insertAt(0, toDelete->prev->elements[toDelete->prev->numElements - 1]);
				toDelete->prev->removeAt(toDelete->prev->numElements - 1);
				return;
			}
			else
			{
				for (int i = (toDelete->prev->numElements - 1); i >= 0; i--)
				{
					toDelete->insertAt(0, toDelete->prev->elements[i]);
				}

				if (toDelete->prev->prev != NULL)
				{
					Node *del = toDelete->prev;
					toDelete->prev = toDelete->prev->prev;
					toDelete->prev->next = toDelete;
					delete del; del = NULL;
					numOfNodes -= 1;
					return;
				}
				else
				{
					Node *del = toDelete->prev;
					toDelete->prev = NULL;
					head = tail;
					delete del; del = NULL;
					numOfNodes -= 1;
					return;
				}
			}
		}
		else
		{
			if (toDelete->next->numElements > toDelete->next->getHalfNodeSize())
			{
				toDelete->add(toDelete->next->elements[0]);
				toDelete->next->removeAt(0);
				return;
			}
			else if (toDelete->prev->numElements > toDelete->prev->getHalfNodeSize())
			{
				toDelete->insertAt(0, toDelete->prev->elements[toDelete->prev->numElements - 1]);
				toDelete->prev->removeAt(toDelete->prev->numElements - 1);
				return;
			}
			else
			{
				for (int i = 0; i < toDelete->next->numElements; i++)
				{
					toDelete->add(toDelete->next->elements[i]);
				}

				if (toDelete->next == tail)
				{
					Node *del = toDelete->next;
					toDelete->next = NULL;
					tail = toDelete;
					delete del; del = NULL;
					numOfNodes -= 1;
					return;
				}
				else
				{
					Node *del = toDelete->next;
					toDelete->next = toDelete->next->next;
					toDelete->next->prev = toDelete;
					delete del; del = NULL;
					numOfNodes -= 1;
					return;
				}
			}
		}
	}
}

int UnrolledLinkedList::firstIndexOf(int val) {
	Node *hold = head; //holding head
	int index = 0;
	while (head != NULL)
	{
		for (int i = 0; i < head->numElements; i++)
		{
			if (head->elements[i] == val)
			{
				head = hold;
				return index;
			}
			else
				index++;
		}
		head = head->next;
	}
	head = hold;
	return -1;
}

int UnrolledLinkedList::lastIndexOf(int val) {
	Node *hold = tail; //holding head
	int index = size - 1;
	while (tail != NULL)
	{
		for (int i = (tail->numElements - 1); i >= 0; i--)
		{
			if (tail->elements[i] == val)
			{
				tail = hold;
				return index;
			}
			else
				index--;
		}
		tail = tail->prev;
	}
	tail = hold;
	return -1;
}

bool UnrolledLinkedList::contains(int val) {
	// TODO
	Node *hold = head; //holding head
	bool check = false;
	while (head != NULL)
	{
		for (int i = 0; i < head->numElements; i++)
		{
			if (head->elements[i] == val)
			{
				check = true;
				head = hold;
				return check;
			}
		}
		//update head;
		head = head->next;
	}
	head = hold;
	return check;
}

void UnrolledLinkedList::reverse() {
	// TODO
	if (head == NULL)
		return;
	Node *hold = head;
	int *list = toArray();
	int index = size - 1;
	while (head != NULL)
	{
		for (int i = 0; i < head->numElements; i++)
		{
			head->elements[i] = list[index];
			index--;
		}
		head = head->next;
	}
	head = hold;
}

int* UnrolledLinkedList::toArray() {
	// TODO
	//if (head == NULL) //or size == 0
		//print NULL; (handled)
	int *list_numbers = new int[size];
	int index = 0;
	Node *hold = head; //holding head
	while (head != NULL)
	{
		for (int i = 0; i < head->numElements; i++)
		{
			list_numbers[index] = head->elements[i];
			index++;
		}
		//update head;
		head = head->next;
	}
	head = hold;
	return list_numbers;
}