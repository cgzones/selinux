py = import('python').find_installation(pure: false)

libsemanage_sources = [
  'boolean_internal.h',
  'boolean_record.c',
  'booleans_active.c',
  'booleans_activedb.c',
  'booleans_file.c',
  'booleans_local.c',
  'booleans_policy.c',
  'booleans_policydb.c',
  'compressed_file.c',
  'compressed_file.h',
  'context_record.c',
  'database.c',
  'database.h',
  'database_activedb.c',
  'database_activedb.h',
  'database_file.c',
  'database_file.h',
  'database_join.c',
  'database_join.h',
  'database_llist.c',
  'database_llist.h',
  'database_policydb.c',
  'database_policydb.h',
  'debug.c',
  'debug.h',
  'direct_api.c',
  'direct_api.h',
  'fcontext_internal.h',
  'fcontext_record.c',
  'fcontexts_file.c',
  'fcontexts_local.c',
  'fcontexts_policy.c',
  'genhomedircon.c',
  'genhomedircon.h',
  'handle.c',
  'handle.h',
  'ibendport_internal.h',
  'ibendport_record.c',
  'ibendports_file.c',
  'ibendports_local.c',
  'ibendports_policy.c',
  'ibendports_policydb.c',
  'ibpkey_internal.h',
  'ibpkey_record.c',
  'ibpkeys_file.c',
  'ibpkeys_local.c',
  'ibpkeys_policy.c',
  'ibpkeys_policydb.c',
  'iface_internal.h',
  'iface_record.c',
  'interfaces_file.c',
  'interfaces_local.c',
  'interfaces_policy.c',
  'interfaces_policydb.c',
  'modules.c',
  'modules.h',
  'node_internal.h',
  'node_record.c',
  'nodes_file.c',
  'nodes_local.c',
  'nodes_policy.c',
  'nodes_policydb.c',
  'parse_utils.c',
  'parse_utils.h',
  'policy.h',
  'policy_components.c',
  'port_internal.h',
  'port_record.c',
  'ports_file.c',
  'ports_local.c',
  'ports_policy.c',
  'ports_policydb.c',
  'semanage_conf.h',
  'semanage_store.c',
  'semanage_store.h',
  'seuser_internal.h',
  'seuser_record.c',
  'seusers_file.c',
  'seusers_local.c',
  'seusers_policy.c',
  'sha256.c',
  'sha256.h',
  'user_base_record.c',
  'user_extra_record.c',
  'user_internal.h',
  'user_record.c',
  'users_base_file.c',
  'users_base_policydb.c',
  'users_extra_file.c',
  'users_join.c',
  'users_local.c',
  'users_policy.c',
  'utilities.c',
  'utilities.h',
]

libsemanage_includes = ['../include/']

# ---------- bison + flex grammar ---------- #

prog_flex = find_program(
  'flex',
  required: true,
)

prog_yacc = find_program('bison', required: false, disabler: true)
if prog_yacc.found()
  yacc_cmd = [prog_yacc, '-o', '@OUTPUT0@', '--defines=@OUTPUT1@', '@INPUT@']
else
  prog_yacc = find_program(
    'byacc',
    required: true,
  )
  yacc_cmd = [prog_yacc, '-o', '@OUTPUT0@', '-H', '@OUTPUT1@', '@INPUT@']
endif # prog_yacc.found()

conf_parse_y = custom_target(
  'conf-parse',
  input: 'conf-parse.y',
  output: ['conf-parse.c', 'conf-parse.h'],
  command: yacc_cmd,

)

conf_scan_l = custom_target(
  'conf-scan',
  input: 'conf-scan.l',
  output: 'conf-scan.c',
  depends: conf_parse_y,
  command: [prog_flex, '-s', '-o', '@OUTPUT@', '@INPUT@'],
)

# ---------- libraries ---------- #

# TODO: include headers from ../include as sources

libsemanage_map_path = meson.current_source_dir() / 'libsemanage.map'

libsemanage_link_args = [
  '-Wl,--version-script=' + libsemanage_map_path,
  '-Wl,-z,defs',
  '-Wl,-z,relro',
]

libsepol_static = dependency(
  'libsepol',
  fallback: ['libsepol', 'libsepol_static_dep'],
  required: true,
  static: true,
)
libsepol_shared = dependency('libsepol', fallback: ['libsepol', 'libsepol_shared_dep'], required: true)
libselinux_static = dependency(
  'libselinux',
  fallback: ['libselinux', 'libselinux_static_dep'],
  required: true,
  static: true,
)
libselinux_shared = dependency(
  'libselinux',
  fallback: ['libselinux', 'libselinux_shared_dep'],
  required: true,
)

libaudit = dependency('audit', required: true)
libbz2 = dependency('bzip2', required: true)

libsemanage_static = static_library(
  'semanage',
  include_directories: libsemanage_includes,
  sources: [libsemanage_sources, conf_scan_l, conf_parse_y],
  dependencies: [
    libaudit,
    libbz2,
    libselinux_static,
    libsepol_static,
  ],
  install: true,
)

libsemanage_shared = shared_library(
  'libsemanage',
  name_prefix: '',
  soversion: '2',
  include_directories: libsemanage_includes,
  sources: [libsemanage_sources, conf_scan_l, conf_parse_y],
  dependencies: [
    libaudit,
    libbz2,
    libselinux_shared,
    libsepol_shared,
  ],
  link_args: libsemanage_link_args,
  install: true,
)

libsemanage_shared_dep = declare_dependency(link_with: libsemanage_shared, include_directories: libsemanage_includes)

install_data('semanage.conf', install_dir: get_option('sysconfdir') / 'selinux')

# ---------- python bindings ---------- #

bash = find_program('bash', required: true)
swig = find_program('swig', required: true)
#if get_option('werror')
#  swig_cmd = [swig, '-Wall', '-Werror']
#else
swig_cmd = [swig, '-Wall']
#endif # get_option('werror')

semanage_include_files = files(
  '../include/semanage/boolean_record.h',
  '../include/semanage/booleans_active.h',
  '../include/semanage/booleans_local.h',
  '../include/semanage/booleans_policy.h',
  '../include/semanage/context_record.h',
  '../include/semanage/debug.h',
  '../include/semanage/fcontext_record.h',
  '../include/semanage/fcontexts_local.h',
  '../include/semanage/fcontexts_policy.h',
  '../include/semanage/handle.h',
  '../include/semanage/ibendport_record.h',
  '../include/semanage/ibendports_local.h',
  '../include/semanage/ibendports_policy.h',
  '../include/semanage/ibpkey_record.h',
  '../include/semanage/ibpkeys_local.h',
  '../include/semanage/ibpkeys_policy.h',
  '../include/semanage/iface_record.h',
  '../include/semanage/interfaces_local.h',
  '../include/semanage/interfaces_policy.h',
  '../include/semanage/modules.h',
  '../include/semanage/node_record.h',
  '../include/semanage/nodes_local.h',
  '../include/semanage/nodes_policy.h',
  '../include/semanage/port_record.h',
  '../include/semanage/ports_local.h',
  '../include/semanage/ports_policy.h',
  '../include/semanage/semanage.h',
  '../include/semanage/seuser_record.h',
  '../include/semanage/seusers_local.h',
  '../include/semanage/seusers_policy.h',
  '../include/semanage/user_record.h',
  '../include/semanage/users_local.h',
  '../include/semanage/users_policy.h',
)

semanageswig_python_exception_i = custom_target(
  'semanageswig_python_exception.i',
  depend_files: semanage_include_files,
  input: 'exception.sh',
  output: 'semanageswig_python_exception.i',
  command: [bash, '-e', '@INPUT@'],
  env: ['LIBSEMANAGE_SRC=' + meson.current_source_dir()],
  capture: true,
  install: false,
)

swig_python_wrap = custom_target(
  'python_wrap',
  input: 'semanageswig_python.i',
  output: 'semanageswig_python_wrap.c',
  command: [
    swig_cmd,
    '-python',
    '-o', '@OUTPUT@',
    '-I' + meson.current_build_dir(),
    '-I' + meson.current_source_dir(), '@INPUT@',
  ],
  depends: semanageswig_python_exception_i,
)

wno_undef = cc.get_supported_arguments('-Wno-undef')
wno_deprecated_declarations = cc.get_supported_arguments('-Wno-deprecated-declarations')
wno_missing_prototypes = cc.get_supported_arguments('-Wno-missing-prototypes')
wno_missing_declarations = cc.get_supported_arguments('-Wno-missing-declarations')
wno_unused_variable = cc.get_supported_arguments('-Wno-unused-variable')
wno_unused_parameter = cc.get_supported_arguments('-Wno-unused-parameter')
wno_shadow = cc.get_supported_arguments('-Wno-shadow')
wno_discarded_qualifiers = cc.get_supported_arguments('-Wno-discarded-qualifiers')

pywrap = py.extension_module(
  '_semanage',
  swig_python_wrap,
  c_args: [
    wno_undef, # Ubuntu 24.04 CI
    wno_missing_prototypes, # TODO: fix in code?
    wno_missing_declarations, # TODO: fix in code?
    wno_unused_variable, # TODO: fix in wrapper?
    wno_unused_parameter, # TODO: fix in wrapper!
    wno_shadow, # TODO: fix in wrapper!
    wno_discarded_qualifiers, # TODO: fix in wrapper!
  ],
  include_directories: libsemanage_includes,
  install: true,
)

noop = find_program('true')
custom_target(
  input: pywrap,
  output: 'semanage.py',
  command: [noop],
  install: true,
  install_dir: py.get_install_dir(),
)

# ---------- ruby bindings ---------- #

ruby = find_program('ruby', required: true)

swig_ruby_wrap = custom_target(
  'ruby_wrap',
  input: 'semanageswig_ruby.i',
  output: 'semanageswig_ruby_wrap.c',
  command: [swig_cmd, '-ruby', '-o', '@OUTPUT@', '@INPUT@'],
)

ruby_c_args = run_command(
  [
    ruby,
    '-e', 'puts "-I" + RbConfig::CONFIG["rubyarchhdrdir"] + " -I" + RbConfig::CONFIG["rubyhdrdir"]',
  ],
  capture: true,
  check: true,
)

ruby_link_args = run_command(
  [
    ruby,
    '-e', 'puts "-L" + RbConfig::CONFIG["libdir"] + " -L" + RbConfig::CONFIG["archlibdir"] + " " + RbConfig::CONFIG["LIBRUBYARG_SHARED"]',
  ],
  capture: true,
  check: true,
)

ruby_install_dir = run_command(
  [ruby, '-e', 'puts RbConfig::CONFIG["vendorarchdir"]'],
  capture: true,
  check: true,
)

wno_bad_function_cast = cc.get_supported_arguments('-Wno-bad-function-cast')
wno_strict_prototypes = cc.get_supported_arguments('-Wno-strict-prototypes')
wno_attribute_warning = cc.get_supported_arguments('-Wno-attribute-warning')
wno_missing_field_initializers = cc.get_supported_arguments('-Wno-missing-field-initializers')
wno_missing_noreturn = cc.get_supported_arguments('-Wno-missing-noreturn')

shared_library(
  'semanage',
  name_prefix: '',
  include_directories: libsemanage_includes,
  sources: swig_ruby_wrap,
  c_args: [
    ruby_c_args.stdout().split(),
    wno_unused_parameter,
    wno_bad_function_cast,
    wno_strict_prototypes,
    wno_undef, # Ubuntu 24.04 CI
    wno_deprecated_declarations, # Ubuntu 24.04 CI
    wno_attribute_warning, # Ubuntu 24.04 CI
    wno_missing_field_initializers, # Ubuntu 24.04 CI
    wno_missing_noreturn, # Ubuntu 24.04 CI
    wno_missing_prototypes, # TODO: fix in code?
    wno_missing_declarations, # TODO: fix in code?
  ],
  link_args: [ruby_link_args.stdout().split()],
  dependencies: [libsemanage_shared_dep],
  install: true,
  install_dir: ruby_install_dir.stdout().split(),
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  libsemanage_shared,
  description: 'SELinux management library',
  name: 'libsemanage',
  filebase: 'libsemanage',
  version: meson.project_version(),
  url: 'https://github.com/SELinuxProject/selinux/wiki/Releases',
  # meson >= 1.9.0: requires_private: [libsepol, libselinux],
  requires_private: ['libsepol', 'libselinux'],
)
