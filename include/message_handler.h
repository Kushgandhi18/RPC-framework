#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

typedef struct {
    char *func_name;   
    char *params;      
} Message;

char *serialize_message(Message *mes);
Message *deserialize_message(char *buffer);

#endif
