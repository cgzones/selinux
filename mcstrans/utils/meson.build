executable(
  'transcon',
  sources: ['transcon.c'],
  include_directories: ['../src'],
  dependencies: [libsepol, libselinux, pcre2],
  link_args: [exe_link_args],
  link_with: [mcstrans_static],
  install: false,
  install_dir: get_option('sbindir'),
)

executable(
  'untranscon',
  sources: ['untranscon.c'],
  include_directories: ['../src'],
  dependencies: [libsepol, libselinux, pcre2],
  link_args: [exe_link_args],
  link_with: [mcstrans_static],
  install: false,
  install_dir: get_option('sbindir'),
)

# TODO: file does not exist
#mlstrans_test_runner_py = find_program('mlstrans-test-runner.py')
#
#test(
#  'mlstrans-test-runner.py',
#  mlstrans_test_runner_py,
#  args: ['../test/*.test'],
#  #depends: [secilc_exec, test_files],
#  workdir: meson.current_build_dir(),
#  #env: ['CHECKPOLICY=@0@'.format(checkpolicy.full_path())],
#)
