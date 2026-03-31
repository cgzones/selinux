executable(
  'open_init_pty',
  c_args: [
    '-DUSE_NLS',
    '-DLOCALEDIR="' + get_option('localedir') + '"',
    '-DPACKAGE="policycoreutils"',
    '-DUSE_PAM', # TODO: add option
    '-DUSE_AUDIT', # TODO: add option
  ],
  sources: 'open_init_pty.c',
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

executable(
  'run_init',
  c_args: [
    '-DUSE_NLS',
    '-DLOCALEDIR="' + get_option('localedir') + '"',
    '-DPACKAGE="policycoreutils"',
    '-DUSE_PAM', # TODO: add option
    '-DUSE_AUDIT', # TODO: add option
  ],
  sources: 'run_init.c',
  dependencies: [
    libselinux,
    libaudit,
    libpam,
    libpammisc,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_data(
  'run_init.pamd',
  install_dir: get_option('sysconfdir') / 'pam.d',
  rename: 'run_init',
)

install_man(
  [
    'open_init_pty.8',
    'run_init.8',
  ],
)
