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
	 	tag = seL4_Recv(EP_CPTR,&sender_badge);
		msg = seL4_GetMR(0);
		func_id = seL4_GetMR(1);

		int length = seL4_GetMR(2);
		seL4_Word param_arr[length];
		for(int i = 0 ; i < length; ++i){
			int temp = seL4_GetMR(i+3);
			param_arr[i] = temp;
		}
		printf("ta: got message:= %#d from tee-container, function id = %d  \n",msg,func_id);
		tee_result result = function_handler(msg,func_id,param_arr,length);
		if(result.status){
			int length = result.size/(double)sizeof(seL4_Word);
			seL4_SetMR(0, msg+1);
			if(length > 0){
				seL4_Word* blockptr = (seL4_Word*)result.data;
				seL4_SetMR(1,length);
				 for(int i =0 ; i < length;++i){
					seL4_SetMR(i+2,*blockptr);
					blockptr++;
			   	 }
			}
			seL4_Reply(tag);	
		}else{
			printf("Error! invalid reference to function\n");
		}	
 	}
	
 }

 tee_result tee_make_result(int val,void *data,size_t size){
 	tee_result t_obj;
 	t_obj.status = 1;
 	t_obj.ret_val = val;
 	t_obj.data = data;
 	t_obj.size = size;
 	return t_obj;
 }

 tee_result tee_ta_failure(){
 	tee_result t_obj;
 	t_obj.status = 0;
 	return t_obj; 	
 }