#!/bin/sh

CH=$1
LOCATION=$2

/usr/bin/gst-launch-1.0 rtspsrc location=$LOCATION latency=1000 ! rtph264depay ! mpegtsmux ! rtksink ch=$CH &

