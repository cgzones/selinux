executable(
  'semodule_package',
  sources: ['semodule_package.c'],
  dependencies: libsepol,
  install: true,
  install_dir: get_option('bindir'),
  link_args: [exe_link_args],
)

executable(
  'semodule_unpackage',
  sources: ['semodule_unpackage.c'],
  dependencies: libsepol,
  install: true,
  install_dir: get_option('bindir'),
  link_args: [exe_link_args],
)

install_man(['semodule_package.8', 'semodule_unpackage.8'])
