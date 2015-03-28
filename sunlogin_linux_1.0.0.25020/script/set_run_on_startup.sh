#!/bin/bash
echo "set orayremoteservice run on startup"
if [ -d "/etc/init.d" ]; then
     if [ -d "/etc/rc0.d" ]; then
	ln -sf /etc/init.d/orayremoteservice /etc/rc0.d/K50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc1.d/K50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc6.d/K50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc2.d/S50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc3.d/S50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc4.d/S50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc5.d/S50orayremoteservice
     else
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc0.d/K50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc1.d/K50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc6.d/K50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc2.d/S50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc3.d/S50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc4.d/S50orayremoteservice
	ln -sf /etc/init.d/orayremoteservice /etc/rc.d/rc5.d/S50orayremoteservice
     fi
else
     if [ -d "/etc/rc0.d" ]; then
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc0.d/K50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc1.d/K50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc6.d/K50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc2.d/S50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc3.d/S50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc4.d/S50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc5.d/S50orayremoteservice
     else
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc0.d/K50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc1.d/K50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc6.d/K50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc2.d/S50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc3.d/S50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc4.d/S50orayremoteservice
	ln -sf /etc/rc.d/init.d/orayremoteservice /etc/rc.d/rc5.d/S50orayremoteservice
     fi
fi