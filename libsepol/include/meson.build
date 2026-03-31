sepol_headers = files(
  'sepol/boolean_record.h',
  'sepol/booleans.h',
  'sepol/context.h',
  'sepol/context_record.h',
  'sepol/debug.h',
  'sepol/errcodes.h',
  'sepol/handle.h',
  'sepol/ibendport_record.h',
  'sepol/ibendports.h',
  'sepol/ibpkey_record.h',
  'sepol/ibpkeys.h',
  'sepol/iface_record.h',
  'sepol/interfaces.h',
  'sepol/kernel_to_cil.h',
  'sepol/kernel_to_conf.h',
  'sepol/module.h',
  'sepol/module_to_cil.h',
  'sepol/node_record.h',
  'sepol/nodes.h',
  'sepol/policydb.h',
  'sepol/policydb/avrule_block.h',
  'sepol/policydb/avtab.h',
  'sepol/policydb/conditional.h',
  'sepol/policydb/constraint.h',
  'sepol/policydb/context.h',
  'sepol/policydb/ebitmap.h',
  'sepol/policydb/expand.h',
  'sepol/policydb/flask_types.h',
  'sepol/policydb/hashtab.h',
  'sepol/policydb/hierarchy.h',
  'sepol/policydb/link.h',
  'sepol/policydb/mls_types.h',
  'sepol/policydb/module.h',
  'sepol/policydb/polcaps.h',
  'sepol/policydb/policydb.h',
  'sepol/policydb/services.h',
  'sepol/policydb/sidtab.h',
  'sepol/policydb/symtab.h',
  'sepol/policydb/util.h',
  'sepol/port_record.h',
  'sepol/ports.h',
  'sepol/sepol.h',
  'sepol/user_record.h',
  'sepol/users.h',
)

cil_headers = files(
  '../cil/include/cil/cil.h',
)

install_headers(
  sepol_headers,
  preserve_path: true,
)

if enable_cil
  install_headers(
    cil_headers,
    subdir: 'sepol/cil',
  )
endif # enable_cil
