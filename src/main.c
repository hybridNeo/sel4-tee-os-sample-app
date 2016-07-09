/*
 *	@Author : Rahul Mahadev (hybridNeo)
 *	Hello world app 
 */


#include "tee_internal_api.h"
#include "tee_crypto_api.h"
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

int ceil_num(double a){
	return (int)a + 1;
}

//Temporary fix - will fetch from secure storage later
static const char *key_string = "2b7e151628aed2a6abf7158809cf4f3c";
// static const char *plaintext_string = "6bc1bee22e409f96e93d7e117393172a";	
void encrypt(char *arr){
	uint8_t key[16];
	uint8_t plaintext[16];
	uint8_t ciphertext[16];
	int param_len = strlen(arr);
	char plaintext_string[16 * ceil_num(param_len/16.0)];	
	strcpy(plaintext_string,arr);
	for(int i= strlen(arr); i < strlen(plaintext_string);++i){
		plaintext_string[i] = 0;
	}
	AES128_STRING_parse(key_string, key);
	AES128_STRING_parse(plaintext_string, plaintext);
	AES128_ECB_encrypt(plaintext, key, ciphertext);
	strcpy(arr,ciphertext);
	int i,j=0;
	for (i = 0; i < 16; i++){
		sprintf(arr+j,"%02x", ciphertext[i]);
		j+=2;
	}	
}

void decrypt(char *arr){
	uint8_t key[16];
	uint8_t plaintext[16];
	uint8_t ciphertext[16];
	int param_len = strlen(arr);
	char plaintext_string[16 * ceil_num(param_len/16.0)];
	strcpy(plaintext_string,arr);
	for(int i= strlen(arr); i < strlen(plaintext_string);++i){
		plaintext_string[i] = 0;
	}
	AES128_STRING_parse(key_string, key); 	
	AES128_STRING_parse(plaintext_string, plaintext);
	AES128_ECB_decrypt(plaintext, key, ciphertext);
	strcpy(arr,ciphertext);
	int i,j=0;
	for (i = 0; i < 16; i++){
		sprintf(arr+j,"%02x", ciphertext[i]);
		j+=2;
	}	
}

//Every ta must have a function handler.
tee_result function_handler(int msg, int func_id ,seL4_Word* param_arr,int length){
	if(func_id == HELLO_TA_INCREMENT ){
		// char *temp = (char *)param_arr;
		// int arr[5] = {12,34,4,45,55};
		return tee_make_result(increment(msg),NULL,0);
	}else if(func_id == HELLO_TA_DECRYPT){
		char *temp = (char *)param_arr;
		decrypt(temp);
		return tee_make_result(0,temp,length * sizeof(seL4_Word));	 
	}
	else if(func_id == HELLO_TA_ENCRYPT){
		char *temp = (char *)param_arr;
		encrypt(temp);
		return tee_make_result(0,temp,length * sizeof(seL4_Word));	 
	}else if(func_id == HELLO_TA_DECRYPT){
		char *temp = (char *)param_arr;
		decrypt(temp);
		return tee_make_result(0,temp,length * sizeof(seL4_Word));
	}
	else{
		return tee_ta_failure();
	}
}
