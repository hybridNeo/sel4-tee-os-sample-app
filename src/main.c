/*
 *  @Author : Rahul Mahadev (hybridNeo)
 *  Hello world app 
 */


#include "tee_internal_api.h"
#include "config.h"
#include <string.h>

/* constants */
int main(int argc, char **argv) {
    printf("ta: TA has started.\n");
	init();
	
	return 0;
}

//sample function
int increment(int i){
	return i++;
}
void encrypt(char *arr){
	int key = 2;
	int len = strlen(arr);
	for(int i=0;i < len;++i){
		arr[i] += key;
	}
}

//Every ta must have a function handler.
tee_result function_handler(int msg, int func_id ,seL4_Word* param_arr,int length){
	if(func_id == HELLO_TA_INCREMENT ){
		char *temp = (char *)param_arr;
		// int arr[5] = {12,34,4,45,55};
		return tee_make_result(increment(msg),NULL,0);
	}
	else if(func_id == HELLO_TA_ENCRYPT){
		char *temp = (char *)param_arr;
		// printf("passed string parameter: %s \n",temp);
        encrypt(temp);
		return tee_make_result(0,temp,length * sizeof(seL4_Word));   
	}
	else{
		return tee_ta_failure();
	}
}
