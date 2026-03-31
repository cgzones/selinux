executable(
  'sestatus',
  sources: ['sestatus.c'],
  dependencies: libselinux,
  install: true,
  link_args: [exe_link_args],
)

install_symlink(
  'sestatus',
  install_dir: get_option('sbindir'),
  pointing_to: '../bin/sestatus',
)

install_data(
  'sestatus.conf',
  install_dir: get_option('sysconfdir'),
)

install_man(
  [
    'sestatus.8',
    'sestatus.conf.5',
  ],
)
