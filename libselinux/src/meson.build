py = import('python').find_installation(pure: false)

selinux_sources = [
  'avc.c',
  'avc_internal.c',
  'avc_internal.h',
  'avc_sidtab.c',
  'avc_sidtab.h',
  'booleans.c',
  'callbacks.c',
  'callbacks.h',
  'canonicalize_context.c',
  'checkAccess.c',
  'check_context.c',
  'checkreqprot.c',
  'compute_av.c',
  'compute_create.c',
  'compute_member.c',
  'compute_relabel.c',
  'compute_user.c',
  'context.c',
  'context_internal.h',
  'deny_unknown.c',
  'disable.c',
  'enabled.c',
  'fgetfilecon.c',
  'file_path_suffixes.h',
  'freecon.c',
  'freeconary.c',
  'fsetfilecon.c',
  'get_context_list.c',
  'get_context_list_internal.h',
  'get_default_type.c',
  'get_default_type_internal.h',
  'get_initial_context.c',
  'getenforce.c',
  'getfilecon.c',
  'getpeercon.c',
  'init.c',
  'is_customizable_type.c',
  'label.c',
  'label_backends_android.c',
  'label_db.c',
  'label_file.c',
  'label_file.h',
  'label_internal.h',
  'label_media.c',
  'label_support.c',
  'label_x.c',
  'lgetfilecon.c',
  'load_policy.c',
  'lsetfilecon.c',
  'mapping.c',
  'mapping.h',
  'matchmediacon.c',
  'matchpathcon.c',
  'policy.h',
  'policyvers.c',
  'procattr.c',
  'query_user_context.c',
  'regex.c',
  'regex.h',
  'reject_unknown.c',
  'selinux_check_securetty_context.c',
  'selinux_config.c',
  'selinux_internal.c',
  'selinux_internal.h',
  'selinux_netlink.h',
  'selinux_restorecon.c',
  'sestatus.c',
  'setenforce.c',
  'setexecfilecon.c',
  'setfilecon.c',
  'setrans_client.c',
  'setrans_internal.h',
  'seusers.c',
  'sha1.c',
  'sha1.h',
  'stringrep.c',
  'validatetrans.c',
]

selinux_includes = ['../include/']

# TODO: include headers from ../include as sources

selinux_map_path = meson.current_source_dir() / 'libselinux.map'

selinux_link_args = [
  '-Wl,--version-script=' + selinux_map_path,
  '-Wl,-z,defs',
  '-Wl,-z,relro',
]

# TODO old pcre3 support
pcre2 = dependency('libpcre2-8', required: true)
add_project_arguments(
  [
    '-DUSE_PCRE2',
    '-DPCRE2_CODE_UNIT_WIDTH=8',
  ],
  language: 'c',
)

libsepol_static = dependency(
  'libsepol',
  fallback: ['libsepol', 'libsepol_static_dep'],
  required: true,
  static: true,
)

libsepol_shared = dependency(
  'libsepol',
  fallback: ['libsepol', 'libsepol_shared_dep'],
  required: true,
)

selinux_static = static_library(
  'selinux',
  include_directories: selinux_includes,
  dependencies: [libsepol_static, pcre2],
  sources: selinux_sources,
  install: true,
)

selinux_shared = shared_library(
  'libselinux',
  name_prefix: '',
  soversion: '1',
  include_directories: selinux_includes,
  sources: selinux_sources,
  dependencies: [libsepol_static, pcre2],
  link_args: selinux_link_args,
  install: true,
)

libselinux_shared_dep = declare_dependency(
  link_with: selinux_shared,
  dependencies: [libsepol_shared, pcre2],
  include_directories: selinux_includes,
)

libselinux_static_dep = declare_dependency(
  link_with: selinux_static,
  dependencies: [libsepol_static, pcre2],
  include_directories: selinux_includes,
)

# ---------- python bindings ---------- #

bash = find_program('bash', required: true)
swig = find_program('swig', required: true)
swig_cmd = [swig, '-Wall']

selinuxswig_python_exception_i = custom_target(
  'selinuxswig_python_exception.i',
  depend_files: ['../include/selinux/selinux.h'],
  input: 'exception.sh',
  output: 'selinuxswig_python_exception.i',
  command: [bash, '-e', '@INPUT@'],
  env: ['LIBSELINUX_SRC=' + meson.current_source_dir()],
  capture: true,
  install: false,
)

selinuxswig_python_wrap_c = custom_target(
  'selinuxswig_python_wrap.c',
  input: 'selinuxswig_python.i',
  output: 'selinuxswig_python_wrap.c',
  command: [
    swig_cmd,
    '-python',
    '-o', '@OUTPUT@',
    '-I' + meson.current_build_dir(),
    '-I' + meson.current_source_dir(), '@INPUT@',
  ],
  depends: selinuxswig_python_exception_i,
)

py.extension_module(
  'audit2why',
  'audit2why.c',
  include_directories: selinux_includes,
  dependencies: [libsepol_static, libselinux_shared_dep],
  install: true,
  subdir: 'selinux',
)

wno_deprecated_declarations = cc.get_supported_arguments('-Wno-deprecated-declarations')
wno_discarded_qualifiers = cc.get_supported_arguments('-Wno-discarded-qualifiers')
wno_missing_prototypes = cc.get_supported_arguments('-Wno-missing-prototypes')
wno_missing_declarations = cc.get_supported_arguments('-Wno-missing-declarations')
wno_undef = cc.get_supported_arguments('-Wno-undef')

pywrap = py.extension_module(
  '_selinux',
  [selinuxswig_python_wrap_c],
  c_args: [
    wno_deprecated_declarations,
    wno_discarded_qualifiers, # Ubuntu 24.04 CI
    wno_undef, # Ubuntu 24.04 CI
    wno_missing_prototypes, # TODO: fix in code: `SWIG_init(void)`
    wno_missing_declarations, # TODO: fix in code: `SWIG_init(void)`
  ],
  include_directories: selinux_includes,
  dependencies: [libselinux_shared_dep],
  install: true,
  subdir: 'selinux',
)

install_symlink(
  pywrap.name() + '.so', # TODO: autodetect extension or retrieve from py.extension_module
  install_dir: py.get_install_dir(),
  pointing_to: 'selinux' / pywrap.name() + '.so',
)

noop = find_program('true')
selinux_py = custom_target(
  input: pywrap,
  output: 'selinux.py',
  command: [noop],
)

cp = find_program('cp')
custom_target(
  input: selinux_py,
  output: '__init__.py',
  command: [cp, '@INPUT@', '@OUTPUT@'],
  install: true,
  install_dir: py.get_install_dir() / 'selinux',
)

# TODO: drop shipping /tmp/destdir_meson/usr/lib/python3/dist-packages/selinux/__pycache__/__init__.cpython-312.pyc ?

# ---------- ruby bindings ---------- #

ruby = find_program('ruby', required: true)

swig_ruby_wrap = custom_target(
  'ruby_wrap',
  input: 'selinuxswig_ruby.i',
  output: 'selinuxswig_ruby_wrap.c',
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

wno_strict_prototypes = cc.get_supported_arguments('-Wno-strict-prototypes')
wno_unused_parameter = cc.get_supported_arguments('-Wno-unused-parameter')
wno_bad_function_cast = cc.get_supported_arguments('-Wno-bad-function-cast')
wno_attribute_warning = cc.get_supported_arguments('-Wno-attribute-warning')
wno_missing_field_initializers = cc.get_supported_arguments('-Wno-missing-field-initializers')
wno_missing_noreturn = cc.get_supported_arguments('-Wno-missing-noreturn')

shared_library(
  'selinux',
  name_prefix: '',
  include_directories: selinux_includes,
  sources: swig_ruby_wrap,
  c_args: [
    ruby_c_args.stdout().split(),
    wno_deprecated_declarations,
    wno_unused_parameter,
    wno_bad_function_cast,
    wno_attribute_warning, # Ubuntu 24.04 CI
    wno_missing_field_initializers, # Ubuntu 24.04 CI
    wno_missing_noreturn, # Ubuntu 24.04 CI
    wno_strict_prototypes, # Ubuntu 24.04 CI
    wno_undef, # Ubuntu 24.04 CI
    wno_missing_declarations, # TODO: fix in code:  `SWIGEXPORT void Init_selinux(void)`
    wno_missing_prototypes, # TODO: fix in code: `SWIGEXPORT void Init_selinux(void)`
  ],
  link_args: [ruby_link_args.stdout().split()],
  link_with: [selinux_shared],
  install: true,
  install_dir: ruby_install_dir.stdout().split(),
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  selinux_shared,
  description: 'SELinux utility library',
  name: 'libselinux',
  filebase: 'libselinux',
  version: meson.project_version(),
  url: 'https://github.com/SELinuxProject/selinux/wiki/Releases',
  # meson >= 1.9.0: requires_private: [libsepol_shared, pcre2],
  requires_private: ['libsepol', 'libpcre2-8'],
)
