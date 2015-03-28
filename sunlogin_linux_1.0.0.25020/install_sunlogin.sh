#!/bin/bash
echo "Start install linux sunlogin"
echo "Install path(/usr/local/sunlogin)"
mkdir -p /a /usr/local/sunlogin/bin
if [ $? -ne 0 ]; then
echo "Install failed"
exit
fi
mkdir -p /a /usr/local/sunlogin/html
if [ $? -ne 0 ]; then
echo "Install failed"
exit
fi
cp bin/oraysunloginservice /usr/local/sunlogin/bin
if [ $? -ne 0 ]; then
echo "Install failed"
exit
fi
cp script/phremote.ini /etc/
chmod +x /usr/local/sunlogin/bin/oraysunloginservice
cp bin/ethtool /usr/local/sunlogin/bin
cp html/* /usr/local/sunlogin/html/
chmod +x /usr/local/sunlogin/bin/ethtool

if [ -d "/etc/init.d" ]; then
cp script/orayremoteservice /etc/init.d/
chmod +x /etc/init.d/orayremoteservice
else
cp script/orayremoteservice /etc/rc.d/init.d/
chmod +x /etc/rc.d/init.d/orayremoteservice
fi
#输入护照或者葵码
chmod +x bin/oraysunloginservice
./bin/oraysunloginservice -reset
echo "you can switch account by running command (-u<username> -p<password> or -reset) option, or by command (changelogon) after logon."
chmod +x script/set_run_on_startup.sh
chmod +x script/close_run_on_startup.sh
chmod +x uninstall_sunlogin.sh
mkdir -p /a /usr/local/sunlogin/script
cp uninstall_sunlogin.sh /usr/local/sunlogin/script
cp script/set_run_on_startup.sh /usr/local/sunlogin/script/
cp script/close_run_on_startup.sh /usr/local/sunlogin/script/
chmod +x /usr/local/sunlogin/script/uninstall_sunlogin.sh
chmod +x /usr/local/sunlogin/script/set_run_on_startup.sh
chmod +x /usr/local/sunlogin/script/close_run_on_startup.sh
#是否设置开机启动
i=1
while [ $i -eq 1 ]
do
echo "Need to run on startup(y/n):"
read result
if [ "$result" == "y" ]; then
./script/set_run_on_startup.sh
echo "please run /usr/local/sunlogin/script/close_run_on_startup.sh if you don't want to run on startup"
break
elif [ "$result" == "n" ]; then
./script/close_run_on_startup.sh
echo "please run /usr/local/sunlogin/script/set_run_on_startup.sh if you want to run on startup"
break
else
continue
fi
done
#检测sshd是否安装并启动
echo "start sshd service"
service sshd start
if [ $? -ne 0 ]; then
echo "sshd service start failed,please check and install the ssh,or you can't connect the putty by the web host"
fi
#是否立即启动程序
i=1
while [ $i -eq 1 ]
do
echo "Run now?(y/n):"
read result
if [ "$result" == "y" ]; then
service orayremoteservice start
break
elif [ "$result" == "n" ]; then
break
else
continue
fi
echo "application can be started by running as a service (service orayremoteservice start) or by command (/usr/local/sunlogin/bin/oraysunloginservice)"
done
echo "finish install linux sunlogin"
echo "install path:/usr/local/sunlogin"
echo "config file:/etc/orayremoteclient.conf"
echo "log path:/var/log/sunlogin"