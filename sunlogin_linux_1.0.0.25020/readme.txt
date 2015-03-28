1.解压Linux被控端sunlogin_linux_1.0.0.0.tar.gz tar -xzf sunlogin_linux_1.0.0.0.tar.gz（解压到本地）
2.修改安装脚本权限install_sunlogin.sh，以root身份运行脚本 chmod +x install_sunlogin.sh ./install_sunlogin.sh
3.运行Linux被控端（分两种方式运行）
   3.1 直接运行二进制文件./bin/oraysunloginservice
   3.2 以服务方式运行 service orayremoteservice start(以服务的方式在后台运行)
4.Linux被控端的登录
   4.1 不带任何参数运行被控端，读取配置文件来运行程序，没有配置文件会出现两种登录方式，护照登录和葵码登录。你可以选择。
   4.2 带参数运行被控端（仅限于直接运行二进制文件，参数有葵码登录 -c1019-0539-3757-1099-3465，护照登录 -uhuzhao -p123456，在后台运行 -d，指定日志目录 -l/home/oray/sunlogin_log等等，具体的可以查看./bin/oraysunloginservice --help）
   4.3 开启远程开机（默认是开启），修改配置文件/etc/orayremotclient.conf中的enablewakeup=1，关闭开机enablewakeup=0.
   4.4 修改开机密码（默认没有开机密码），修改配置文件/etc/orayremoteclient.conf的wakeuperpassword=自定义的密码。
   4.5 登录Linux被控端后，可以写命令logout--注销，logon--登录，changelogon--更换登录(仅限于直接运行二进制文件)
5.Linux被控端的卸载
   运行脚本/usr/local/sunlogin/script/uninstall_sunlogin.sh
注意：
   1,Linux系统需要把ssh服务开启，并配置好ssh，这样就能确保web主控端通过putty连接上Linux被控端 
   2,有些系统会发现不了开机棒（由于防火墙会禁用掉一些端口，使得收不到开机棒发过来的信息）
   所以要在配置文件中指定端口（防火墙没禁用的端口）修改配置文件/etc/orayremoteclient.conf的destinationport=指定的端口。