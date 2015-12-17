#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    sleep(10);  //sleel a bit

    //then become a zombie  

	if(fork() != 0)
	{
        //father doesn't capture child death
		while(1)
        {
            sleep(1);    
        }
	}
	
	
	return 0;
}
