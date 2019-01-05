/*
*Filename: 		dict.h
*Author: 		Jonathan Delgado
*Description: 	Declaration of the dictionary struct including its methods
*				and a declaration for the prototype of a dictionary constructor
*/

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
	void (*set_key_comparator)(Dict *self, bool (*key_comparator)(void *key1, void *key2));
	bool (*__key_comparator__)(void *key1, void *key2);
	
	void (*set_key_to_string)(Dict *self, void (*key_to_string)(void *key, char *string));
	void (*__key_to_string__)(void *key, char *string);

	void (*set_value_to_string)(Dict *self, void (*value_to_string)(void *value, char *string));
	void (*__value_to_string__)(void *value, char *string);
	//General Functionality
	void (*print)(Dict *self);
	//Getters
	int (*capacity)(Dict *self);
	int (*length)(Dict *self);
	bool (*is_empty)(Dict *self);
	bool (*is_full)(Dict *self);
	int (*contains)(Dict *self, void *key);
	void *(*get)(Dict *self, void *key);
	void *(*get_key_by_index)(Dict *self, int index);
	//Setters
	void (*set)(Dict *self, void *key, void *value);
};

/******************************Constructors******************************/
/*
*Function: newDict
*-----------------------------
*Pseudo-constructor function to create a new dictionary.
*
*returns: 	a struct pointer to the newly created dictionary
*/
Dict *newDict(void);