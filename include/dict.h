#include <stdbool.h>

/******************************Structs******************************/
typedef struct Dict Dict;

struct Dict {
	int __capacity__;
	int __length__;

	void **__keys__;
	void **__values__;
	//"METHODS"
	//Interfacing
	void (*setKeyComparator)(Dict *self, bool (*__keyComparator__)(void *key1, void *key2));
	bool (*__keyComparator__)(void *key1, void *key2);
	
	void (*setKeyToString)(Dict *self, void (*__keyToString__)(void *key, char *string));
	void (*__keyToString__)(void *key, char *string);

	void (*setValueToString)(Dict *self, void (*__valueToString__)(void *value, char *string));
	void (*__valueToString__)(void *value, char *string);
	//General Functionality
	void (*print)(Dict *self);
	//Getters
	int (*capacity)(Dict *self);
	int (*length)(Dict *self);
	bool (*isEmpty)(Dict *self);
	bool (*isFull)(Dict *self);
	int (*contains)(Dict *self, void *key);
	void *(*get)(Dict *self, void *key);
	void *(*getKey)(Dict *self, int index);
	//Setters
	void (*set)(Dict *self, void *key, void *value);
};

/******************************PROTOTYPES******************************/

/******************************Interfacing******************************/
//Sets the __keyComparator__ in the dictionary, in case a custom one is written
//Analogous to interfaces in Java
void __setKeyComparator__(Dict *self, bool (*__keyComparator__)(void *key1, void *key2));
//Default implemented keyComparator, used to check if a key is in the dictionary
bool __keyComparator__(void *key1, void *key2);

void __setKeyToString__(Dict *self, void (*__keyToString__)(void *key, char *string));
//Default converter for keys to strings
//Default behavior is to convert the address of the pointer pointing to the
//key and value to a string
void __keyToString__(void *key, char *string);

void __setValueToString__(Dict *self, void(*__valueToString__)(void *value, char *string));
void __valueToString__(void *value, char *string);


/******************************General Functionality******************************/
void __printDict__(Dict *self);
//Hidden helper function used to increase the size of dictionaries
//once they've reached their limit
void __grow__(Dict *self);
void __replace__(Dict *self, int index, void *value);

/******************************Constructors******************************/
Dict *newDict(void);


/******************************Getters******************************/
int __getDictCapacity__(Dict *self);
int __getDictLength__(Dict *self);
bool __isEmptyDict__(Dict *self);
bool __isFullDict__(Dict *self);
//Returns the index (a nonnegative number) of the entry with the same key
//otherwise, returns a negative value if the key is not currently in the dictionary
int __contains__(Dict *self, void *key);
//Returns a NULL pointer on failure to find the value with corresponding key
void *__get__(Dict *self, void *key);
void *__getKey__(Dict *self, int index);


/******************************Setters******************************/
void __set__(Dict *self, void *key, void *value);