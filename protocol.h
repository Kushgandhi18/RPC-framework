#ifndef PROTOCOL_H
#define PROTOCOL_H

#include<stdint.h>
#include<stddef.h>

#define MSG_REQUEST 0x01
#define MSG_RESPONSE 0x02
#define MSG_ERROR 0x03

#define ERR_NONE 0
#define ERR_FUNCTION_NOT_FOUND 1
#define ERR_INVALID_ARGS 2
#define ERR_SERIALIZATION 3
#define ERR_NETWORK 4
#define ERR_TIMEOUT 5

#define TYPE_INT 0x01
#define TYPE_FLOAT 0x02
#define TYPE_STRING 0x03
#define TYPE_VOID 0x04

#define MAX_FUNCTION_NAME 64
#define MAX_ARGS 10
#define MA_PAYLOAD_SIZE 4096

typedef struct
{
    uint8_t msg_type;
    uint32_t request_id;
    uint32_t payload_length;
    uint8_t error_code;
} __attribute__((packed)) MessageHeader;

typedef struct 
{
    char function_name[MAX_FUNCTION_NAME];
    uint8_t num_args;
    uint8_t arg_types[MAX_ARGS];
    uint8_t return_type;   
} __attribute__((packed)) RPCRequest;

typedef struct
{
    uint8_t return_type;
    uint8_t error_code;
} __attribute__((packed))RPCResponse;

MessageHeader create_message_header(uint8_t type, uint32_t req_id, uint32_t payload_len); 

int serilize_int(uint8_t *buffer, int value);
int deserialize_int(const uint8_t *buffer, int *value);
int serialize_float(const uint8_t *buffer, float *value);
int deserialize_float(const uint8_t *buffer, float *value);
int serialize_string(uint8_t *buffer, const char *str, size_t max_len);
int deserialize_string(const uint8_t *buffer, char *str, size_t max_len);

int send_message(int sockfd, const MessageHeader *header, const void *payload);
int recv_message(int sockfd, MessageHeader *header, void *payload, size_t max_payload);
#endif