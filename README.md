*Description*

Application for catching screenshots of all active users' displays.

*Configuration:*

Before starting the application make sure that the account used for launching the app is able to access other users' displays. To provide the access do the following:

<pre>
sudo xauth merge ~otherusename/.Xauthority
sudo chown currenusername:cureenusername ~/.Xauthority
</pre>

Where:
+ otherusename - account name to which display you need the access
+ currenusername - current account name

<pre>

*Command line options*

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
