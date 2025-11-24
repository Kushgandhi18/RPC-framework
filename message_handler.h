#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

typedef struct _message{
    const char *func_name;
    char *params;
}Message;

//buffer divsion == int(func_name len), int(params len), func_name, params
char *serialize_message(Message *mes);
Message *deserialize_message(char *buffer);

#endif
