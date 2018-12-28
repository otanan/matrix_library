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

/******************************PROTOTYPES******************************/

/******************************Interfacing******************************/
//Sets the key_comparator in the dictionary, in case a custom one is written
//Analogous to interfaces in Java
static void set_key_comparator(Dict *self, bool (*key_comparator)(void *key1, void *key2));
//Default implemented key_comparator, used to check if a key is in the dictionary
static bool __key_comparator__(void *key1, void *key2);

static void set_key_to_string(Dict *self, void (*key_to_string)(void *key, char *string));
//Default converter for keys to strings
//Default behavior is to convert the address of the pointer pointing to the
//key and value to a string
static void __key_to_string__(void *key, char *string);

static void set_value_to_string(Dict *self, void(*value_to_string)(void *value, char *string));
static void __value_to_string__(void *value, char *string);


/******************************General Functionality******************************/
static void print_dict(Dict *self);
//Hidden helper function used to increase the size of dictionaries
//once they've reached their limit
static void grow(Dict *self);
static void replaceValue(Dict *self, int index, void *value);

/******************************Constructors******************************/
Dict *newDict(void);


/******************************Getters******************************/
static int get_dict_capacity(Dict *self);
static int get_dict_length(Dict *self);
static bool is_empty_dict(Dict *self);
static bool is_full_dict(Dict *self);
//Returns the index (a nonnegative number) of the entry with the same key
//otherwise, returns a negative value if the key is not currently in the dictionary
static int contains(Dict *self, void *key);
//Returns a NULL pointer on failure to find the value with corresponding key
static void *get(Dict *self, void *key);
static void *get_key_by_index(Dict *self, int index);


/******************************Setters******************************/
static void set(Dict *self, void *key, void *value);