# TODO: install as setuuid binary
executable(
  'newrole',
  c_args: [
    '-DUSE_NLS',
    '-DVERSION="' + meson.project_version() + '"',
    '-DLOCALEDIR="' + get_option('localedir') + '"',
    '-DPACKAGE="policycoreutils"',
    '-DUSE_PAM', # TODO: add option
    '-DUSE_AUDIT', # TODO: add option
    '-DAUDIT_LOG_PRIV', # TODO: add option
    '-DNAMESPACE_PRIV', # TODO: add option
  ],
  sources: [
    'hashtab.c',
    'hashtab.h',
    'newrole.c',
  ],
  dependencies: [
    libselinux,
    libaudit,
    libcapng,
    libpam,
    libpammisc,
  ],
  install: true,
  install_dir: get_option('bindir'),
  link_args: [exe_link_args],
)

# TODO: install newrole.pamd depending on option
install_data(
  'newrole-lspp.pamd',
  install_dir: get_option('sysconfdir') / 'pam.d',
  rename: 'newrole',
)

install_man('newrole.1')
