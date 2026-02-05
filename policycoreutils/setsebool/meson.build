executable(
  'setsebool',
  sources: 'setsebool.c',
  dependencies: [
    libselinux,
    libsemanage,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_data(
  'setsebool-bash-completion.sh',
  install_dir: get_option('datadir') / 'bash-completion' / 'completions',
  rename: 'setsebool',
)

install_man('setsebool.8')
