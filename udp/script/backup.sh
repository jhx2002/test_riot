#！/bin/sh

BAK_DIR=$HOME/backup
TMP_DIR=$HOME/backup/bak 
mkdir $TMP_DIR

cp -r /home/huaxing/proj/riot_apps/controller $TMP_DIR

tar -zcvf $BAK_DIR/controller.$(date +%Y%m%d).tar.gz $TMP_DIR
rm -rf $TMP_DIR

#find $BAK_DIR/ -mtime +30 -name "*.tar.gz" -exec rm -rf {} \;   //删除改文件夹下超过30天的文件
