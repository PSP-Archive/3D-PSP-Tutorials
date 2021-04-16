#include "UtilObject.h"
#include <stdlib.h>
#include <time.h>

UtilObject* UtilObject::_instance = 0;// initialize pointer

UtilObject* UtilObject::Instance (void) {
    
	if (_instance == 0){  
		_instance = new UtilObject; // create sole instance
    }
    return _instance; // address of sole instance
}

UtilObject::UtilObject(void) { 
    // creation of object
}

UtilObject::~UtilObject(void) {
	// clean up
}

void UtilObject::InitRandomizer() {
	srand(time(NULL));
	sceKernelUtilsMt19937Init(&ctx, time(NULL));
}

int UtilObject::getRandomIntBad(int low, int high) {
	// return a random number between low and high
	return (rand() % (high-low+1)) + low ; 
}

int UtilObject::getRandomIntGood(int low, int high) { 
	// return a random number between low and high using a twister.
	u32 rand_val = sceKernelUtilsMt19937UInt(&ctx);
	rand_val = low + rand_val % (high-low);
	return (int)rand_val;
} 

