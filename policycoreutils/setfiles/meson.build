executable(
  'setfiles',
  c_args: '-DUSE_AUDIT', # TODO: add option
  sources: [
    'restore.c',
    'restore.h',
    'setfiles.c',
  ],
  dependencies: [
    libsepol,
    libselinux,
    libaudit,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

executable(
  'restorecon_xattr',
  c_args: '-DUSE_AUDIT', # TODO: add option
  sources: [
    'restore.c',
    'restorecon_xattr.c',
    'restore.h',
  ],
  dependencies: libselinux,
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_symlink(
  'restorecon',
  install_dir: get_option('sbindir'),
  pointing_to: 'setfiles',
)

install_man(
  [
    'restorecon.8',
    'restorecon_xattr.8',
    'setfiles.8',
  ],
)
