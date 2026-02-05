py = import('python').find_installation(pure: false)

sources = files(
  '__init__.py',
  'access.py',
  'audit.py',
  'classperms.py',
  'defaults.py',
  'interfaces.py',
  'lex.py',
  'matching.py',
  'module.py',
  'objectmodel.py',
  'output.py',
  'policygen.py',
  'refparser.py',
  'refpolicy.py',
  'sepolgeni18n.py',
  'util.py',
  'yacc.py',
)

install_data(
  sources,
  install_dir: py.get_install_dir() / 'sepolgen',
  install_mode: 'rw-r--r--',
)
