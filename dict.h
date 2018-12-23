#include <stdbool.h>

/******************************Structs******************************/
typedef struct Dict Dict;

struct Dict {
	int __capacity__;
	int __length__;

	void **__keys__;
	void **__values__;
	//"METHODS"
	// void (*print)(Dict *self);
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

/******************************General Functionality******************************/
// void __printDict__(Dict *self);
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
void *__get__(Dict *self, void *key);
void *__getKey__(Dict *self, int index);


/******************************Setters******************************/
void __set__(Dict *self, void *key, void *value);