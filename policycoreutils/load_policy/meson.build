executable(
  'load_policy',
  c_args: [
    '-DUSE_NLS',
    '-DLOCALEDIR="' + get_option('localedir') + '"',
    '-DPACKAGE="policycoreutils"',
  ],
  sources: ['load_policy.c'],
  dependencies: [
    libsepol,
    libselinux,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_man('load_policy.8')
