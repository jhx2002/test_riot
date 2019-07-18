#docker run --device=/dev/video0:/dev/video0   -it --net=host -e DISPLAY=$DISPLAY  -v $HOME:$HOME -v $XSOCK:$XSOCK -v $AUTH:$AUTH  -w $PWD wugui:latest  /bin/bash

docker run --rm -it --net=host \
       --device=$(readlink -f /dev/ttyUSB1) \
       --device=/dev/ttyUSB1:/dev/ttyUSB0 \
       --security-opt seccomp=unconfined \
       -v $HOME:$HOME  -w $(pwd) riot
