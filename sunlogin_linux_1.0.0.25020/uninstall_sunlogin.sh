#!/bin/bash
echo "Start uninstall linux sunlogin"
#关闭开机启动
/usr/local/sunlogin/script/close_run_on_startup.sh
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
#判断服务是否运行并关闭
res=$(ps aux | grep '/usr/local/sunlogin/bin/oraysunloginservice -d' | wc -l)
if [ $res -ne 0 ]; then
   service orayremoteservice stop
fi
if [ -d "/var/log/sunlogin" ]; then
rm -rf /var/log/sunlogin
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
fi
if [ -f "/etc/init.d/orayremoteservice" ]; then
rm -f /etc/init.d/orayremoteservice
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
fi
if [ -f "/etc/rc.d/init.d/orayremoteservice" ]; then
rm -f /etc/rc.d/init.d/orayremoteservice
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
fi
if [ -f "/etc/phremote.ini" ]; then
rm -f /etc/phremote.ini
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
fi
if [ -f "/tmp/proc_oray_save.pid" ]; then
rm -f /tmp/proc_oray_save.pid
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
fi
if [ -d "/usr/local/sunlogin" ]; then
rm -rf /usr/local/sunlogin
if [ $? -ne 0 ]; then
echo "Uninstall failed"
exit
fi
fi
echo "Finish uninstall linux sunlogin"