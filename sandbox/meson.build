project(
  'selinux-sandbox',
  'c',
  version: '3.10',
  license: 'GPL-2',
  default_options: [
    'prefix=/usr',
    'optimization=2',
    'werror=true',
    'warning_level=2',
  ],
)

cc = meson.get_compiler('c')

add_project_arguments('-D_GNU_SOURCE', language: 'c')

try_cc_flags = [
  '-Wbad-function-cast',
  '-Wdeprecated',
  '-Wfloat-equal',
  '-Wformat=2',
  '-Winit-self',
  '-Wmain',
  '-Wmissing-declarations',
  '-Wmissing-format-attribute',
  '-Wmissing-noreturn',
  '-Wmissing-prototypes',
  '-Wnull-dereference',
  '-Wpointer-arith',
  '-Wreturn-type',
  '-Wshadow',
  '-Wstrict-prototypes',
  '-Wundef',
  '-Wuninitialized',
  '-Wunused',
  '-Wwrite-strings',
  '-fno-semantic-interposition',
  '-fno-common',
]

add_project_arguments(cc.get_supported_arguments(try_cc_flags), language: 'c')

add_project_link_arguments(
  # --as-needed and --no-undefined are enabled by default
  cc.get_supported_link_arguments(
    [
      '-Wl,--fatal-warnings',
      '-Wl,-O1',
    ],
  ),
  language: 'c',
)

exe_link_args = cc.get_supported_link_arguments(
  [
    '-Wl,-z,relro',
    '-Wl,-z,now',
  ],
)

libselinux = dependency(
  'libselinux',
  fallback: ['libselinux', 'libselinux_shared_dep'],
  required: true,
)

libcapng = dependency('libcap-ng', required: true)

executable(
  'seunshare',
  c_args: '-DPACKAGE="policycoreutils"',
  sources: ['seunshare.c'],
  dependencies: [
    libselinux,
    libcapng,
  ],
  install: true,
  install_dir: get_option('sbindir'),
  link_args: [exe_link_args],
)

install_man(['sandbox.5', 'sandbox.8', 'seunshare.8'])

install_data('sandbox', install_dir: get_option('bindir'), install_mode: 'rwxr-xr-x')

install_data(
  'sandboxX.sh',
  install_dir: get_option('datadir') / 'sandbox',
  install_mode: 'rwxr-xr-x',
)

install_data(
  'start',
  install_dir: get_option('datadir') / 'sandbox',
  install_mode: 'rwxr-xr-x',
)

install_data(
  'sandbox.conf',
  install_dir: get_option('sysconfdir') / 'sysconfig',
  install_mode: 'rw-r--r--',
  rename: 'sandbox',
)

subdir('po')
