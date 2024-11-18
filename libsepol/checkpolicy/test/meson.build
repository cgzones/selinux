utils = [
  ['dismod', 'dismod.c'],
  ['dispol', 'dispol.c'],
]

foreach util : utils
  executable(
    util[0],
    sources: [util[1]],
    include_directories: ['../../include'], #TODO: check if recompiles after header change
    install: false,
    link_args: [exe_link_args],
    link_with: [sepol_static],
  )
endforeach
