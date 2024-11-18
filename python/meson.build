project(
  'selinux-python',
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

libsepol = dependency(
  'libsepol',
  fallback: ['libsepol', 'libsepol_static_dep'],
  required: true,
  static: true,
)
libselinux = dependency(
  'libselinux',
  fallback: ['libselinux', 'libselinux_shared_dep'],
  required: true,
)

#pcre2 = dependency('libpcre2-8', required: true)
#add_project_arguments('-DPCRE2_CODE_UNIT_WIDTH=8', language: 'c')

#libcap = dependency('libcap', required: true)

subdir('audit2allow')
subdir('chcat')
subdir('po')
subdir('semanage')
subdir('sepolicy')
subdir('sepolgen')
