project(
  'restorecond',
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

cc = meson.get_compiler('c')

add_project_arguments('-D_GNU_SOURCE', language: 'c')

try_cc_flags = [
  '-Wbad-function-cast',
  '-Wdeprecated',
  '-Wfloat-equal',
  '-Wformat=2',
  '-Winit-self',
  '-Wmain',
  '-Wmissing-declarations',
  '-Wmissing-format-attribute',
  '-Wmissing-noreturn',
  '-Wmissing-prototypes',
  '-Wnull-dereference',
  '-Wpointer-arith',
  '-Wreturn-type',
  '-Wshadow',
  '-Wstrict-prototypes',
  '-Wundef',
  '-Wuninitialized',
  '-Wunused',
  '-Wwrite-strings',
  '-fno-semantic-interposition',
  '-fno-common',
]

add_project_arguments(cc.get_supported_arguments(try_cc_flags), language: 'c')

add_project_link_arguments(
  # --as-needed and --no-undefined are enabled by default
  cc.get_supported_link_arguments(
    [
      '-Wl,--fatal-warnings',
      '-Wl,-O1',
    ],
  ),
  language: 'c',
)

exe_link_args = cc.get_supported_link_arguments(
  [
    '-Wl,-z,relro',
    '-Wl,-z,now',
  ],
)

libselinux = dependency(
  'libselinux',
  fallback: ['libselinux', 'libselinux_shared_dep'],
  required: true,
)

gio_2 = dependency('gio-2.0', required: true)

executable(
  'restorecond',
  c_args: '-DHAVE_DBUS',
  sources: [
    'restore.c',
    'restore.h',
    'restorecond.c',
    'restorecond.h',
    'stringslist.c',
    'stringslist.h',
    'user.c',
    'utmpwatcher.c',
    'utmpwatcher.h',
    'watch.c',
  ],
  dependencies: [
    libselinux,
    gio_2,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_man('restorecond.8')

install_data(
  'restorecond.init',
  install_dir: get_option('sysconfdir') / 'init.d',
  install_mode: 'rwxr-xr-x',
  rename: 'restorecond',
)

install_data(
  'restorecond.conf',
  install_dir: get_option('sysconfdir') / 'selinux',
  install_mode: 'rw-r--r--',
)

install_data(
  'restorecond_user.conf',
  install_dir: get_option('sysconfdir') / 'selinux',
  install_mode: 'rw-r--r--',
)

install_data(
  'restorecond.desktop',
  install_dir: get_option('sysconfdir') / 'xdg' / 'autostart',
  install_mode: 'rw-r--r--',
)

install_data(
  'org.selinux.Restorecond.service',
  install_dir: get_option('datadir') / 'dbus-1' / 'services',
  install_mode: 'rw-r--r--',
)

systemd = dependency('systemd')

install_data(
  'restorecond.service',
  install_dir: systemd.get_variable('systemdsystemunitdir'),
  install_mode: 'rw-r--r--',
)

install_data(
  'restorecond_user.service',
  install_dir: systemd.get_variable('systemduserunitdir'),
  install_mode: 'rw-r--r--',
)
