#!/bin/sh

if [ -x /rom/usr/bin/curl ]; then
    /usr/bin/curl -V >/dev/null 2>&1 && exec /usr/bin/curl "$@"
    exec /rom/usr/bin/curl "$@"
fi
exec /usr/bin/curl "$@"
