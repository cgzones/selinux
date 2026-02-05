mcstrans_sources = [
  'mcstrans.c',
  'mcstrans.h',
  'mcscolor.c',
  'mcscolor.h',
  'mls_level.c',
  'mls_level.h',
]

mcstrans_static = static_library(
  'mcstrans',
  dependencies: [libsepol, libselinux],
  sources: mcstrans_sources,
  install: false,
)

executable(
  'mcstransd',
  sources: 'mcstransd.c',
  dependencies: [libsepol, libselinux, pcre2, libcap],
  link_args: [exe_link_args],
  link_with: [mcstrans_static],
  install: true,
  install_dir: get_option('sbindir'),
)

install_data(
  'mcstrans.init',
  install_dir: get_option('sysconfdir') / 'init.d',
  install_mode: 'rwxr-xr-x',
  rename: 'mcstrans',
)

systemd = dependency('systemd')

install_data(
  'mcstrans.service',
  install_dir: systemd.get_variable('systemdsystemunitdir'),
  install_mode: 'rw-r--r--',
)
