# Steering Wheel Project 

## Repository Description 

In this repository you can find the source code of our steering wheel.

The project is divided in 2 version: 

* **Desktop**: is compiled for Desktop (Linux x86), and is used to the development part, to test and introduce new feature. This version use different `.cpp` files that you can find in the `.pro` file. In order to work without wiringpi we mapped the input and use the keyboard also for the inteface to comunicate with the car through can-utils we virtualized the interface.

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

* Be sure the directory written in ```QMAKE``` is the same as the one you can find in your PC.

* Qt, can-utils and libgl-dev are required.

## Common problems

### New Files

Each time a file is added, be sure is reported both in "eagleSteeringWheel.pro" and "FeniceSteeringWheel.pro" for cpp header and source files and in qml.qrc for qml files.

### Raspberry

RaspberryPI doesn't keep the same IP each session. So check each time the correct address. In principle it would keep something like 192.168.8.100-101...


## General stucture of the project

Project starts from main_x86.cpp. Here 3 classes are instantiated:
```Buttons
   CarStatus
   Canbus
```
These have different tasks. **Buttons** manages the pression of the physical buttons of the Steering Wheel. **CarStatus** saves the status of each different part of the car, such as inverter temperature and HV charge. **Canbus** handle everything related to reception and sending of can messages.
These three objects are passed as parameter to qml via ```QQuickView* view```. This operation is required to garant a communication between C++ and qml.
The UI runs into a Thread in order to improve performances and consistency. Class ```Graphics``` manage this operation.

### Message is sent by the car to the Steering Wheel

#### BackEnd

SteeringWheel works thanks to CAN messages. These are sended through CAN-Bus (which is a bus :D). Each time a message came to Steering Wheel, it is passed to a Thread, wich manages an object called **device**, and then paresed via ```parseCanMessage``` in CanBus class. This function has the task to update the different status of the car (like inverters temperature as well as speed). It works with a switch case, each case is an ID and for each IDs there a if condition to parse the payload. Once the message is parsed, some variables in CarStatus will change.

#### FrontEnd

The **UI** is written in **qml** and presented with a TabView. Each tab has properties connected to the backend. Everytime a variable in CarStatus, that is a property in a Tab, a ```signal``` will be sent. Here functions called *Changed (such as ```TelemetrystatusChanged```) have the task to update the tab, respecting the new values.


### Message is sent by the Stering Wheel to the car

Even the Steering Wheel send can messages. This could happen in 2 cases. A message is sent automatically or after pressing a button. But each time the message start from qml, here a ```slot``` CanBus function is called. This function could modify CarStatus values and ,after that, will invoke ```sendCanMessage``` with ID and payload.