#!/vendor/bin/sh

setprop bpf.progs_loaded 1

# Start suntrold
/vendor/bin/suntrold

# Sleep infinite to prevent that suntrold's subprocess gets killed
tail -f /dev/null
