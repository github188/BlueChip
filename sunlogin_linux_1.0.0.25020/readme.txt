1.��ѹLinux���ض�sunlogin_linux_1.0.0.0.tar.gz tar -xzf sunlogin_linux_1.0.0.0.tar.gz����ѹ�����أ�
2.�޸İ�װ�ű�Ȩ��install_sunlogin.sh����root������нű� chmod +x install_sunlogin.sh ./install_sunlogin.sh
3.����Linux���ضˣ������ַ�ʽ���У�
   3.1 ֱ�����ж������ļ�./bin/oraysunloginservice
   3.2 �Է���ʽ���� service orayremoteservice start(�Է���ķ�ʽ�ں�̨����)
4.Linux���ض˵ĵ�¼
   4.1 �����κβ������б��ضˣ���ȡ�����ļ������г���û�������ļ���������ֵ�¼��ʽ�����յ�¼�Ϳ����¼�������ѡ��
   4.2 ���������б��ضˣ�������ֱ�����ж������ļ��������п����¼ -c1019-0539-3757-1099-3465�����յ�¼ -uhuzhao -p123456���ں�̨���� -d��ָ����־Ŀ¼ -l/home/oray/sunlogin_log�ȵȣ�����Ŀ��Բ鿴./bin/oraysunloginservice --help��
   4.3 ����Զ�̿�����Ĭ���ǿ��������޸������ļ�/etc/orayremotclient.conf�е�enablewakeup=1���رտ���enablewakeup=0.
   4.4 �޸Ŀ������루Ĭ��û�п������룩���޸������ļ�/etc/orayremoteclient.conf��wakeuperpassword=�Զ�������롣
   4.5 ��¼Linux���ض˺󣬿���д����logout--ע����logon--��¼��changelogon--������¼(������ֱ�����ж������ļ�)
5.Linux���ض˵�ж��
   ���нű�/usr/local/sunlogin/script/uninstall_sunlogin.sh
ע�⣺
   1,Linuxϵͳ��Ҫ��ssh�������������ú�ssh����������ȷ��web���ض�ͨ��putty������Linux���ض� 
   2,��Щϵͳ�ᷢ�ֲ��˿����������ڷ���ǽ����õ�һЩ�˿ڣ�ʹ���ղ�������������������Ϣ��
   ����Ҫ�������ļ���ָ���˿ڣ�����ǽû���õĶ˿ڣ��޸������ļ�/etc/orayremoteclient.conf��destinationport=ָ���Ķ˿ڡ�