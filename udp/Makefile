# name of your application
APPLICATION = udp

# If no BOARD is found in the environment, use this default:
#BOARD ?= native
BOARD = stm32f4discovery

# This has to be the absolute path to the RIOT base directory:
#RIOTBASE ?= $(CURDIR)/../..
RIOTBASE ?= /home/huaxing/oproj/riot/RIOT


# Include packages that pull up and auto-init the link layer.
# NOTE: 6LoWPAN will be included if IEEE802.15.4 devices are present
USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
# Specify the mandatory networking modules for IPv6 and UDP
USEMODULE += gnrc_sock_udp
USEMODULE += gnrc_ipv6_default
# Include MQTT-SN
USEMODULE += emcute
# Add also the shell, some shell commands
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
# For testing we also include the ping6 command and some stats
USEMODULE += gnrc_icmpv6_echo

# use Ethernet
USEMODULE += enc28j60
USEMODULE += gnrc_ipv6_router_default
USEMODULE += gnrc_icmpv6_echo

# stdio
# uart port: PD8, PD9
STDIO_DEV = UART_DEV\(1\)
CFLAGS += -DSTDIO_UART_DEV=$(STDIO_DEV)

# fallback: set SPI bus and pins to default values
ENC_SPI ?= SPI_DEV\(0\)
ENC_CS  ?= GPIO_PIN\(0,2\)  # PA2
ENC_INT ?= GPIO_PIN\(0,4\)  # PA4
ENC_RST ?= GPIO_PIN\(0,3\)  # PA3
# export SPI and pins
CFLAGS += -DENC28J60_PARAM_SPI=$(ENC_SPI)
CFLAGS += -DENC28J60_PARAM_CS=$(ENC_CS)
CFLAGS += -DENC28J60_PARAM_INT=$(ENC_INT)
CFLAGS += -DENC28J60_PARAM_RESET=$(ENC_RST)

#
USEMODULE += pulse_counter
USEMODULE += periph_pwm

#
THREAD_EXTRA_STACKSIZE_PRINTF = 2048

## 
# add a list of subdirectories, that should also be build
EXTERNAL_MODULE_DIRS += $(CURDIR)/sender
INCLUDES += -I$(CURDIR)/sender/include
USEMODULE += zhilu_sender


# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Comment this out to join RPL DODAGs even if DIOs do not contain
# DODAG Configuration Options (see the doc for more info)
# CFLAGS += -DGNRC_RPL_DODAG_CONF_OPTIONAL_ON_JOIN

# release flags
# CFLAGS += -DNDEBUG -DLOG_LEVEL=LOG_NONE

GNRC_UDP_MSG_QUEUE_SIZE = 16
GNRC_IPV6_MSG_QUEUE_SIZE = 16
GNRC_NETIF_MSG_QUEUE_SIZE = 32

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
