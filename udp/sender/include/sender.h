/**
 * @brief     Speed sensor module, ...
 */

#ifndef SENDER_H
#define SENDER_H

#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SENDER_RB_NUM
#define SENDER_RB_NUM 1
#endif
    

/**
 * @brief Configuration for sender
 */
typedef struct {
    char* data_name;          /** data topic in mqttsn */
    char* cmd_name;           /** control topic in mqttsn */
    char* gw_ipv6;
    int gw_port;
} sender_params_t;

    
/**
 * @brief speed sensor type 
 */
typedef struct {
    sender_params_t params;
} sender_t;


/**
 * @brief   Possible SENDER return values
 */
enum {
    SENDER_OK = 0,       /**< everything in order */
    SENDER_INVALID_ARG,       /**< everything in order */
    SENDER_ERR,    /**< invalid device given */
};

int sender_init(sender_t* dev, const sender_params_t *params);

int sender_start(sender_t* dev);

    
#ifdef __cplusplus
}
#endif

#endif /* SENDER_H */
