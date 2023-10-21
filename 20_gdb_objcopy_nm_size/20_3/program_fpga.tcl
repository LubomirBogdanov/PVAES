connect
targets
targets 4
fpga ./boot/bitstream.bit
targets 2
dow ./boot/fsbl.elf
con
after 1000
dow ./boot/cortex.elf
con
targets 6
dow ./debug/main.elf
con
