/*
 *  @Author : Rahul Mahadev (hybridNeo)
 *  Hello world app 
 */


#include "tee_internal_api.h"
#include "config.h"


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


//Every ta must have a function handler.
tee_result function_handler(int msg, int func_id ){
    if(func_id == HELLO_TA_INCREMENT ){
        return tee_make_result(increment(msg));
    }else{
        return tee_ta_failure();
    }
}
