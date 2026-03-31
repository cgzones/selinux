project(
  'selinux-dbus',
  'c',
  version: '3.10',
  license: 'GPL-2',
  default_options: [
    'prefix=/usr',
    'optimization=2',
    'werror=true',
    'warning_level=2',
  ],
)

install_data(
  'org.selinux.conf',
  install_dir: get_option('sysconfdir') / 'dbus-1' / 'system.d',
  install_mode: 'rw-r--r--',
)

install_data(
  'org.selinux.service',
  install_dir: get_option('datadir') / 'dbus-1' / 'system-services',
  install_mode: 'rw-r--r--',
)

install_data(
  'org.selinux.policy',
  install_dir: get_option('datadir') / 'polkit-1' / 'actions',
  install_mode: 'rw-r--r--',
)

install_data(
  'selinux_server.py',
  install_dir: get_option('datadir') / 'system-config-selinux',
  install_mode: 'rwxr-xr-x',
)
