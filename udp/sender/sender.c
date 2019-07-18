#include "thread.h"
#include "xtimer.h"
#include "net/ipv6/addr.h"
#include "net/sock/udp.h"
#include "log.h"
#include "assert.h"

#include "sender.h"

#define SENDER_PRIO  (THREAD_PRIORITY_MAIN - 1)
#define MY_PORT 1112

static char main_stack[THREAD_STACKSIZE_DEFAULT ];

//static sock_udp_t sock;
static sock_udp_ep_t gw;
static sock_udp_ep_t local = SOCK_IPV6_EP_ANY;
static char* CLIENT_ADDR = "fe80::f58c:2fb7:adad:10";

//static uint8_t rbuf[32];
//static uint8_t tbuf[32];


void send(sender_t* dev) {
    assert(dev != NULL);

    char* buf = "hi";
    size_t res = sock_udp_send(NULL, buf, strlen(buf), &gw);
    //sock_udp_send(&sock, buf, strlen(buf), &gw);
   
    printf("send %d\n", res);
}


static void *main_task(void *arg)
{
    assert(arg != NULL);
    
    sender_t* dev = (sender_t*)arg;
    //sender_params_t* params = &dev->params;

    
    /* main loop */
    int count = 0;
    while(1) {
        send(dev);
        
        count ++ ;
        xtimer_usleep(10000); //10ms
    }

    return NULL;    /* should never be reached */
}


int sender_init(sender_t* dev, const sender_params_t *params) {
    assert(dev != NULL);
    assert(params != NULL);

    dev->params = *params;

    // add this client addr
    gnrc_netif_t *netif;
    ipv6_addr_t addr;

    if (!(netif = gnrc_netif_iter(NULL))) {
        printf("No valid network interface found\n");
        return 1;
    }

    if (ipv6_addr_from_str(&addr, CLIENT_ADDR) == NULL) {
        printf("Can't convert given string to IPv6 Address\n");
        return 1;
    }
    
    if (gnrc_netif_ipv6_addr_add(netif, &addr, 64,
                                 GNRC_NETIF_IPV6_ADDRS_FLAGS_STATE_VALID) < 0) {
        printf("Can't assign given IPv6 Address\n");
        return 1;
    }

    
    // remote
    gw.family = AF_INET6;
    gw.port = params->gw_port ;
    if (ipv6_addr_from_str((ipv6_addr_t *)&gw.addr.ipv6, params->gw_ipv6) == NULL) {
        LOG_ERROR("[sender] error parsing IPv6 address\n");
        return SENDER_ERR;
    }

    // local
    local.family = AF_INET6;
    local.port = MY_PORT;
    if (ipv6_addr_from_str((ipv6_addr_t *)&local.addr.ipv6, CLIENT_ADDR) == NULL) {
        LOG_ERROR("[sender] error parsing IPv6 address\n");
        return SENDER_ERR;
    }

/*    
    // sock
    if (sock_udp_create(&sock, &local, NULL, 0) < 0) {
        LOG_ERROR("[sender] unable to open UDP socket on port %i\n", (int)MY_PORT);
        return SENDER_ERR;
    }
*/

    char addr_buf[64];
    printf("gateway: %s\n", 
           ipv6_addr_to_str(addr_buf, (ipv6_addr_t *)&gw.addr.ipv6, 64) );

    printf("local: %s\n", 
           ipv6_addr_to_str(addr_buf, (ipv6_addr_t *)&local.addr.ipv6, 64) );


    return SENDER_OK;
}


int sender_start(sender_t* dev) {
    assert(dev != NULL);

    /* create a thread to read/convert/send speed data */
    thread_create(main_stack, sizeof(main_stack), SENDER_PRIO,
                  0, main_task, dev, "sender_task");
    
    xtimer_usleep(10000); // 10ms
    
    return SENDER_OK;
}

