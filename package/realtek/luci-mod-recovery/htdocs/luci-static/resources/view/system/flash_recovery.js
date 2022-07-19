'use strict';
'require view';
'require dom';
'require form';
'require rpc';
'require fs';
'require ui';

var isReadonlyView = !L.hasViewPermission();

var callSystemValidateFirmwareImage = rpc.declare({
	object: 'system',
	method: 'validate_firmware_image',
	params: [ 'path' ],
	expect: { '': { valid: false, forcable: true } }
});

function findStorageSize(procmtd, procpart) {
	var kernsize = 0, rootsize = 0, wholesize = 0;

	procmtd.split(/\n/).forEach(function(ln) {
		var match = ln.match(/^mtd\d+: ([0-9a-f]+) [0-9a-f]+ "(.+)"$/),
		    size = match ? parseInt(match[1], 16) : 0;

		switch (match ? match[2] : '') {
		case 'linux':
		case 'firmware':
			if (size > wholesize)
				wholesize = size;
			break;

		case 'kernel':
		case 'kernel0':
			kernsize = size;
			break;

		case 'rootfs':
		case 'rootfs0':
		case 'ubi':
		case 'ubi0':
			rootsize = size;
			break;
		}
	});

	if (wholesize > 0)
		return wholesize;
	else if (kernsize > 0 && rootsize > kernsize)
		return kernsize + rootsize;

	procpart.split(/\n/).forEach(function(ln) {
		var match = ln.match(/^\s*\d+\s+\d+\s+(\d+)\s+(\S+)$/);
		if (match) {
			var size = parseInt(match[1], 10);

			if (!match[2].match(/\d/) && size > 2048 && wholesize == 0)
				wholesize = size * 1024;
		}
	});

	return wholesize;
}


var mapdata = { actions: {}, config: {} };

return view.extend({
	load: function() {
		var tasks = [
			L.resolveDefault(fs.stat('/lib/upgrade/platform.sh'), {}),
			fs.trimmed('/proc/sys/kernel/hostname'),
			fs.trimmed('/proc/mtd'),
			fs.trimmed('/proc/partitions'),
			fs.trimmed('/proc/mounts')
		];

		return Promise.all(tasks);
	},

	handleBackup: function(ev) {
		var form = E('form', {
			method: 'post',
			action: L.env.cgi_base + '/cgi-backup',
			enctype: 'application/x-www-form-urlencoded'
		}, E('input', { type: 'hidden', name: 'sessionid', value: rpc.getSessionID() }));

		ev.currentTarget.parentNode.appendChild(form);

		form.submit();
		form.parentNode.removeChild(form);
	},

	handleFirstboot: function(ev) {
		if (!confirm(_('Do you really want to erase all settings?')))
			return;

		ui.showModal(_('Erasing...'), [
			E('p', { 'class': 'spinning' }, _('The system is erasing the configuration partition now.'))
		]);

		fs.exec('/sbin/firstboot', [ '-y' ])
			.then(L.bind(function(res) {
				if (res.code != 0) {
					ui.addNotification(null, [
						E('p', _('The reset command failed with code %d').format(res.code)),
						res.stderr ? E('pre', {}, [ res.stderr ]) : ''
					]);
					L.raise('Error', 'Reset failed');
				}
				ui.addNotification(null, E('p', _('Reset success')), 'info');
			}, this))
			.catch(function(e) { ui.addNotification(null, E('p', e.message)) })
			.finally(ui.hideModal);
	},

	handleRestore: function(ev) {
		return ui.uploadFile('/tmp/backup.tar.gz', ev.target)
			.then(L.bind(function(btn, res) {
				btn.firstChild.data = _('Checking archive…');
				return fs.exec('/bin/tar', [ '-tzf', '/tmp/backup.tar.gz' ]);
			}, this, ev.target))
			.then(L.bind(function(btn, res) {
				if (res.code != 0) {
					ui.addNotification(null, E('p', _('The uploaded backup archive is not readable')));
					return fs.remove('/tmp/backup.tar.gz');
				}

				ui.showModal(_('Apply backup?'), [
					E('p', _('The uploaded backup archive appears to be valid and contains the files listed below. Press "Continue" to restore the backup, or "Cancel" to abort the operation.')),
					E('pre', {}, [ res.stdout ]),
					E('div', { 'class': 'right' }, [
						E('button', {
							'class': 'btn',
							'click': ui.createHandlerFn(this, function(ev) {
								return fs.remove('/tmp/backup.tar.gz').finally(ui.hideModal);
							})
						}, [ _('Cancel') ]), ' ',
						E('button', {
							'class': 'btn cbi-button-action important',
							'click': ui.createHandlerFn(this, 'handleRestoreConfirm', btn)
						}, [ _('Continue') ])
					])
				]);
			}, this, ev.target))
			.catch(function(e) { ui.addNotification(null, E('p', e.message)) })
			.finally(L.bind(function(btn, input) {
				btn.firstChild.data = _('Upload archive...');
			}, this, ev.target));
	},

	handleRestoreConfirm: function(btn, ev) {
		return fs.exec('/sbin/restore_host_conf', [ '/tmp/backup.tar.gz' ])
			.then(L.bind(function(btn, res) {
				ui.hideModal();
				if (res.code != 0) {
					ui.addNotification(null, [
						E('p', _('The restore command failed with code %d').format(res.code)),
						res.stderr ? E('pre', {}, [ res.stderr ]) : ''
					]);
					L.raise('Error', 'Restore failed');
				}
				ui.addNotification(null, E('p', _('Restore success')), 'info');
			}, this, ev.target))
			.catch(function(e) { ui.addNotification(null, E('p', e.message)) })
			.finally(function() { btn.firstChild.data = _('Upload archive...') });
	},

	handleBlock: function(hostname, ev) {
		var mtdblock = dom.parent(ev.target, '.cbi-section').querySelector('[data-name="mtdselect"] select').value;
		var form = E('form', {
			'method': 'post',
			'action': L.env.cgi_base + '/cgi-download',
			'enctype': 'application/x-www-form-urlencoded'
		}, [
			E('input', { 'type': 'hidden', 'name': 'sessionid', 'value': rpc.getSessionID() }),
			E('input', { 'type': 'hidden', 'name': 'path',      'value': '/dev/mtdblock%d'.format(mtdblock) }),
			E('input', { 'type': 'hidden', 'name': 'filename',  'value': '%s.mtd%d.bin'.format(hostname, mtdblock) })
		]);

		ev.currentTarget.parentNode.appendChild(form);

		form.submit();
		form.parentNode.removeChild(form);
	},

	handleSysupgrade: function(storage_size, ev) {
		return ui.uploadFile('/tmp/firmware.bin', ev.target.firstChild)
			.then(L.bind(function(btn, reply) {
				btn.firstChild.data = _('Checking image…');

				ui.showModal(_('Checking image…'), [
					E('span', { 'class': 'spinning' }, _('Verifying the uploaded image file.'))
				]);

				return callSystemValidateFirmwareImage('/tmp/firmware.bin')
					.then(function(res) { return [ reply, res ]; });
			}, this, ev.target))
			.then(L.bind(function(btn, reply) {
				return fs.exec('/sbin/sysupgrade', [ '--test', '/tmp/firmware.bin' ])
					.then(function(res) { reply.push(res); return reply; });
			}, this, ev.target))
			.then(L.bind(function(btn, res) {
				var keep = E('input', { type: 'checkbox' }),
				    force = E('input', { type: 'checkbox' }),
				    is_valid = res[1].valid,
				    is_forceable = res[1].forceable,
				    allow_backup = res[1].allow_backup,
				    is_too_big = (storage_size > 0 && res[0].size > storage_size),
				    body = [];

				body.push(E('p', _("The flash image was uploaded. Below is the checksum and file size listed, compare them with the original file to ensure data integrity. <br /> Click 'Continue' below to start the flash procedure.")));
				body.push(E('ul', {}, [
					res[0].size ? E('li', {}, '%s: %1024.2mB'.format(_('Size'), res[0].size)) : '',
					res[0].checksum ? E('li', {}, '%s: %s'.format(_('MD5'), res[0].checksum)) : '',
					res[0].sha256sum ? E('li', {}, '%s: %s'.format(_('SHA256'), res[0].sha256sum)) : ''
				]));

				body.push(E('p', {}, E('label', { 'class': 'btn' }, [
					keep, ' ', _('Keep settings and retain the current configuration')
				])));

				if (!is_valid || is_too_big)
					body.push(E('hr'));

				if (is_too_big)
					body.push(E('p', { 'class': 'alert-message' }, [
						_('It appears that you are trying to flash an image that does not fit into the flash memory, please verify the image file!')
					]));

				if (!is_valid)
					body.push(E('p', { 'class': 'alert-message' }, [
						res[2].stderr ? res[2].stderr : '',
						res[2].stderr ? E('br') : '',
						res[2].stderr ? E('br') : '',
						_('The uploaded image file does not contain a supported format. Make sure that you choose the generic image format for your platform.')
					]));

				if (!allow_backup)
					body.push(E('p', { 'class': 'alert-message' }, [
						_('The uploaded firmware does not allow keeping current configuration.')
					]));

				if (allow_backup)
					keep.checked = true;
				else
					keep.disabled = true;


				if ((!is_valid || is_too_big) && is_forceable)
					body.push(E('p', {}, E('label', { 'class': 'btn alert-message danger' }, [
						force, ' ', _('Force upgrade'),
						E('br'), E('br'),
						_('Select \'Force upgrade\' to flash the image even if the image format check fails. Use only if you are sure that the firmware is correct and meant for your device!')
					])));

				var cntbtn = E('button', {
					'class': 'btn cbi-button-action important',
					'click': ui.createHandlerFn(this, 'handleSysupgradeConfirm', btn, keep, force),
					'disabled': (!is_valid || is_too_big) ? true : null
				}, [ _('Continue') ]);

				body.push(E('div', { 'class': 'right' }, [
					E('button', {
						'class': 'btn',
						'click': ui.createHandlerFn(this, function(ev) {
							return fs.remove('/tmp/firmware.bin').finally(ui.hideModal);
						})
					}, [ _('Cancel') ]), ' ', cntbtn
				]));

				force.addEventListener('change', function(ev) {
					cntbtn.disabled = !ev.target.checked;
				});

				ui.showModal(_('Flash image?'), body);
			}, this, ev.target))
			.catch(function(e) { ui.addNotification(null, E('p', e.message)) })
			.finally(L.bind(function(btn) {
				btn.firstChild.data = _('Flash image...');
			}, this, ev.target));
	},

	handleSysupgradeConfirm: function(btn, keep, force, ev) {
		btn.firstChild.data = _('Flashing…');

		ui.showModal(_('Flashing…'), [
			E('p', { 'class': 'spinning' }, _('The system is flashing now.<br /> DO NOT POWER OFF THE DEVICE!<br /> Wait a few minutes before you try to reconnect. It might be necessary to renew the address of your computer to reach the device again, depending on your settings.'))
		]);

		var opts = [];

		if (!keep.checked)
			opts.push('-n');

		if (force.checked)
			opts.push('--force');

		opts.push('/tmp/firmware.bin');

		/* Currently the sysupgrade rpc call will not return, hence no promise handling */
		fs.exec('/sbin/sysupgrade', opts);

		if (keep.checked)
			ui.awaitReconnect(window.location.host);
		else
			ui.awaitReconnect('192.168.1.1', 'openwrt.lan');
	},

	handleBackupList: function(ev) {
		return fs.exec('/sbin/sysupgrade', [ '--list-backup' ]).then(function(res) {
			if (res.code != 0) {
				ui.addNotification(null, [
					E('p', _('The sysupgrade command failed with code %d').format(res.code)),
					res.stderr ? E('pre', {}, [ res.stderr ]) : ''
				]);
				L.raise('Error', 'Sysupgrade failed');
			}

			ui.showModal(_('Backup file list'), [
				E('p', _('Below is the determined list of files to backup. It consists of changed configuration files marked by opkg, essential base files and the user defined backup patterns.')),
				E('ul', {}, (res.stdout || '').trim().split(/\n/).map(function(ln) { return E('li', {}, ln) })),
				E('div', { 'class': 'right' }, [
					E('button', {
						'class': 'btn',
						'click': ui.hideModal
					}, [ _('Dismiss') ])
				])
			], 'cbi-modal');
		});
	},

	handleBackupSave: function(m, ev) {
		return m.save(function() {
			return fs.write('/etc/sysupgrade.conf', mapdata.config.editlist.trim().replace(/\r\n/g, '\n') + '\n');
		}).then(function() {
			ui.addNotification(null, E('p', _('Contents have been saved.')), 'info');
		}).catch(function(e) {
			ui.addNotification(null, E('p', _('Unable to save contents: %s').format(e)));
		});
	},

	render: function(rpc_replies) {
		var has_sysupgrade = (rpc_replies[0].type == 'file'),
		    hostname = rpc_replies[1],
		    procmtd = rpc_replies[2],
		    procpart = rpc_replies[3],
		    procmounts = rpc_replies[4],
		    has_rootfs_data =  (procmtd.match(/"rootfs_data"/) != null) || (procmounts.match("overlayfs:\/overlay \/ ") != null) || (procmounts.match(" \/overlay ") != null),
		    storage_size = findStorageSize(procmtd, procpart),
		    m, s, o, ss;

		m = new form.JSONMap(mapdata, _('Flash operations'));
		m.tabbed = true;
		m.readonly = isReadonlyView;

		s = m.section(form.NamedSection, 'actions', _('Actions'));

		o = s.option(form.SectionValue, 'actions', form.NamedSection, 'actions', 'actions', _('Restore'), _('To restore configuration files, you can upload a previously generated backup archive here. To reset the firmware to its initial state, click "Perform reset" (only possible with squashfs images).'));
		ss = o.subsection;

		if (has_rootfs_data)  {
			o = ss.option(form.Button, 'reset', _('Reset to defaults'));
			o.inputstyle = 'negative important';
			o.inputtitle = _('Perform reset');
			o.onclick = this.handleFirstboot;
		}

		if (procmounts.match(" \/overlay ") != null)  {
			o = ss.option(form.Button, 'restore', _('Restore backup'), _('Custom files (certificates, scripts) may remain on the system. To prevent this, perform a factory-reset first.'));
			o.inputstyle = 'action important';
			o.inputtitle = _('Upload archive...');
			o.onclick = L.bind(this.handleRestore, this);
		}


		var mtdblocks = [];
		procmtd.split(/\n/).forEach(function(ln) {
			var match = ln.match(/^mtd(\d+): .+ "(.+?)"$/);
			if (match)
				mtdblocks.push(match[1], match[2]);
		});

		if (mtdblocks.length) {
			o = s.option(form.SectionValue, 'actions', form.NamedSection, 'actions', 'actions', _('Save mtdblock contents'), _('Click "Save mtdblock" to download specified mtdblock file. (NOTE: THIS FEATURE IS FOR PROFESSIONALS! )'));
			ss = o.subsection;

			o = ss.option(form.ListValue, 'mtdselect', _('Choose mtdblock'));

			for (var i = 0; i < mtdblocks.length; i += 2)
				o.value(mtdblocks[i], mtdblocks[i+1]);

			o = ss.option(form.Button, 'mtddownload', _('Download mtdblock'));
			o.inputstyle = 'action important';
			o.inputtitle = _('Save mtdblock');
			o.onclick = L.bind(this.handleBlock, this, hostname);
		}


		o = s.option(form.SectionValue, 'actions', form.NamedSection, 'actions', 'actions', _('Flash new firmware image'),
			has_sysupgrade
				? _('Upload a sysupgrade-compatible image here to replace the running firmware.')
				: _('Sorry, there is no sysupgrade support present; a new firmware image must be flashed manually. Please refer to the wiki for device specific install instructions.'));

		ss = o.subsection;

		if (has_sysupgrade) {
			o = ss.option(form.Button, 'sysupgrade', _('Image'));
			o.inputstyle = 'action important';
			o.inputtitle = _('Flash image...');
			o.onclick = L.bind(this.handleSysupgrade, this, storage_size);
		}

		return m.render();
	},

	handleSaveApply: null,
	handleSave: null,
	handleReset: null
});
