#!/usr/bin/env bash
if [ $UID = 0 ];then
	if [ x$1 = x ];then
		$1 = install
	fi
	case $1 in
		install)
		mkdir build
		cd build
		cmake -DCMAKE_BUILD_TYPE=Release ..
		make
		make install 
		cp install_manifest.txt ..
		cd ..
		rm -rf build
		;;
		uninstall)
		cat install_manifest.txt | sudo xargs rm -f
		rm -f install_manifest
		;;
		*)
		echo 未知选项
	esac
else
	echo 没有root权限
fi
