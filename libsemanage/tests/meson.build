secilc = find_program('secilc', required: true)

test_bool_cil = custom_target(
  'test_bool.cil',
  input: 'test_bool.cil',
  output: 'test_bool.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_fcontext_cil = custom_target(
  'test_fcontext.cil',
  input: 'test_fcontext.cil',
  output: 'test_fcontext.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_handle_cil = custom_target(
  'test_handle.cil',
  input: 'test_handle.cil',
  output: 'test_handle.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_ibendport_cil = custom_target(
  'test_ibendport.cil',
  input: 'test_ibendport.cil',
  output: 'test_ibendport.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_iface_cil = custom_target(
  'test_iface.cil',
  input: 'test_iface.cil',
  output: 'test_iface.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_node_cil = custom_target(
  'test_node.cil',
  input: 'test_node.cil',
  output: 'test_node.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_port_cil = custom_target(
  'test_port.cil',
  input: 'test_port.cil',
  output: 'test_port.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

test_user_cil = custom_target(
  'test_user.cil',
  input: 'test_user.cil',
  output: 'test_user.policy',
  install: false,
  command: [secilc, '@INPUT@', '-o', '@OUTPUT@', '-f', '/dev/null'],
)

cil_files = [
  test_bool_cil,
  test_fcontext_cil,
  test_handle_cil,
  test_ibendport_cil,
  test_iface_cil,
  test_node_cil,
  test_port_cil,
  test_user_cil,
]

test_sources = [
  'libsemanage-tests.c',
  'test_bool.c',
  'test_fcontext.c',
  'test_handle.c',
  'test_ibendport.c',
  'test_iface.c',
  'test_node.c',
  'test_other.c',
  'test_port.c',
  'test_semanage_store.c',
  'test_user.c',
  'test_utilities.c',
  'utilities.c',
]

nc_sort_malformed = configure_file(
  input: 'nc_sort_malformed',
  output: 'nc_sort_malformed',
  copy: true,
)

nc_sort_sorted = configure_file(
  input: 'nc_sort_sorted',
  output: 'nc_sort_sorted',
  copy: true,
)

nc_sort_unsorted = configure_file(
  input: 'nc_sort_unsorted',
  output: 'nc_sort_unsorted',
  copy: true,
)

noop = find_program('true', required: true)
nc_files = custom_target(
  depend_files: [
    nc_sort_malformed,
    nc_sort_sorted,
    nc_sort_unsorted,
  ],
  command: [noop],
  output: 'fake',
)

cunit = dependency('cunit', required: true)
libaudit = dependency('audit', required: true)
libbz2 = dependency('bzip2', required: true)

libsepol = dependency(
  'libsepol',
  fallback: ['libsepol', 'libsepol_static_dep'],
  required: true,
  static: true,
)
libselinux = dependency(
  'libselinux',
  fallback: ['libselinux', 'libselinux_static_dep'],
  required: true,
  static: true,
)

wno_unused_parameter = cc.get_supported_arguments('-Wno-unused-parameter')

# TODO: split into multiple binaries to run in parallel
libsemanage_tests = executable(
  'libsemanage-tests',
  sources: [test_sources],
  dependencies: [
    cunit,
    libaudit,
    libbz2,
    libsepol,
    libselinux,
  ],
  include_directories: [
    '../src',
    '../include',
  ],
  link_with: [libsemanage_static],
  install: false,
)

test(
  'libsemanage',
  libsemanage_tests,
  depends: [nc_files, cil_files],
  workdir: meson.current_build_dir(),
)
