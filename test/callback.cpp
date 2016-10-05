


#include <iostream>
#include <stdio.h>

// Define callback signature.
typedef void (*DoneCallback )(int reason, const char *explanation);

// A method that takes a callback as argument.
void doSomeWorkWithCallback(DoneCallback done)
{
	if (done)
	{
		done(1, "Finished");
	}
}

// A callback
void myCallback(int reason , const char *explanation)
{
	printf(" Callback called with reason %d: %s\n", reason, explanation);
}

int main(int argc, char* argv[])
{
	doSomeWorkWithCallback(myCallback);
	return 0 ;
}


