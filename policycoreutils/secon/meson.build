executable(
  'secon',
  c_args: '-DVERSION="' + meson.project_version() + '"',
  sources: ['secon.c'],
  dependencies: libselinux,
  install: true,
  link_args: [exe_link_args],
)

install_man('secon.1')
