usb_connect
if { [as_device_id] } {
  as_write  printer.bin
  as_verify printer.bin
}
usb_close
