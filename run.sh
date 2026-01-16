make
./make_iso.sh
qemu-system-x86_64 -m 2G -cdrom owos-c.iso # -d int,cpu_reset,guest_errors
