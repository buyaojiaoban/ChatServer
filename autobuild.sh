#########################################################################
# File Name: autobuild.sh
# Author: jiang yi lin
# mail: buyaojiaoban@163.com
# Created Time: 2022年12月23日 星期日 18时40分35秒
#########################################################################
#!/bin/bash

set -x

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
