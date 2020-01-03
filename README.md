# PCIe Dummy Driver
  * Base [jserv/dummy-driver](https://github.com/jserv/dummy-driver) to develop.

# Test the system calls to copy data between kernel and user space

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

