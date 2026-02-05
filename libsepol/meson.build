project(
  'libsepol',
  'c',
  version: '3.10',
  license: 'LGPL-2.1+',
  default_options: [
    'prefix=/usr',
    'optimization=2',
    'werror=true',
    'warning_level=2',
  ],
)

enable_checkpolicy = get_option('checkpolicy')
enable_cil = get_option('cil')

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

check_functions = [
  ['reallocarray', '#include <stdlib.h>'],
]
foreach ident : check_functions
  if cc.has_function(ident[0], prefix: ident[1], args: '-D_GNU_SOURCE')
    add_project_arguments('-DHAVE_' + ident[0].to_upper(), language: 'c')
  endif
endforeach

if enable_checkpolicy
  prog_yacc = find_program('bison', required: false, disabler: true)
  if prog_yacc.found()
    yacc_cmd = [prog_yacc, '-o', '@OUTPUT0@', '--defines=@OUTPUT1@', '@INPUT@']
  else
    prog_yacc = find_program(
      'byacc',
      required: true,
    )
    yacc_cmd = [prog_yacc, '-o', '@OUTPUT0@', '-H', '@OUTPUT1@', '@INPUT@']
  endif

  #bison = find_program('bison')
  #bison_gen = generator(
  #  bison,
  #  output: ['@BASENAME@.tab.c', '@BASENAME@.tab.h'],
  #  arguments: [
  #    #TODO: '-Wall',
  #    '--output=@OUTPUT0@',
  #    '--defines=@OUTPUT1@',
  #    '@INPUT@',
  #  ]
  #)
endif # enable_checkpolicy

if enable_checkpolicy or enable_cil
  prog_flex = find_program(
    'flex',
    required: true,
  )

  #flex = find_program(
  #  'flex',
  #  required: true,
  #)
  #
  #flex_gen = generator(
  #  flex,
  #  output: ['@BASENAME@.c', '@BASENAME@.h'],
  #  arguments: [
  #    '--outfile=@OUTPUT0@',
  #    '@INPUT@',
  #  ]
  #)
endif # enable_checkpolicy or enable_cil

subdir('include')
subdir('man')
subdir('src')
subdir('utils')
if enable_checkpolicy
  subdir('checkpolicy')
  subdir('tests')
endif # enable_checkpolicy
