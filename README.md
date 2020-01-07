# Charater Dummy Driver
  * Base [jserv/dummy-driver](https://github.com/jserv/dummy-driver) to develop.
  * Environment 
    * Ubuntu 16.04 LTS (x86_64)
    * uname -r, 4.15.0-72-generic

# Test the system calls to copy data between kernel and user space
* Behavior:
  * AP read a binary file and write to device driver, 64KB/time.
  * AP read the total size of written data from driver.

* Please install kernel headers first:
```shell
sudo apt-get install linux-headers-generic
```

* Usage:
```shell
$ make check
```

* Generate binary file for test
```shell
$ dd if=/dev/zero of=test.bin bs=65K count=1

```

