/*
 *  @Author : Rahul Mahadev (hybridNeo)
 *  Starting point for tee-os
 */
#include "tee_internal_api.h"
 void init(){
 	seL4_Word sender_badge;
    seL4_MessageInfo_t tag;
    seL4_Word msg,func_id;

    tag = seL4_Recv(EP_CPTR,&sender_badge);
    // assert(sender_badge == EP_CPTR );
    // assert(seL4_MessageInfo_get_length(tag) == 1);
    msg = seL4_GetMR(0);
    func_id = seL4_GetMR(1);
    printf("ta: got message from %#d from tee-container, function id = %d  \n",msg,func_id);
    tee_result result = function_handler(msg,func_id);
    if(result.status){
    	seL4_SetMR(0, msg+1);
    	seL4_ReplyRecv(EP_CPTR,tag,&sender_badge);	
    }else{
    	printf("Error! invalid reference to function\n");
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