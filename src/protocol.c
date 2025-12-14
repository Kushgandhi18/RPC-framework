#include "protocol.h"
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

/* ---------------- Message Header ---------------- */

MessageHeader create_message_header(uint8_t type,
                                    uint32_t req_id,
                                    uint32_t payload_len)
{
    MessageHeader header;
    header.msg_type = type;
    header.request_id = req_id;
    header.payload_length = payload_len;
    header.error_code = ERR_NONE;
    return header;
}

/* ---------------- Serialization Helpers ---------------- */

int serialize_int(uint8_t *buffer, int value)
{
    uint32_t network_value = htonl((uint32_t)value);
    memcpy(buffer, &network_value, sizeof(uint32_t));
    return sizeof(uint32_t);
}

int serialize_float(uint8_t *buffer, float value)
{
    memcpy(buffer, &value, sizeof(float));
    return sizeof(float);
}

int deserialize_float(const uint8_t *buffer, float *value)
{
    memcpy(value, buffer, sizeof(float));
    return sizeof(float);
}

int serialize_string(uint8_t *buffer, const char *str, size_t max_len)
{
    size_t len = strlen(str);
    if (len >= max_len)
        len = max_len - 1;

    uint32_t network_len = htonl((uint32_t)len);
    memcpy(buffer, &network_len, sizeof(uint32_t));
    memcpy(buffer + sizeof(uint32_t), str, len);
    buffer[sizeof(uint32_t) + len] = '\0';

    return sizeof(uint32_t) + len + 1;
}

int deserialize_string(const uint8_t *buffer, char *str, size_t max_len)
{
    uint32_t network_len;
    memcpy(&network_len, buffer, sizeof(uint32_t));

    size_t len = ntohl(network_len);
    if (len >= max_len)
        len = max_len - 1;

    memcpy(str, buffer + sizeof(uint32_t), len);
    str[len] = '\0';

    return sizeof(uint32_t) + len + 1;
}

/* ---------------- Send / Receive ---------------- */

int send_message(int sockfd,
                 const MessageHeader *header,
                 const void *payload)
{
    ssize_t sent = send(sockfd, header, sizeof(MessageHeader), 0);
    if (sent != sizeof(MessageHeader))
        return -1;

    if (header->payload_length > 0 && payload != NULL)
    {
        size_t total_sent = 0;
        const uint8_t *data = (const uint8_t *)payload;

        while (total_sent < header->payload_length)
        {
            sent = send(sockfd,
                        data + total_sent,
                        header->payload_length - total_sent,
                        0);

            if (sent <= 0)
                return -1;

            total_sent += sent;
        }
    }
    return 0;
}

int recv_message(int sockfd,
                 MessageHeader *header,
                 void *payload,
                 size_t max_payload)
{
    size_t total_received = 0;
    uint8_t *header_buf = (uint8_t *)header;

    /* Receive header */
    while (total_received < sizeof(MessageHeader))
    {
        ssize_t received = recv(sockfd,
                                header_buf + total_received,
                                sizeof(MessageHeader) - total_received,
                                0);

        if (received <= 0)
            return -1;

        total_received += received;
    }

    /* Receive payload */
    if (header->payload_length > 0)
    {
        if (header->payload_length > max_payload)
            return -1;

        total_received = 0;
        uint8_t *payload_buf = (uint8_t *)payload;

        while (total_received < header->payload_length)
        {
            ssize_t received = recv(sockfd,
                                    payload_buf + total_received,
                                    header->payload_length - total_received,
                                    0);

            if (received <= 0)
                return -1;

            total_received += received;
        }
    }
    return 0;
}
