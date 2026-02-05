executable(
  'semodule_expand',
  sources: ['semodule_expand.c'],
  dependencies: libsepol,
  install: true,
  install_dir: get_option('bindir'),
  link_args: [exe_link_args],
)

install_man('semodule_expand.8')
