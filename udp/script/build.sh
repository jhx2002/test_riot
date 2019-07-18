docker run --rm -it --net=host  -v $HOME:$HOME  -w $(pwd) riot \
       make all
