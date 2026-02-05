executable(
  'unsetfiles',
  sources: 'unsetfiles.c',
  dependencies: libselinux,
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_man('unsetfiles.1')
