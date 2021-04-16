#ifndef UTILOBJECT_H_
#define UTILOBJECT_H_

#include <psputils.h>

class UtilObject {

private:
	static UtilObject* _instance;
protected:
	UtilObject(void);
	UtilObject(const UtilObject&);
	UtilObject& operator= (const UtilObject&);

	SceKernelUtilsMt19937Context ctx;

public:
	static UtilObject* Instance(void);
	~UtilObject(void);
	void InitRandomizer();
	int getRandomIntBad(int low, int high);
	int getRandomIntGood(int low, int high);

};


#endif
