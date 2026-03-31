project(
  'libselinux',
  'c',
  version: '3.10',
  license: 'Public-Domain',
  default_options: [
    'prefix=/usr',
    'optimization=2',
    'werror=true',
    'warning_level=2',
  ],
)

# TODO: options: DISABLE_SETRANS, DISABLE_RPM, ANDROID_HOST, LABEL_BACKEND_ANDROID, DISABLE_BOOL, DISABLE_X11

cc = meson.get_compiler('c')

add_project_arguments('-D_GNU_SOURCE', language: 'c')

# TODO: flags from src/Makefile and utils/Makefile
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

check_functions = [
  ['reallocarray', '#include <stdlib.h>'],
  ['strlcpy', '#include <string.h>'],
]
foreach ident : check_functions
  if cc.has_function(ident[0], prefix: ident[1], args: '-D_GNU_SOURCE')
    add_project_arguments('-DHAVE_' + ident[0].to_upper(), language: 'c')
  endif
endforeach

python_wrapper = find_program('tests/test_python_wrap.py', required: true)
test('python-wrappers', python_wrapper)

subdir('include')
subdir('man')
subdir('src')
subdir('utils')
