project(
  'secilc',
  'c',
  version: '3.10',
  license: 'BSD-2-Clause-FreeBSD',
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

libsepol = dependency('libsepol', fallback: ['libsepol', 'libsepol_shared_dep'], required: true)

secilc = executable(
  'secilc',
  sources: ['secilc.c'],
  dependencies: [libsepol],
  install: true,
  link_args: [exe_link_args],
)
meson.override_find_program('secilc', secilc)

secil2conf = executable(
  'secil2conf',
  sources: ['secil2conf.c'],
  dependencies: [libsepol],
  install: true,
  link_args: [exe_link_args],
)
meson.override_find_program('secil2conf', secil2conf)

secil2tree = executable(
  'secil2tree',
  sources: ['secil2tree.c'],
  dependencies: [libsepol],
  install: true,
  link_args: [exe_link_args],
)
meson.override_find_program('secil2tree', secil2tree)

xmlto = find_program('xmlto', required: true)

custom_target(
  'secilc.8',
  input: 'secilc.8.xml',
  output: 'secilc.8',
  command: [xmlto, 'man', '@INPUT@', '-o', meson.current_build_dir()],
  install: true,
  install_dir: get_option('mandir') / 'man8',
)

custom_target(
  'secil2conf.8',
  input: 'secil2conf.8.xml',
  output: 'secil2conf.8',
  command: [xmlto, 'man', '@INPUT@', '-o', meson.current_build_dir()],
  install: true,
  install_dir: get_option('mandir') / 'man8',
)

custom_target(
  'secil2tree.8',
  input: 'secil2tree.8.xml',
  output: 'secil2tree.8',
  command: [xmlto, 'man', '@INPUT@', '-o', meson.current_build_dir()],
  install: true,
  install_dir: get_option('mandir') / 'man8',
)

policy_cil = configure_file(
  input: 'test/policy.cil',
  output: 'policy.cil',
  copy: true,
)

opt_input_cil = configure_file(
  input: 'test/opt-input.cil',
  output: 'opt-input.cil',
  copy: true,
)

opt_expected_cil = configure_file(
  input: 'test/opt-expected.cil',
  output: 'opt-expected.cil',
  copy: true,
)

noop = find_program('true', required: true)
test_files = custom_target(
  depend_files: [
    policy_cil,
    opt_input_cil,
    opt_expected_cil,
  ],
  command: [noop],
  output: 'fake',
)

checkpolicy = find_program('checkpolicy', required: true)
run_test_sh = find_program('run_test.sh')

test(
  'secilc',
  run_test_sh,
  depends: [secilc, test_files],
  workdir: meson.current_build_dir(),
  env: ['CHECKPOLICY=@0@'.format(checkpolicy.full_path())],
)

# TODO
#subdir('docs')
