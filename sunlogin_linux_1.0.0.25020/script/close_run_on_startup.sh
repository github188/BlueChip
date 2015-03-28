#!/bin/bash
echo "close orayremoteservice run on startup"

if [ -f "/etc/rc0.d/K50orayremoteservice" ]; then  
rm -f /etc/rc0.d/K50orayremoteservice
fi
if [ -f "/etc/rc.d/rc0.d/K50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc0.d/K50orayremoteservice
fi

if [ -f "/etc/rc1.d/K50orayremoteservice" ]; then  
rm -f /etc/rc1.d/K50orayremoteservice
fi 
if [ -f "/etc/rc.d/rc1.d/K50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc1.d/K50orayremoteservice
fi

if [ -f "/etc/rc6.d/K50orayremoteservice" ]; then  
rm -f /etc/rc6.d/K50orayremoteservice
fi
if [ -f "/etc/rc.d/rc6.d/K50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc6.d/K50orayremoteservice
fi

if [ -f "/etc/rc2.d/S50orayremoteservice" ]; then  
rm -f /etc/rc2.d/S50orayremoteservice
fi
if [ -f "/etc/rc.d/rc2.d/S50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc2.d/S50orayremoteservice
fi

if [ -f "/etc/rc3.d/S50orayremoteservice" ]; then  
rm -f /etc/rc3.d/S50orayremoteservice
fi
if [ -f "/etc/rc.d/rc3.d/S50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc3.d/S50orayremoteservice
fi

if [ -f "/etc/rc4.d/S50orayremoteservice" ]; then  
rm -f /etc/rc4.d/S50orayremoteservice
fi
if [ -f "/etc/rc.d/rc4.d/S50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc4.d/S50orayremoteservice
fi

if [ -f "/etc/rc5.d/S50orayremoteservice" ]; then  
rm -f /etc/rc5.d/S50orayremoteservice
fi
if [ -f "/etc/rc.d/rc5.d/S50orayremoteservice" ]; then  
rm -f /etc/rc.d/rc5.d/S50orayremoteservice
fi