#include <cstdint>
#include <iostream>

// This line is evil, but we'll do it anyway
using namespace std;

struct DLL {
	DLL *prev, *next;
	uint32_t value;
};

// Add a new entry after the given one, with the given value.
// Returns the new entry.
DLL *insert(DLL *entry, uint32_t value)
{
	DLL *newEntry = new DLL();
	newEntry->value = value;

	// Reassign pointers
	entry->next = newEntry;
	newEntry->prev = entry;
	entry->next->prev = newEntry;
	newEntry->next = entry->next;
	return newEntry;
}

// Remove an entry from the list, and return its value
// If the entry isn't in the list, do nothing.
// Don't worry about freeing memory.
uint32_t remove(DLL *entry)
{
	entry->prev->next = entry->next;
	entry->next->prev = entry->prev;
	return entry->value;
}

int main()
{
	// Create a new list, with one entry, with value 6
	DLL *first = new DLL();
	first->value = 6;

	/* Let's add some more, making a chain */
	DLL *second = insert(first, 7);
	DLL *third = insert(first, 8);
	DLL *fourth = insert(first, 9);

	// What does the list look like now?
	DLL *list = first;
	cout << list->value << endl;
	list = list->next;
	cout << list->value << endl;
	list = list->next;
	cout << list->value << endl;
	list = first->next;
	cout << list->value << endl;

	// Let's delete 9, 7 ate it.
	uint32_t deletedValue = remove(fourth);
	cout << "Deleted " << deletedValue << "!" << endl;

	// Let's delete 9, 7 ate it again.
	deletedValue = remove(fourth);
	cout << "Deleted " << deletedValue << "!" << endl;

	// Let's delete 7, it's too lucky for us.
	deletedValue = remove(second);
	cout << "Deleted " << deletedValue << "!" << endl;

	// Let's delete the whole list, I never wanted it anyway.
	remove(third);
	remove(first);

	return 0;
}
