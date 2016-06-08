/*
 *  @Author : Rahul Mahadev (hybridNeo)
 *  Starting point for tee-os
 */
#include "tee_internal_api.h"
 void init(){
 	while(1){
 		seL4_Word sender_badge;
	    seL4_MessageInfo_t tag;
	    seL4_Word msg,func_id;
	    printf("receiver...........\n");
	 	tag = seL4_Recv(EP_CPTR,&sender_badge);
	    msg = seL4_GetMR(0);
	    func_id = seL4_GetMR(1);
	    int length = seL4_GetMR(2);
	    for(int i = 0 ; i < length; ++i){
	    	int temp = seL4_GetMR(i+3);
	    	printf("  	%d \n",temp );
	    }
	    printf("ta: got message from %#d from tee-container, function id = %d  \n",msg,func_id);
	    tee_result result = function_handler(msg,func_id);
	    if(result.status){
	    	seL4_SetMR(0, msg+1);
	    	seL4_ReplyRecv(EP_CPTR,tag,&sender_badge);	
	    }else{
	    	printf("Error! invalid reference to function\n");
	    }	
 	}
    
 }

 tee_result tee_make_result(int val){
 	tee_result t_obj;
 	t_obj.status = 1;
 	t_obj.ret_val = val;
 	return t_obj;
 }

 tee_result tee_ta_failure(){
 	tee_result t_obj;
 	t_obj.status = 0;
 	return t_obj; 	
 }