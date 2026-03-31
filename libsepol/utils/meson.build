utils = [
  ['chkcon', 'chkcon.c'],
  ['sepol_check_access', 'sepol_check_access.c'],
  ['sepol_compute_av', 'sepol_compute_av.c'],
  ['sepol_compute_member', 'sepol_compute_member.c'],
  ['sepol_compute_relabel', 'sepol_compute_relabel.c'],
  ['sepol_validate_transition', 'sepol_validate_transition.c'],

]

foreach util: utils
  executable(
    util[0],
    sources: [util[1]],
    include_directories: sepol_includes,
    install: true,
    link_args: [exe_link_args],
    link_with: [sepol_shared],
  )
endforeach
