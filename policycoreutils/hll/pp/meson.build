executable(
  'pp',
  sources: ['pp.c'],
  dependencies: libsepol,
  install: true,
  install_dir: get_option('libexecdir') / 'selinux' / 'hll',
  link_args: [exe_link_args],
)
