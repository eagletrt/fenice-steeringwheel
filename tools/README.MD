# Volante Cheat Sheet

## `Install SocketCan on Linux`

```bash
$ sudo apt-get install can-utils
```

## `Setup Can on Linux`

```bash
$ modprobe vcan
$ sudo ip link add dev vcan0 type vcan
$ sudo ip link set up vcan0
```

## `Can utils Command`

```bash
$ cansniffer vcan0 -c
$ candump vcan0 
$ cansend vcan0 0B0#0110110000000000
```

## Can Send Message

The message used by can-utils contains
0B0 : Message ID
00 00 00 00 00 00 00 00 : Message Payload 

## Qt TODO

.pro
./deploy.sh //parametrizzati in base allo user (chiedere user a luca, pc lab) eagletrt -> pc lab      lucamartinelli -> luca
./deployChimera.sh

## Raspberry Remove Warning

include extraconfig.txt in config.txt

```bash
avoid_warnings = 1
```


## Raspberry CAN-BUS

### `/boot/config.txt`
```bash
dtparam=i2c_arm=on
dtparam=i2c0=on
dtparam=i2c1=on
dtparam=spi=on
dtoverlay=mcp2515-can0,oscillator=16000000,interrupt=25
dtoverlay=spi-1cs
```
### `canbus.sh`

```bash
#!/bin/bash

if [ $1 = "vcan0" ]
    then
        echo "setting up vcan ..."
        sudo modprobe vcan
        sudo ip link add dev vcan0 type vcan
        sudo ifconfig vcan0 up
        echo "setup done :)"
    else
        echo "setting up can0 ..."
        sudo modprobe i2c-dev
        sudo modprobe can_dev
        sudo modprobe can_raw
        sudo modprobe can
        sudo ip link set can0 up type can bitrate 1000000
        sudo ifconfig can0 up
        echo "setup done :)"
fi
```
### can0


```bash
$ sudo modprobe i2c-dev
$ sudo modprobe can_dev
$ sudo modprobe can_raw
$ sudo modprobe can
$ sudo ip link set can0 up type can bitrate 1000000
$ sudo ifconfig can0 up
```

## `PM2 Startup Application`

```bash
$ sudo npm install -g pm2
$ pm2 start server.js
$ pm2 start systemd
```

copy where you have to copy and paste it in the terminal

```bash
$ pm2 save
$ pm2 list //to check
$ pm2 show server
```
## `Create a Service`

`myscript.service`

```bash
[Unit]
Description=My service
After=network.target

[Service]
ExecStart=/usr/bin/python3 -u main.py
WorkingDirectory=/home/pi/myscript
StandardOutput=inherit
StandardError=inherit
Restart=always
User=pi

[Install]
WantedBy=multi-user.target
```

```bash
$ sudo cp myscript.service /etc/systemd/system/myscript.service
$ sudo systemctl start myscript.service
$ sudo systemctl stop myscript.service
$ sudo systemctl enable myscript.service
```

## UBUNTU-RPI

### Turn On WIFI 

```bash
$ sudo wpa_supplicant -B -c /etc/wpa_supplicant/wpa_supplicant.conf -i wlan0
$ sudo dhclient wlan0
```

### Auto Login on Ubuntu

```bash
ExecStart=-/sbin/agetty --noclear -a pi %I $TERM
```

## WiFi

### Static IP

in /etc/network/interfaces
change "iface wlan0 inet dhcp" in "iface wlan0 inet static"

in /etc/wpa_supplicant/wpa_supplicant.conf

```bash
    address 10.196.30.211   # Static IP you want 
    netmask 255.255.254.0 
    gateway 10.196.31.130   # IP of your router
```

### Auto Connect Wifi Network

in /etc/network/interfaces

```bash
auto wlan0

allow-hotplug wlan0
iface wlan0 inet dhcp
wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf
iface default inet dhcp
```

in /etc/wpa_supplicant/wpa_supplicant.conf

```bash
network={
    ssid="eagletrt-24"
    psk="eaglepiTRT"
    proto=RSN
    key_mgmt=WPA-PSK
    pairwise=CCMP
    auth_alg=OPEN
}
```

### Wireless Config Example

in /etc/network/interfaces

```bash
auto wlan0

iface lo inet loopback
iface eth0 inet dhcp

allow-hotplug wlan0
iface wlan0 inet static
address 192.168.1.155
netmask 255.255.255.0
gateway 192.168.1.1
wpa-conf /etc/wpa_supplicant/wpa_supplicant.conf
iface default inet dhcp
```

in /etc/wpa_supplicant/wpa_supplicant.conf

```bash
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1

network={
ssid="NYO_WWWP"
psk="topsecret"
proto=RSN
key_mgmt=WPA-PSK
pairwise=CCMP
auth_alg=OPEN
}
```


## Others
```bash
$ screenfetch
$ cat textfile.txt
```

