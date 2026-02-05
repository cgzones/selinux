sepol_sources = files(
  'assertion.c',
  'avrule_block.c',
  'avtab.c',
  'boolean_internal.h',
  'boolean_record.c',
  'booleans.c',
  'conditional.c',
  'constraint.c',
  'context.c',
  'context.h',
  'context_internal.h',
  'context_record.c',
  'debug.c',
  'debug.h',
  'ebitmap.c',
  'expand.c',
  'flask.h',
  'handle.c',
  'handle.h',
  'hashtab.c',
  'hierarchy.c',
  'ibendport_internal.h',
  'ibendport_record.c',
  'ibendports.c',
  'ibpkey_internal.h',
  'ibpkey_record.c',
  'ibpkeys.c',
  'iface_internal.h',
  'iface_record.c',
  'interfaces.c',
  'kernel_to_cil.c',
  'kernel_to_common.c',
  'kernel_to_common.h',
  'kernel_to_conf.c',
  'link.c',
  'mls.c',
  'mls.h',
  'module.c',
  'module_internal.h',
  'module_to_cil.c',
  'node_internal.h',
  'node_record.c',
  'nodes.c',
  'optimize.c',
  'polcaps.c',
  'policydb.c',
  'policydb_convert.c',
  'policydb_internal.h',
  'policydb_public.c',
  'policydb_validate.c',
  'policydb_validate.h',
  'port_internal.h',
  'port_record.c',
  'ports.c',
  'private.h',
  'services.c',
  'sidtab.c',
  'symtab.c',
  'user_internal.h',
  'user_record.c',
  'users.c',
  'util.c',
  'write.c',
)

sepol_includes = ['../include/']

# TODO: include headers from ../include as sources

if enable_cil
  cil_sources = files(
    '../cil/src/cil.c',
    '../cil/src/cil_binary.c',
    '../cil/src/cil_binary.h',
    '../cil/src/cil_build_ast.c',
    '../cil/src/cil_build_ast.h',
    '../cil/src/cil_copy_ast.c',
    '../cil/src/cil_copy_ast.h',
    '../cil/src/cil_deny.c',
    '../cil/src/cil_deny.h',
    '../cil/src/cil_find.c',
    '../cil/src/cil_find.h',
    '../cil/src/cil_flavor.h',
    '../cil/src/cil_fqn.c',
    '../cil/src/cil_fqn.h',
    '../cil/src/cil_internal.h',
    '../cil/src/cil_lexer.h',
    #flex_gen.process('../cil/src/cil_lexer.l'),
    '../cil/src/cil_list.c',
    '../cil/src/cil_list.h',
    '../cil/src/cil_log.c',
    '../cil/src/cil_log.h',
    '../cil/src/cil_mem.c',
    '../cil/src/cil_mem.h',
    '../cil/src/cil_parser.c',
    '../cil/src/cil_parser.h',
    '../cil/src/cil_policy.c',
    '../cil/src/cil_policy.h',
    '../cil/src/cil_post.c',
    '../cil/src/cil_post.h',
    '../cil/src/cil_reset_ast.c',
    '../cil/src/cil_reset_ast.h',
    '../cil/src/cil_resolve_ast.c',
    '../cil/src/cil_resolve_ast.h',
    '../cil/src/cil_stack.c',
    '../cil/src/cil_stack.h',
    '../cil/src/cil_strpool.c',
    '../cil/src/cil_strpool.h',
    '../cil/src/cil_symtab.c',
    '../cil/src/cil_symtab.h',
    '../cil/src/cil_tree.c',
    '../cil/src/cil_tree.h',
    '../cil/src/cil_verify.c',
    '../cil/src/cil_verify.h',
    '../cil/src/cil_write_ast.c',
    '../cil/src/cil_write_ast.h',
  )

  cil_includes = [
    '../cil/include',
    '../cil/src',
  ]

  cil_lexer_l = custom_target(
    'cil_lexer',
    input: '../cil/src/cil_lexer.l',
    output: 'cil_lexer.c',
    command: [prog_flex, '-o', '@OUTPUT@', '@INPUT@'],
  )

  sepol_sources += cil_sources
  sepol_sources += cil_lexer_l
  sepol_includes += cil_includes
endif # enable_cil

sepol_map_file = 'libsepol.map'
sepol_map_in_file = 'libsepol.map.in'

if enable_cil
  sepol_map_target = custom_target(
    'sepol_map',
    output: sepol_map_file,
    input: sepol_map_in_file,
    command: ['cp', '@INPUT@', '@OUTPUT@'],
  )
else
  sepol_map_target = custom_target(
    'sepol_map',
    output: sepol_map_file,
    input: sepol_map_in_file,
    command: ['sed', '-e', '/^\s*cil_/d', '@INPUT@', '@OUTPUT@'],
  )
endif # enable_cil

sepol_map_path = meson.current_build_dir() / sepol_map_file

sepol_link_deps = [sepol_map_target]

sepol_link_args = [
  '-Wl,--version-script=' + sepol_map_path,
  '-Wl,-z,defs',
  '-Wl,-z,relro',
]

sepol_static = static_library(
  'sepol',
  include_directories: sepol_includes,
  sources: sepol_sources,
  install: true,
)

sepol_shared = shared_library(
  'sepol',
  soversion: '2',
  include_directories: sepol_includes,
  sources: sepol_sources,
  link_depends: sepol_link_deps,
  link_args: sepol_link_args,
  install: true,
)

pkgconfig = import('pkgconfig')
pkgconfig.generate(
  sepol_shared,
  description: 'SELinux policy library',
  name: 'libsepol',
  filebase: 'libsepol',
  version: meson.project_version(),
  url: 'https://github.com/SELinuxProject/selinux/wiki/Releases',
)

libsepol_static_dep = declare_dependency(link_with: sepol_static, include_directories: sepol_includes)
libsepol_shared_dep = declare_dependency(link_with: sepol_shared, include_directories: sepol_includes)
