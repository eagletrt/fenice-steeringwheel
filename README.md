# Steering Wheel Project 

## Repository Description 

In this repository you can find the source code of our steering wheel.

The project is divided in 2 version: 

* **Desktop**: is compiled for Desktop (Linux x86), and is used to the development part, to test and introduce new feature. This version used different `.cpp` files that you can find in the `.pro` file. In order to work without wiringpi we mapped the input and use the keyboard also for the inteface to comunicate with the car through can-utils we virtualized the interface.

* **Embedded**: is compiled for arm using this [guide](https://eagletrt.github.io/volanteCrosscompilazione.html) and is sended via SSH to the target device. 

## Cross Compile for Taget Device

### Stop the process

```sh
$ ssh root@eaglepi
$ kill -9 "pid"
```

### Compile for the Steering Wheel

```sh
$ ./fenice-deploy.sh
```
Be sure that the IP address, written in fenice-deploy.sh, is the same as the SteeringWheel IP address.


## Compile for Desktop

```sh
$ ./deploy.sh
```

Be sure the directory written in ```QMAKE``` is the same as the one you can find in your PC.

## Common problems

### New Files

Each time a file is added, be sure is reported both in "eagleSteeringWheel.pro" and "FeniceSteeringWheel.pro" for cpp header and source files and in qml.qrc for qml files.

### Raspberry

RaspberryPI doesn't keep the same IP each session. So check each time the correct address. In principle it would keep something like 192.168.8.100-101...


## General structure of the project

### BackEnd

SteeringWheel works thanks to CAN messages. These are sended through CAN-Bus (which is a bus :D). Each time a message came to SW, is stored into an object called ** device ** and then paresed via ```parseCanMessage``` in CanBus class. This function has the task to update the different status of the car (like inverters temperature as well as speed). These statuses are stored in CarStatus.

### FrontEnd

Each time a value changes, a signal will send to ** qml ** interface (thanks to Qt framework). Here functions called *Changed (such as TelemetrystatusChanged) have the task to update the interface in order to show to the screen the current status of the car.