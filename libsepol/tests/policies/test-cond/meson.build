test_cond_refpolicy_base_std = custom_target(
  'test-cond_refpolicy-base-std',
  input: 'refpolicy-base.conf',
  output: 'refpolicy-base.conf.std',
  command: m4_cmd_std,
  capture: true,
)

test_cond_refpolicy_base_mls = custom_target(
  'test-cond_refpolicy-base-mls',
  input: 'refpolicy-base.conf',
  output: 'refpolicy-base.conf.mls',
  command: m4_cmd_mls,
  capture: true,
)
