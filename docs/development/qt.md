# Building Qt for the Raspberry Pi

This guide is an edited version of the [original](https://github.com/abhiTronix/raspberry-pi-cross-compilers/blob/master/QT_build_instructions.md)
by [abhiTronix](https://github.com/abhiTronix).

## Prerequites

### A. Hardware

- **Host:** Any x86 / x86_64 AMD / Intel machine
- **Target:** Raspberry Pi any variant / module

### B. Software

- **Host:** Any Linux machine *(Ubuntu 20.04 Tested)*
- **Target:** [Any Raspberry Pi Linux 32-bit
  OS](https://www.raspberrypi.org/software/operating-systems/)
  *(Raspbian Buster Tested)*

### C. Others

- **Storage and Time Requirements:** The build directory takes around
  \~10GB space and about 2-5 hours to complete *(based on dependencies &
  Host Machine Specifications)*.
- **Networking:** Your Target Machine *(Raspberry Pi)* and Host Machine
  *(where you cross-compiling)* both must have internet access, and
  must be on same network to follow these instructions.

## Setup the Target Machine

### 1. Start from Scratch *(Optional)*

**Important:** If you just brought a new Raspberry Pi or wanted to start
from scratch just follow along. Otherwise, if you already has your
Raspberry Pi setup, running, and Network Ready, then just skip to [step
2](#2-set-up-ssh).

**Note:** This section assume you have atleast 10GB SDcard for
installing Raspbian Buster OS and a Laptop/PC for uploading it.

#### 1.1. Download Softwares & Prepare the SD card

- Download the latest version of Raspbian (Buster) from
  [here](https://www.raspberrypi.org/software/operating-systems/) on
  your laptop/pc.
- You will be needing an image writer to write the downloaded OS into
  the SD card *(micro SD card in our case)*. So download the
  open-source **“win32 disk imager”** from
  [here](https://sourceforge.net/projects/win32diskimager/files/Archive/),
  OR you can also use [Balena Etcher](https://www.balena.io/etcher/)
  instead.
- Insert the SD card into the laptop/pc and run the image writer. Once
  open, browse and select the downloaded Raspbian image file. Select
  the correct device, that is the drive representing the SD card.
  **Note:***If the drive (or device) selected is different from the
  SD card then the other selected drive will become corrupted.***SO
  BE CAREFUL!**
- Once the write is complete, eject the SD card and insert it into the
  Raspberry Pi and turn it on. It should start booting up.
- Please remember that after booting the Pi, there might be situations
  when the user credentials like the “username” and password will be
  asked. Raspberry Pi comes with a default username `pi` and password
  `raspberry` and so use it whenever it is being asked.

#### 1.2 Set up Network

Now the you have your Raspberry Pi up and Running, its time to connect
it your network with one of following ways:

- [If you have Monitor](https://www.raspberrypi.org/documentation/configuration/wireless/desktop.md).
- [If you don’t have Monitor](https://www.raspberrypi.org/documentation/configuration/wireless/wireless-cli.md)
- [Any other way](https://www.raspberrypi.org/documentation/configuration/wireless/)

### 2. Set up SSH

- **If you have Monitor:** On the Raspberry Pi terminal, type:
  `sudo raspi-config` and menu should pop up on your terminal. To
  enable SSH, go to: `Interfacing Options` -> `SSH` -> `Yes`, and
  Click `OK` to enable it. Choose `Finish` finally and exit.
- **If you don’t have Monitor:** After setting up the network, if you
  don’t have monitor or you operating it remotely. Then, enable SSH by
  just taking out your SD card, and hook it your computer, and simply
  create an empty file called `ssh` in the `/boot/parition` path
  inside SD card. Now insert back SD card into the Raspberry Pi.

### 3. Open Terminal

- **From another Laptop/PC using SSH:** To connect to your Pi from a
  different computer, copy and paste the following command into the
  terminal window but replace `192.160.1.47` with the IP address of
  the Raspberry Pi. Use `Ctrl + Shift + V` to paste in the terminal.

  ```sh
  ssh pi@192.168.1.47
  ```

  It will ask for password, and if not changed, it is default
  (`raspberry`), and so use it whenever it is being asked.

  **Note:** It is possible to configure your Raspberry Pi to allow
  access from another computer without needing to provide a password
  each time you connect. *For more details,*[see
  here](https://www.raspberrypi.org/documentation/remote-access/ssh/passwordless.md).

- **On Raspberry Pi directly with a Monitor:** Just search “Terminal”
  and click on it.

### 4. Enable GL (FAKE KMS)

To enable Fake KMS, type `sudo raspi-config` on your terminal to open
a menu, then go to: `Advanced Options` -> `A8 GL Driver` ->
`G2 GL (Fake KMS)` That should enable KMS. Choose `Finish` finally
and exit.

**Note:** If you are using a minimal build, you may be prompted to
download some updates before this option becomes available. If asked, do
so.

### 5. Enable Development Sources

You need to edit your sources list to enable development sources. To do
this, enter the following command into pi terminal:

```sh
sudo nano /etc/apt/sources.list
```

In the nano text editor, uncomment the following line by removing the
`#` character from following line:

```sh
deb-src http://raspbian.raspberrypi.org/raspbian/ buster main contrib non-free rpi
```

When done, press `Ctrl+O` and then `ENTER` to quit.

### 6. Update the system

Run the following commands in terminal to update the system

```sh
sudo apt update
sudo apt dist-upgrade
```

### 7. Enable rsync with elevated rights

Later in this guide, we will be using the `rsync` command to sync
files between the Host PC/Laptop and the Raspberry Pi. For some of these
files, root rights (i.e. sudo) is required internally.

You can do this with a single terminal command as follows:

```sh
echo "$USER ALL=NOPASSWD:$(which rsync)" | sudo tee --append /etc/sudoers
```

That’s it. Now `rsync` should be setup to run with `sudo` if needed.

### 8. Install the important Development Packages

Run the following commands in Raspberry Pi terminal to install the
required packages:

```sh
sudo apt install build-essential cmake unzip pkg-config gfortran
sudo apt build-dep qt5-qmake libqt5gui5 libqt5webengine-data libqt5webkit5 libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0 gdbserver
sudo apt install libxcb-randr0-dev libxcb-xtest0-dev libxcb-shape0-dev libxcb-xkb-dev
```

### 9. Additional packages (Optional)

You can install these packages if you want additional multimedia and
bluetooth capability with your QT binaries:

```sh
# additional (multimedia) packages
sudo apt install libjpeg-dev libpng-dev libtiff-dev
sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev
sudo apt install libxvidcore-dev libx264-dev
# audio packages
sudo apt install libopenal-data libsndio7.0 libopenal1 libopenal-dev pulseaudio
# bluetooth packages
sudo apt install bluez-tools
sudo apt install libbluetooth-dev
# gstreamer (multimedia) packages
sudo apt install libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
sudo apt install libgstreamer1.0-dev  libgstreamer-plugins-base1.0-dev
```

### 10. Create directory for QT Deployment

Now we create directories where the built QT Binaries will be deployed
to your the Rasberry Pi, with following commands:

```sh
sudo mkdir /usr/local/qt5.15
sudo chown -R pi:pi /usr/local/qt5.15
```

Also don’t forget to setup Important Symlinks as follows:
**(Important)**

```sh
sudo ln -sf -r /usr/include/arm-linux-gnueabihf/asm /usr/include
sudo ln -sf -r /usr/include/arm-linux-gnueabihf/gnu /usr/include
sudo ln -sf -r /usr/include/arm-linux-gnueabihf/bits /usr/include
sudo ln -sf -r /usr/include/arm-linux-gnueabihf/sys /usr/include
sudo ln -sf -r /usr/include/arm-linux-gnueabihf/openssl /usr/include
sudo ln -sf /usr/lib/arm-linux-gnueabihf/crtn.o /usr/lib/crtn.o
sudo ln -sf /usr/lib/arm-linux-gnueabihf/crt1.o /usr/lib/crt1.o
sudo ln -sf /usr/lib/arm-linux-gnueabihf/crti.o /usr/lib/crti.o
```

That’s it for Raspberry Pi setup.

## Setup the Host Machine

Now Raspberry Pi Side all setup, Let’s focus on commands for our Host
Machine, i.e. PC/Laptop, where you going to cross-compile the QT
Binaries for your Raspberry Pi.

**Important:** Make sure your Raspberry Pi and this Host machine *(where
you cross-compiling)* MUST be on the SAME Network.

### 1. Update the Host Machine

First of all, Run the following commands to update your system and
install important dependancies:

```sh
sudo apt update
sudo apt dist-upgrade
sudo apt install build-essential cmake unzip gfortran
sudo apt install gcc git bison python gperf pkg-config gdb-multiarch wget
sudo apt-get -y install gcc g++ gperf flex texinfo gawk bison openssl pigz libncurses-dev autoconf automake tar figlet
```

### 2. Setting up the directory structure

You can use these following commands to create “rpi-qt” to use as
workspace for building QT Binaries:

```sh
sudo mkdir ~/rpi-qt
sudo mkdir ~/rpi-qt/build
sudo mkdir ~/rpi-qt/tools
sudo mkdir ~/rpi-qt/sysroot
sudo mkdir ~/rpi-qt/sysroot/usr
sudo mkdir ~/rpi-qt/sysroot/opt
sudo chown -R 1000:1000 ~/rpi-qt
cd ~/rpi-qt
```

**Note:** Ensure the last command should have changed your current
directory to `~/rpi-qt`. If not, run the last line again to make sure
you are inside it, as the next steps assume you’re running your commands
from this directory.

### 3. Download & Extract QT Source

#### A. Download Binary

Now, we can download the Latest source files for QT LTS
(i.e. `v5.15.2`) by running following Terminal command to download the
source files:

```sh
sudo wget http://download.qt.io/archive/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz
```

**Note:** You can also [manually download
file](http://download.qt.io/archive/qt/5.15/5.15.2/single/qt-everywhere-src-5.15.2.tar.xz)
through browser, and place it in the `~/rpi-qt` directory.

#### B. Extract Binary

Extract the downloaded `tar` file with the following command:

```sh
sudo tar xfv qt-everywhere-src-5.15.2.tar.xz
```

### 4. Patching QT Source

We need to slightly modify the a mkspec file within the source files to
allow us to use our cross compiler. We will copy an existing directory
within the source files, and modify the name of the directory and the
contents of the `qmake.conf` file within that directory to follow the
name of our compiler. To do this, run the following two command:

```sh
cp -R qt-everywhere-src-5.15.2/qtbase/mkspecs/linux-arm-gnueabi-g++ qt-everywhere-src-5.15.2/qtbase/mkspecs/linux-arm-gnueabihf-g++

sed -i -e 's/arm-linux-gnueabi-/arm-linux-gnueabihf-/g' qt-everywhere-src-5.15.2/qtbase/mkspecs/linux-arm-gnueabihf-g++/qmake.conf
```

### 5. Download & Extract the Precompiled Cross-Compiler

Let’s first change into `tools` directory for downloading our
Precompiled Cross-compiler with the following command:

```sh
cd ~/rpi-qt/tools
```

**Note:** Ensure the last command should have changed your current
directory to `~/rpi-qt/tools` now. If not, run it again.

#### A. Copy Binary URL

Copy URL from one of following Precompiled Compressed Base-Toolchain
*(for maximum compatability)* based on your Raspberry Pi Variant and OS
you installed on it, from below:

```{eval-rst}
.. list-table::
   :widths: 25 25 50
   :header-rows: 1

   *  - Raspberry Pi Board
      - Stretch(32-bit) OS
      - Buster(32-bit) OS

   *  - Raspberry Pi - *Zero/W/WH & 1 Model A/B/A+/B+*
      - https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Stretch/GCC%206.3.0/Raspberry%20Pi%201%2C%20Zero/cross-gcc-6.3.0-pi_0-1.tar.gz
      - https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Buster/GCC%208.3.0/Raspberry%20Pi%201%2C%20Zero/cross-gcc-8.3.0-pi_0-1.tar.gz

   *  - Raspberry Pi - *2 & 3 Model A/B*
      - https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Stretch/GCC%206.3.0/Raspberry%20Pi%202%2C%203/cross-gcc-6.3.0-pi_2-3.tar.gz
      - https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Buster/GCC%208.3.0/Raspberry%20Pi%202%2C%203/cross-gcc-8.3.0-pi_2-3.tar.gz

   *  - Raspberry Pi - *3 & 4 Model A+/B+ & Compute 3/3-lite/3+*
      - https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Stretch/GCC%206.3.0/Raspberry%20Pi%203A%2B%2C%203B%2B%2C%204/cross-gcc-6.3.0-pi_3%2B.tar.gz
      - https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Buster/GCC%208.3.0/Raspberry%20Pi%203A%2B%2C%203B%2B%2C%204/cross-gcc-8.3.0-pi_3%2B.tar.gz
```

**Note:** You can also use the [latest cross-compiler
binaries](https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/)
instead. But they are not tested.

#### B. Download Binary

After that, paste your copied URL and run the following command to
download the Cross-compiler:

```sh
wget <Copied Binary URL goes here> #for e.g. => wget https://sourceforge.net/projects/raspberry-pi-cross-compilers/files/Raspberry%20Pi%20GCC%20Cross-Compiler%20Toolchains/Buster/GCC%208.3.0/Raspberry%20Pi%202%2C%203/cross-gcc-8.3.0-pi_2-3.tar.gz
```

#### C. Extract Binary

Once it is downloaded, we can extract it using the following command:

```sh
tar xf cross-gcc-*.tar.gz
```

### 6. Sync Raspberry Pi sysroot (Most Important)

First, let’s move back into the rpi folder as needed for the next
sections:

```sh
cd ~/rpi-qt
```

Now, we need to sync up our sysroot folder with the system files from
the Raspberry Pi. We will be using `rsync` that let us sync
*(i.e. copy)* files from the Raspberry Pi with appropriate permission
onto your Host Machine, potentially saving you alot of time.

To do this, enter the following commands one by one into your terminal
*(change \`\`192.168.1.47\`\` with the IP address of your Raspberry Pi
present on the same network)*:

- **Command 1:**
  `rsync -avz --rsync-path="sudo rsync" --delete pi@192.168.1.47:/lib sysroot`
- **Command 2:**
  `rsync -avz --rsync-path="sudo rsync" --delete pi@192.168.1.47:/usr/include sysroot/usr`
- **Command 3:**
  `rsync -avz --rsync-path="sudo rsync" --delete pi@192.168.1.47:/usr/lib sysroot/usr`
- **Command 4:**
  `rsync -avz --rsync-path="sudo rsync" --delete pi@192.168.1.47:/opt/vc sysroot/opt`

**Note:** Double check after each of the above commands that all the
files have been copied to `~/rpi-qt/sysroot` folder. There will be an
information message if there were any issues.

### 7. Fix symbolic links

The files we copied in the previous step still have symbolic links
pointing to the file system on the Raspberry Pi. We need to alter this
so that they become relative links from the new sysroot directory on the
host machine. We can do this with a python script, which we can download
as follows:

```sh
wget https://raw.githubusercontent.com/abhiTronix/rpi_rootfs/master/scripts/sysroot-relativelinks.py
```

Once it is downloaded, you just need to make it executable and run it,
using the following commands:

```sh
sudo chmod +x sysroot-relativelinks.py
./sysroot-relativelinks.py sysroot
```

### 8. Configure QT Build

Let’s move into the `build` directory for further steps, as we don’t
want to build within that source directory as its crowded, so we will
access it from within this this directory:

```sh
cd ~/rpi-qt/build
```

Finally, Now we can configure our QT build. We need to run the
`configure` script inside QT source to configure our build. Run
following command to configure the build, including all the necessary
options:

```sh
CROSS_COMPILER_LOCATION=$HOME/rpi-qt/tools/cross-pi-gcc-*

../qt-everywhere-src-5.15.2/configure -release -opengl es2  -eglfs -device linux-rasp-pi4-v3d-g++ -device-option CROSS_COMPILE=$(echo $CROSS_COMPILER_LOCATION)/bin/arm-linux-gnueabihf- -sysroot ~/rpi-qt/sysroot/ -prefix /usr/local/qt5.15 -extprefix ~/rpi-qt/qt5.15 -opensource -confirm-license -skip qtscript -skip qtwayland -skip qtwebengine -nomake tests -make libs -pkg-config -no-use-gold-linker -v -recheck -L$HOME/rpi-qt/sysroot/usr/lib/arm-linux-gnueabihf -I$HOME/rpi-qt/sysroot/usr/include/arm-linux-gnueabihf
```

The configure script may take a few minutes to complete.

#### 8.1 Check Configure Output

Once it is completed you should get a summary of what has been
configured. Make sure the following options appear:

```sh
Configure summary:

Building on: linux-g++ (x86_64, CPU features: mmx sse sse2)
Building for: devices/linux-rasp-pi4-v3d-g++ (arm, CPU features: neon)
Target compiler: gcc 8.3.0
Configuration: cross_compile compile_examples enable_new_dtags largefile neon precompile_header shared shared rpath release c++11 c++14 c++17 c++1z concurrent dbus reduce_exports stl
```

#### 8.2 Check if EGLFS enabled

```sh
QPA backends:
  EGLFS .................................. yes  [SHOULD BE YES]
  EGLFS details:
    EGLFS OpenWFD ........................ no
    EGLFS i.Mx6 .......................... no
    EGLFS i.Mx6 Wayland .................. no
    EGLFS RCAR ........................... no
    EGLFS EGLDevice ...................... yes  [SHOULD BE YES]
    EGLFS GBM ............................ yes
    EGLFS VSP2 ........................... no
    EGLFS Mali ........................... no
    EGLFS Raspberry Pi ................... no   [SHOULD BE NO]
    EGLFS X11 ............................ yes
```

If the your configuration summary doesn’t have the EGLFS features set to
what’s shown above, something has probably gone wrong. You can look at
the config.log file in the build directory to try and diagnose what the
issue might be.

If all looks good and all libraries you need have been installed we can
continue to the next section

### 9. Build QT Source

Our build has been configured now, and it is time to actually build the
source files, and run the following command:

**Important:** Ensure you are still in the `~/rpi-qt/build` directory

```sh
make -j$(nproc)
```

**Note:** `-j$(nproc)` option indicates that the job should be spread
into mutliple threads and run in parallel on available cores.

☕️ This process will take some time!

### 10. Install QT Source

Once it is completed, we can install the built package using the
following command:

```sh
make install
```

This should install the files in the correct directories

### 11. Deploy QT to Raspberry Pi

First move back into the rpi folder using the following command:

```sh
cd ~/rpi-qt
```

Now, We can now deploy built QT Binaries *(contained in \`\`qt5.15\`\`
folder in \`\`~/rpi-qt\`\` directory)* back to our Raspberry Pi, again using
`rsync` command. Just run the following command *(change
\`\`192.168.1.47\`\` with the IP address of your Raspberry Pi present on the
same network)*:

```sh
rsync -avz --rsync-path="sudo rsync" qt5.15 pi@192.168.1.47:/usr/local
```

## Final Step for Target Machine

### Update linker on Raspberry Pi

Enter the following command to update the device letting the linker to
find the new QT binary files:

```sh
echo /usr/local/qt5.15/lib | sudo tee /etc/ld.so.conf.d/qt5.15.conf
sudo ldconfig
```

**For Raspberry Pi 2:** If you’re facing issues with running the
example, try to use `00-qt5pi.conf` instead of `qt5pi.conf`, in the
above command.

🍻 *That should be it! You have now succesfully installed latest QT
5.15.2 on the Raspberry Pi.*
