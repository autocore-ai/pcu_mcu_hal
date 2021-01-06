# zenoh C Client API on mcu

It is a C API for pure clientss, and does not support peer-to-peer communication.


-------------------------------
##How to build it

To build and flash MCU HAL, follow the instructions [How to Flash](docs/How_to_flash.md)


-------------------------------
## Running the Examples

### Starting the zenoh Network Service
Assuming you've intalled  image of the **zenoh** network router on pcu, then simply do:

```bash
$ RUST_LOG=debug ./zenohd -l tcp/192.168.1.239:7447
```
### Basic Pub/Sub Example
Assuming that (1) you are running the **zenoh** network router,  and (2) you are start vStartPubTask on mcu, do:
```bash
$ ./zn_sub -e tcp/192.168.1.239:7447
```

Assuming that (1) you are running the **zenoh** network router,  and (2) you are start vStartSubTask on mcu, do:
```bash
$ ./zn_pub -e tcp/192.168.1.239:7447
```

