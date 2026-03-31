fs = import('fs')

executable(
  'sepolgen-ifgen-attr-helper',
  sources: 'sepolgen-ifgen-attr-helper.c',
  dependencies: [libsepol, libselinux],
  link_args: [exe_link_args],
  install: true,
  install_dir: get_option('bindir'),
)

install_data(
  'audit2allow',
  install_dir: get_option('bindir'),
  install_mode: 'rwxr-xr-x',
)

install_symlink('audit2why', install_dir: get_option('bindir'), pointing_to: 'audit2allow')

install_data(
  'sepolgen-ifgen',
  install_dir: get_option('bindir'),
  install_mode: 'rwxr-xr-x',
)

install_man(['audit2allow.1', 'audit2why.1'])

secilc = find_program('secilc')

test_dummy_policy = custom_target(
  'test_dummy_policy',
  input: 'test_dummy_policy.cil',
  output: 'test_dummy_policy',
  command: [secilc, '-f', '/dev/null', '-o', '@OUTPUT@', '@INPUT@'],
)

python = find_program('python3')

test_audit2allow_py = fs.copyfile('test_audit2allow.py')
test_audit2allow = fs.copyfile('audit2allow')
test_audit2why = fs.copyfile('audit2why')
test_sepolgen_ifgen = fs.copyfile('sepolgen-ifgen')
test_log = fs.copyfile('test.log')

test(
  'audit2allow',
  python,
  args: ['test_audit2allow.py', '-v'],
  depends: [
    test_dummy_policy,
    test_audit2allow_py,
    test_audit2allow,
    test_audit2why,
    test_sepolgen_ifgen,
    test_log,
  ],
  workdir: meson.current_build_dir(),
)
