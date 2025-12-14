// THIS A TEST c file to test message serializing and deserialziing 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "message_handler.h"


void Test_Serialize_1(){
    Message *mes = malloc(sizeof(Message));

    mes->func_name = "test1";
    mes->params = "I'm pooping Here!";

    char *buf = serialize_message(mes);
    char test[100]; 
    for(int i = 0; i < 6; i++){
      test[i] = *(buf + sizeof(int) + i);
    }

    char test2[100]; 
    for(int i = 0; i < 18; i++){
      test2[i] = *(buf + ((sizeof(int) * 2) + 5) + i);
    }
    printf("This is the func in name in buffer %s\n", test);
    printf("This is the func params are %s\n", test2);
}

void Test_Serialize_2(){
    Message *mes = malloc(sizeof(Message));

    mes->func_name = "test2";
    mes->params = "BOOP BOOP!";

    char *buf = serialize_message(mes);
    char test[100]; 
    for(int i = 0; i < 6; i++){
      test[i] = *(buf + sizeof(uint32_t) + i);
    }

    char test2[100]; 
    for(int i = 0; i < 18; i++){
      test2[i] = *(buf + ((sizeof(uint32_t) * 2) + 5) + i);
    }
    printf("This is the func in name in buffer %s\n", test);
    printf("This is the func params are %s\n", test2);

    Message *des_mes = deserialize_message(buf);
    printf("Deserialized func_name %s\n", des_mes->func_name);
    printf("Deserialized params %s\n", des_mes->params);
}

void Test_Serialize_3(){
    Message *mes = malloc(sizeof(Message));

    mes->func_name = "test3";
    mes->params = NULL;

    char *buf = serialize_message(mes);
    char test[100]; 
    for(int i = 0; i < 6; i++){
      test[i] = *(buf + sizeof(uint32_t) + i);
    }
    
    printf("This is the func in name in buffer %s\n", test);

    Message *des_mes = deserialize_message(buf);
    printf("Deserialized func_name %s\n", des_mes->func_name);
}

int main(){
    Test_Serialize_1();
    printf("===============================================================\n");
    Test_Serialize_2();
    printf("===============================================================\n");
    Test_Serialize_3();
    return 0;
}