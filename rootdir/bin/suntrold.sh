#!/vendor/bin/sh

setprop bpf.progs_loaded 1

# Start suntrold
/vendor/bin/suntrold &
sleep 0.5
chmod 0777 /dev/socket/suntory/suntrold.sock 2>/dev/null

# Sleep infinite to prevent that suntrold's subprocess gets killed
tail -f /dev/null
