Host implementation of Virtual Radio Transport (VITA-49)

The vrt subdirectory builds libvrt, a library that knows how to create
and parse VITA-49 packets.  It also includes code that does high speed
UDP input of VRT frames.

This code was developed and tested with a receiver that output samples
at 30MS/s, 16-bit complex baseband (120MB/s).  After accounting for
VRT, UDP and ethernet overhead, it ran within a few percent of the
theoretical maximum for gigabit ethernet.  We used jumbo frames with a
UDP payload of 8192 bytes.
