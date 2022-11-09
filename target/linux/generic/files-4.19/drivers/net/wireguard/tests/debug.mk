REMOTE_HOST1 ?= root@172.16.48.128
REMOTE_HOST2 ?= root@172.16.48.129
REMOTE_HOST3 ?= root@172.16.48.130
PEER1 := [Peer]\nPublicKey=UQGBaem0U6JjIObMQzunZ2Euv8MMYcUUdWKJV87WDE8=\nAllowedIPs=192.168.2.1/32,abcd::1/128\nEndpoint=$(subst root@,,$(REMOTE_HOST1)):12912\n
PEER2 := [Peer]\nPublicKey=tNXrD6GCvHRNgoZ/D/BmTbTbzoVGZh0R2V6rzY6hwl4=\nAllowedIPs=192.168.2.2/32,abcd::2/128\nEndpoint=$(subst root@,,$(REMOTE_HOST2)):21281\n
PEER3 := [Peer]\nPublicKey=gLvFUb1FTyoACC/yZNqGLKnNkt+w30JEvfFChDVuewo=\nAllowedIPs=192.168.2.3/32,abcd::3/128\nEndpoint=$(subst root@,,$(REMOTE_HOST3)):54812\n
SSH_OPTS := -q -o ControlMaster=auto -o ControlPath=.ssh-deployment.sock
SSH_OPTS1 := $(SSH_OPTS)-1
SSH_OPTS2 := $(SSH_OPTS)-2
SSH_OPTS3 := $(SSH_OPTS)-3
RSYNC_OPTS := --exclude="*.o" --exclude="*.mod.c" --exclude="tests/qemu" --exclude "*.ko" --exclude="*.cmd" -avP

MAYBE_DEBUG := "debug"
ifeq ($(D),0)
MAYBE_DEBUG :=
endif

insert: debug
	-modinfo -F depends wireguard.ko | tr ',' '\n' | sudo xargs -n 1 modprobe
	-sudo rmmod wireguard
	-sudo insmod wireguard.ko

test: insert
	sudo PATH="$$PATH:/usr/sbin:/sbin:/usr/bin:/bin:/usr/local/sbin:/usr/local/bin" ./tests/netns.sh

test-qemu:
	$(MAKE) -C tests/qemu

remote-test:
	ssh $(SSH_OPTS1) -Nf $(REMOTE_HOST1)
	rsync --rsh="ssh $(SSH_OPTS1)" $(RSYNC_OPTS) . $(REMOTE_HOST1):wireguard-build/
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'make -C wireguard-build test -j$$(nproc)'
	ssh $(SSH_OPTS1) -O exit $(REMOTE_HOST1)

remote-run-1:
	ssh $(SSH_OPTS1) -Nf $(REMOTE_HOST1)
	rsync --rsh="ssh $(SSH_OPTS1)" $(RSYNC_OPTS) . $(REMOTE_HOST1):wireguard-build/
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'ip l d wg0; rmmod wireguard; cd wireguard-build && make -j$$(nproc) $(MAYBE_DEBUG) && make install'
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'ip l a wg0 type wireguard'
	printf '[Interface]\nListenPort=12912\nPrivateKey=4IoHwlfTyKb9Z9W1YPmBmZvSiU6qcs0oa4xnjAEm/3U=\n$(PEER2)$(PEER3)' | ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'cat > config.conf'
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'wg setconf wg0 config.conf'
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'ip l set up dev wg0'
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'ip a a 192.168.2.1/24 dev wg0'
	ssh $(SSH_OPTS1) $(REMOTE_HOST1) 'ip a a abcd::1/120 dev wg0'
	ssh $(SSH_OPTS1) -O exit $(REMOTE_HOST1)


remote-run-2:
	ssh $(SSH_OPTS2) -Nf $(REMOTE_HOST2)
	rsync --rsh="ssh $(SSH_OPTS2)" $(RSYNC_OPTS) . $(REMOTE_HOST2):wireguard-build/
	ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'ip l d wg0; rmmod wireguard; cd wireguard-build && make -j$$(nproc) $(MAYBE_DEBUG) && make install'
	ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'ip l a wg0 type wireguard'
	printf '[Interface]\nListenPort=21281\nPrivateKey=kEKL+m4h5xTn2cYKU6NTEv32kuXHAkuqrjdT9VtsnX8=\n$(PEER1)$(PEER3)' | ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'cat > config.conf'
	ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'wg setconf wg0 config.conf'
	ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'ip l set up dev wg0'
	ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'ip a a 192.168.2.2/24 dev wg0'
	ssh $(SSH_OPTS2) $(REMOTE_HOST2) 'ip a a abcd::2/120 dev wg0'
	ssh $(SSH_OPTS2) -O exit $(REMOTE_HOST2)

remote-run-3:
	ssh $(SSH_OPTS3) -Nf $(REMOTE_HOST3)
	rsync --rsh="ssh $(SSH_OPTS3)" $(RSYNC_OPTS) . $(REMOTE_HOST3):wireguard-build/
	ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'ip l d wg0; rmmod wireguard; cd wireguard-build && make -j$$(nproc) $(MAYBE_DEBUG) && make install'
	ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'ip l a wg0 type wireguard'
	printf '[Interface]\nListenPort=54812\nPrivateKey=qFunvj5kgENrtWn754hNBLrk5mMA+8+evVtnI2YqWkk=\n$(PEER1)$(PEER2)' | ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'cat > config.conf'
	ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'wg setconf wg0 config.conf'
	ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'ip l set up dev wg0'
	ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'ip a a 192.168.2.3/24 dev wg0'
	ssh $(SSH_OPTS3) $(REMOTE_HOST3) 'ip a a abcd::3/120 dev wg0'
	ssh $(SSH_OPTS3) -O exit $(REMOTE_HOST3)

remote-run:
	$(MAKE) -j3 remote-run-1 remote-run-2 remote-run-3
