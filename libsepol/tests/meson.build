test_sources = [
  'debug.c',
  'debug.h',
  'helpers.c',
  'helpers.h',
  'libsepol-tests.c',
  'test-common.c',
  'test-common.h',
  'test-cond.c',
  'test-cond.h',
  'test-deps.c',
  'test-deps.h',
  'test-downgrade.c',
  'test-downgrade.h',
  'test-ebitmap.c',
  'test-ebitmap.h',
  'test-expander-attr-map.c',
  'test-expander-attr-map.h',
  'test-expander-roles.c',
  'test-expander-roles.h',
  'test-expander-users.c',
  'test-expander-users.h',
  'test-expander.c',
  'test-expander.h',
  'test-linker-cond-map.c',
  'test-linker-cond-map.h',
  'test-linker-roles.c',
  'test-linker-roles.h',
  'test-linker-types.c',
  'test-linker-types.h',
  'test-linker.c',
  'test-linker.h',
  'test-neverallow.c',
  'test-neverallow.h',
]

# TODO: split into single executables to run in parallel

cunit = dependency('cunit', required: true)

test_bin = executable(
  'test_bin',
  sources: [test_sources],
  dependencies: [cunit],
  include_directories: ['../include', '../checkpolicy'],
  install: false,
  link_args: [exe_link_args],
  link_with: [sepol_static, checkpolicy_common],
)

support_macros = files([
  'policies/support/misc_macros.spt',
])

prog_m4 = find_program('m4', required: true)
m4_cmd_std = [prog_m4, '-E', '-E', support_macros, '@INPUT@']
m4_cmd_mls = [prog_m4, '-E', '-E', support_macros, '-D', 'enable_mls', '@INPUT@']

subdir('policies')

#prog_mkdir = find_program('mkdir', required: true)
#downgrade_dir_path = meson.current_build_dir() / 'policies/test-downgrade'
#mkdir_create_downgrade_cmd = [prog_mkdir, '-p', downgrade_dir_path]
#
#downgrade_dir = custom_target(
#  'downgrade_dir',
#  #output: '.stamp_downgrade_dir',
#  output: 'fake',
#  command: mkdir_create_downgrade_cmd,
#)
#
#policy_hi_path = downgrade_dir_path / 'policy.hi'
#checkpolicy_path = meson.current_build_dir() / '../checkpolicy/checkpolicy'
## checkpolicy.full_path()
#
#downgrade_hi_policy = custom_target(
#  'policy.hi',
#  depends: [downgrade_dir, checkpolicy],
#  input: 'policies/test-cond/refpolicy-base.conf',
#  #output: '.stamp.policy.hi',
#  output: 'fake',
#  command: [checkpolicy_path, '-M', '@INPUT@', '-o', policy_hi_path],
#)

configure_file(
  copy: true,
  input: 'policies/test-cond/refpolicy-base.conf',
  output: 'refpolicy-base.conf',
)

prog_prepare_testsuite = find_program('prepare_testsuite.sh', required: true)
prepare_testsuite = custom_target(
  'prepare_testsuite',
  output: 'fake',
  command: [prog_prepare_testsuite],
  depends: [checkpolicy],
  env: [
    'CHECKPOLICY=@0@'.format(checkpolicy.full_path()),
    'WORKDIR=@0@'.format(meson.current_build_dir())
  ],
)

test(
  'sepol_testsuite',
  test_bin,
  depends: [
    prepare_testsuite,
    test_cond_refpolicy_base_std,
    test_cond_refpolicy_base_mls,
    test_deps_base_metrq_std,
    test_deps_base_metrq_mls,
    test_deps_base_notmetrq_std,
    test_deps_base_notmetrq_mls,
    test_deps_modreq_attr_global_std,
    test_deps_modreq_attr_global_mls,
    test_deps_modreq_attr_opt_std,
    test_deps_modreq_attr_opt_mls,
    test_deps_modreq_bool_global_std,
    test_deps_modreq_bool_global_mls,
    test_deps_modreq_bool_opt_std,
    test_deps_modreq_bool_opt_mls,
    test_deps_modreq_obj_global_std,
    test_deps_modreq_obj_global_mls,
    test_deps_modreq_obj_opt_std,
    test_deps_modreq_obj_opt_mls,
    test_deps_modreq_perm_global_std,
    test_deps_modreq_perm_global_mls,
    test_deps_modreq_perm_opt_std,
    test_deps_modreq_perm_opt_mls,
    test_deps_modreq_role_global_std,
    test_deps_modreq_role_global_mls,
    test_deps_modreq_role_opt_std,
    test_deps_modreq_role_opt_mls,
    test_deps_modreq_type_global_std,
    test_deps_modreq_type_global_mls,
    test_deps_modreq_type_opt_std,
    test_deps_modreq_type_opt_mls,
    test_deps_module_std,
    test_deps_module_mls,
    test_deps_small_base_std,
    test_deps_small_base_mls,
    test_expander_alias_base_std,
    test_expander_alias_base_mls,
    test_expander_alias_module_std,
    test_expander_alias_module_mls,
    test_expander_base_base_only_std,
    test_expander_base_base_only_mls,
    test_expander_module_std,
    test_expander_module_mls,
    test_expander_role_base_std,
    test_expander_role_base_mls,
    test_expander_role_module_std,
    test_expander_role_module_mls,
    test_expander_small_base_std,
    test_expander_small_base_mls,
    test_expander_user_base_std,
    test_expander_user_base_mls,
    test_expander_user_module_std,
    test_expander_user_module_mls,
    test_hooks_cmp_policy_std,
    test_hooks_cmp_policy_mls,
    test_hooks_module_add_role_allow_trans_std,
    test_hooks_module_add_role_allow_trans_mls,
    test_hooks_module_add_symbols_std,
    test_hooks_module_add_symbols_mls,
    test_hooks_small_base_std,
    test_hooks_small_base_mls,
    test_linker_module1_std,
    test_linker_module1_mls,
    test_linker_module2_std,
    test_linker_module2_mls,
    test_linker_small_base_std,
    test_linker_small_base_mls,
    test_neverallow_policy_cond_std,
    test_neverallow_policy_cond_mls,
    test_neverallow_policy_std,
    test_neverallow_policy_mls,
    test_neverallow_policy_minus_self_std,
    test_neverallow_policy_minus_self_mls,
    test_neverallow_policy_not_self_std,
    test_neverallow_policy_not_self_mls,
  ],
  workdir: meson.current_build_dir(),

)
