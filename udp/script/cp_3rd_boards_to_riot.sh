# refer to: https://github.com/RIOT-OS/RIOT/wiki/Thirdparty-hardware-support
# refer to: $RIOTBASE/boards/stm32f4discovery

RIOTBASE=/home/huaxing/oproj/riot/RIOT

rm -rf $RIOTBASE/boards/stm32f407vet6
cp -r ./boards/stm32f407vet6  $RIOTBASE/boards/

# fix bugs in emcute
rm -rf $RIOTBASE/sys/net/application_layer/emcute/
cp -r emcute $RIOTBASE/sys/net/application_layer/
