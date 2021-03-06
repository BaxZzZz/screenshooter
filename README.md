[![Build Status](https://travis-ci.org/BaxZzZz/screenshooter.svg?branch=master)](https://travis-ci.org/BaxZzZz/screenshooter) 

**Description:**

Application for catching screenshots of all active users' displays.

**Configuration:**

Before starting the application make sure that the account used for launching the app is able to access other users' displays. To provide the access do the following:

<pre>
sudo xauth merge ~otherusename/.Xauthority
sudo chown currentusername:currentusername ~/.Xauthority
</pre>

Where:
+ otherusename - account name to which display you need the access
+ currentusername - current account name

**Dependencies:**

Screenshooter uses cmake, and depends on libtclap-1.2.1, libjpeg-1.5.1, libX11-1.6.5

If you are on debian-based distro you can grab them with:

<pre>
sudo apt install libjpeg-turbo8-dev libtclap-dev libx11-dev
</pre>

If you are on Gentoo Linux distro you can grab them with:

<pre>
sudo emerge -av media-libs/libjpeg-turbo dev-cpp/tclap x11-libs/libX11
</pre>


**Command line options:**

<pre>
USAGE:

   ./screenshooter  [-d] [-p <string>] [--] [--version] [-h]

Where:

   -d,  --daemon
     Daemonize process

   -p <string>,  --path <string>
     Path for screenshots

   --,  --ignore_rest
     Ignores the rest of the labeled arguments following this flag.

   --version
     Displays version information and exits.

   -h,  --help
     Displays usage information and exits.
</pre>
