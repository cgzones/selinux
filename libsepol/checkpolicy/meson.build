common_sources = files(
  'module_compiler.c',
  'module_compiler.h',
  'parse_util.c',
  'policy_define.c',
  'policy_define.h',
  #bison_gen.process('policy_parse.y'),
  #flex_gen.process('policy_scan.l'),
  'queue.c',
)

policy_parse_y = custom_target(
  'policy_parse',
  input: 'policy_parse.y',
  output: ['y.tab.c', 'y.tab.h'],
  command: yacc_cmd,

)

policy_scan_l = custom_target(
  'policy_scan',
  input: 'policy_scan.l',
  output: 'policy_scan.c',
  depends: policy_parse_y,
  command: [prog_flex, '-o', '@OUTPUT@', '@INPUT@'],
)

checkpolicy_common = static_library(
  'checkpolicy_common',
  include_directories: ['../include'], #TODO: check if recompiles after header change
  sources: [common_sources, policy_parse_y, policy_scan_l],
  install: false,
)

checkpolicy = executable(
  'checkpolicy',
  sources: ['checkpolicy.c'],
  include_directories: ['../include'], #TODO: check if recompiles after header change
  install: true,
  link_args: [exe_link_args],
  link_with: [checkpolicy_common, sepol_static],
)
meson.override_find_program('checkpolicy', checkpolicy)

checkmodule = executable(
  'checkmodule',
  sources: ['checkmodule.c'],
  include_directories: ['../include'], #TODO: check if recompiles after header change
  install: true,
  link_args: [exe_link_args],
  link_with: [checkpolicy_common, sepol_static],
)
meson.override_find_program('checkmodule', checkmodule)

install_man(
  [
    'checkmodule.8',
    'checkpolicy.8',
  ],
)

test_roundtrip = find_program('tests/test_roundtrip.sh')

test(
  'checkpolicy_test_roundtrip',
  test_roundtrip,
  depends: [checkpolicy],
  env: ['CHECKPOLICY=@0@'.format(checkpolicy.full_path())],
  workdir: meson.current_build_dir(),
)

subdir('test')
