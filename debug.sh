#!/bin/bash
#
gdb -ex "file ./vmlinux" \
    -ex "add-symbol-file ./fs_extract/pwhrootkit.ko 0xffffffffc0201000" \
    -ex "target remote localhost:1234"
