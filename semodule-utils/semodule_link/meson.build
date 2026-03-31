executable(
  'semodule_link',
  sources: ['semodule_link.c'],
  dependencies: libsepol,
  install: true,
  install_dir: get_option('bindir'),
  link_args: [exe_link_args],
)

install_man('semodule_link.8')
