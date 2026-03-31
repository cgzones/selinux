project(
  'selinux-gui',
  'c',
  version: '3.10',
  license: 'BSD-2-Clause-FreeBSD',
  default_options: [
    'prefix=/usr',
    'optimization=2',
    'werror=true',
    'warning_level=2',
  ],
)

install_man(
  [
    'selinux-polgengui.8',
    'system-config-selinux.8',
  ],
)

install_data(
  'system-config-selinux.py',
  install_dir: get_option('datadir') / 'system-config-selinux',
  install_mode: 'rwxr-xr-x',
)

install_data(
  'system-config-selinux',
  install_dir: get_option('bindir'),
  install_mode: 'rwxr-xr-x',
)

install_data(
  'polgengui.py',
  install_dir: get_option('bindir'),
  install_mode: 'rwxr-xr-x',
  rename: 'selinux-polgengui',
)

install_data(
  [
    'booleansPage.py',
    'domainsPage.py',
    'fcontextPage.py',
    'loginsPage.py',
    'modulesPage.py',
    'polgen.ui',
    'portsPage.py',
    'semanagePage.py',
    'statusPage.py',
    'system-config-selinux.png',
    'system-config-selinux.ui',
    'usersPage.py',
  ],
  install_dir: get_option('datadir') / 'system-config-selinux',
  install_mode: 'rw-r--r--',
)

install_data(
  'system-config-selinux.png',
  install_dir: get_option('datadir') / 'pixmaps',
  install_mode: 'rw-r--r--',
)

install_data(
  'system-config-selinux.png',
  install_dir: get_option('datadir') / 'icons' / 'hicolor' / '24x24' / 'apps',
  install_mode: 'rw-r--r--',
)

install_data(
  'selinux-polgengui.desktop',
  install_dir: get_option('datadir') / 'applications',
  install_mode: 'rw-r--r--',
)

install_data(
  'sepolicy.desktop',
  install_dir: get_option('datadir') / 'applications',
  install_mode: 'rw-r--r--',
)

install_data(
  'system-config-selinux.desktop',
  install_dir: get_option('datadir') / 'applications',
  install_mode: 'rw-r--r--',
)

install_data(
  'sepolicy_256.png',
  install_dir: get_option('datadir') / 'pixmaps',
  install_mode: 'rw-r--r--',
  rename: 'sepolicy.png',
)

install_data(
  'sepolicy_16.png',
  install_dir: get_option('datadir') / 'icons' / 'hicolor' / '16x16' / 'apps',
  install_mode: 'rw-r--r--',
  rename: 'sepolicy.png',
)

install_data(
  'sepolicy_22.png',
  install_dir: get_option('datadir') / 'icons' / 'hicolor' / '22x22' / 'apps',
  install_mode: 'rw-r--r--',
  rename: 'sepolicy.png',
)

install_data(
  'sepolicy_32.png',
  install_dir: get_option('datadir') / 'icons' / 'hicolor' / '32x32' / 'apps',
  install_mode: 'rw-r--r--',
  rename: 'sepolicy.png',
)

install_data(
  'sepolicy_48.png',
  install_dir: get_option('datadir') / 'icons' / 'hicolor' / '48x48' / 'apps',
  install_mode: 'rw-r--r--',
  rename: 'sepolicy.png',
)

install_data(
  'sepolicy_256.png',
  install_dir: get_option('datadir') / 'icons' / 'hicolor' / '256x256' / 'apps',
  install_mode: 'rw-r--r--',
  rename: 'sepolicy.png',
)

install_data(
  'org.selinux.config.policy',
  install_dir: get_option('datadir') / 'polkit-1' / 'actions',
  install_mode: 'rw-r--r--',
)

subdir('po')
