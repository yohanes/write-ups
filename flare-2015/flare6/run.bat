adb push libs\armeabi\hello /data/local/tmp
adb push libvalidate.so /data/local/tmp
adb shell "chmod 755 /data/local/tmp/hello"
adb push libs\armeabi\libmylib.so /data/local/tmp
adb shell "LD_PRELOAD=/data/local/tmp/libmylib.so /data/local/tmp/hello" 
