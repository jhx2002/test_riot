/**
 * @brief       Vehicle control execute. 
 *  STM32F407VET6 
 *  RAM: 196K     FLASH: 512K     CPU: cortex-M3   168MHz
 *              
 */

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "shell.h"
#include "msg.h"
#include "net/ipv6/addr.h"
#include "thread.h"
#include "log.h"
#include "xtimer.h"

#include "sender.h"

static msg_t queue[8];

static char *gateway_ipv6 = "fe80::f58c:2fb7:adad:1";
static int gateway_port = 10000;


static int cmd_info(int argc, char** argv)
{
    if (argc > 0) {
        printf("%s", argv[0]);
    }

    printf("Vehicle control execute\n");
    puts("");
    return 0;
};


static const shell_command_t shell_commands[] = {
    { "info", " show informations", cmd_info },
    { NULL, NULL, NULL }
};

    
int main(void)
{
    puts("Vehicle control execute \n");

    //sender
    
    sender_params_t ss_params = { 
        .data_name = "/sender/data",
        .cmd_name = "/sender/cmd",
        .gw_ipv6 = gateway_ipv6,
        .gw_port = gateway_port,
    };
    sender_t ss_obj;
    if (0 != sender_init(&ss_obj, &ss_params)) {
        return 1;
    }
    sender_start(&ss_obj);

    /* the main thread needs a msg queue to be able to run `ping6`*/
    msg_init_queue(queue, (sizeof(queue) / sizeof(msg_t)));

    /* start shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    /* should be never reached */
    return 0;
}
