# run in docker

docker run --rm -it --net=host \
       --device=$(readlink -f /dev/ttyUSB1) \
       --device=/dev/ttyUSB1:/dev/ttyUSB0 \
       --security-opt seccomp=unconfined \
       -v $HOME:$HOME  -w $(pwd) riot \
       make flash

