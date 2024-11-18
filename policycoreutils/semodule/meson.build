executable(
  'semodule',
  c_args: '-DVERSION="' + meson.project_version() + '"',
  sources: ['semodule.c'],
  dependencies: [
    libsepol,
    libsemanage,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_symlink(
  'genhomedircon',
  install_dir: get_option('sbindir'),
  pointing_to: 'semodule',
)

install_man(
  [
    'genhomedircon.8',
    'semodule.8',
  ],
)
