# Steering Wheel 

<p align="center">
   <img width="60%" src="https://i.imgur.com/DnmX57U.png">
</p>
<p align="center">
   <kbd>Qt project for the steering wheel UI and backend.</kbd>
</p>

## Development

Clone this repository & all the submodules:

```
$ git clone --recurse-submodules https://github.com/eagletrt/fenice-steeringwheel
```

With Qt Creator open one of the project files:

- `fenice-steering-x86.pro` Desktop version of the steering wheel, useful for debugging.

- `fenice-steering-rpi.pro` ARM project with full support for the Raspberry Pi 3B+ and all the peripheral attached to the production steering wheel.

If you prefer to not use Qt creator you can use the scripts inside [`/tools`](./tools):

```
tools/
├── run     run the x86 project.
├── make    build the x86 project.
├── fmt     run clang format.
├── env     setup env variables needed for a Qt build
└── vcan0   setup virtual can interface
```

### Buttons

- On the Raspberry Pi, buttons states are fetched from:
   - GPIOs:
      - start & stop
   - mcp23017:
      - ... all the other ...

- On x86, buttons are mapped to the keyboard, following this table:

   Key           |Control
   --------------|------------------------
   q:            |exit, run / stop (0)
   a:            |send , start     (1)
   d:            |enter, down      (2)
   r:            |marker, telemetry(3)
   z:            |paddle_btm_left  (4)
   x:            |paddle_btm_right (5)
   c:            |paddle_top_left  (6)
   v:            |paddle_top_right (7)
   s:            |button_start     (8)
   1-6:          |map              (11-20)
   1-6 + ctrl:   |pump             (21-30)
   1-6 + alt:    |traction_control (31-40)


### Leds

- On the Raspberry Pi, leds are controlled by interacting with the TLC59108 
driver through I<sup>2</sup>C.
- On x86 leds statuses are logged in the console.

## Rasberry Pi 3B+ Qt Build

To create a Raspberry Pi build it's highly advised to use Qt Creator.

To get the complete Qt toolchain for the Raspberry Pi 3B+, clone the build repo:

```
$ git clone https://github.com/eagletrt/fenice-qt-build
```

This repository contains prebuilt binaries for the Raspberry Pi 3B+. You only 
need to call `qmake`, which can be found inside the 
[`/bin`](https://github.com/eagletrt/fenice-qt-build/tree/master/bin) folder.
