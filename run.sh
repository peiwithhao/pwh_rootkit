#!/bin/sh
qemu-system-x86_64 \
    -m 1024M \
    -kernel ./bzImage \
    -initrd  ./rootfs.cpio \
    -append "root=/dev/ram console=ttyS0 oops=panic panic=1 loglevel=3 quiet nokaslr" \
    -cpu kvm64,+smep \
    -smp cores=2,threads=1 \
    -netdev user,id=t0, -device e1000,netdev=t0,id=nic0 \
    --enable-kvm \
    -nographic \
    -s
