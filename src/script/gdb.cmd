target remote localhost:4242
monitor endian little
monitor speed 1000
monitor reset
monitor sleep 100
monitor speed 2000
monitor flash device = nrf51
file ./AMJPureBLEKbd.elf
load
monitor reset
break main
continue
