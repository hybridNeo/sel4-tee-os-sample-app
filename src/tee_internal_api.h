/*
 *  @Author : Rahul Mahadev (hybridNeo)
 *  Starting point for tee-os
 */
#include <stdio.h>
#include <assert.h>
#include <sel4/sel4.h>

/*
 * Must be overriden by the ta
 */
typedef struct {
	int ret_val;
	int status;
	void *data;
	size_t size;
}tee_result;
#define EP_CPTR 0x5 // where the cap for the endpoint was placed.
extern tee_result function_handler(int msg,int func_id,seL4_Word* arr,int length);
tee_result tee_make_result(int,void*,size_t);
tee_result tee_ta_failure();
void init();
