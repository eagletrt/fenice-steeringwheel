# Steering Wheel

Welcome to the Fenice Steering Wheel documentation. Fenice Steering Wheel is a
modular Qt application that interacts with the rest of the vehicle and displays
useful information to the team and the pilot during preparation or race.

In production the software is deployed to a Raspberry Pi 3b+ into a custom PCB
that allows simple communications with all the I/O of the device.

During development the software can be tested on any x86 machine that supports
Qt natively. Most of the custom I/O is abstracted so complex interaction can
still be tested.

```{toctree}
:caption: 'Development:'
:maxdepth: 2

development/qt
```

%

```{toctree}
:caption: 'Interface:'
:maxdepth: 2

interface/tabs
```

%

% Other useful stuff

% ----

% * :ref:`genindex`

% * :ref:`search`
