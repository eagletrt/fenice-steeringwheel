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
$ ./chimera-deploy.sh
```



