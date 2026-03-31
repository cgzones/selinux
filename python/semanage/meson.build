py = import('python').find_installation(pure: false)

install_data('semanage', install_dir: get_option('sbindir'), install_mode: 'rwxr-xr-x')

install_data('seobject.py', install_dir: py.get_install_dir(), install_mode: 'rw-r--r--') # TODO: verify path

bash_completion_package = dependency('bash-completion', required: false)

if bash_completion_package.found()
  bash_completion_dir = bash_completion_package.get_variable(pkgconfig: 'completionsdir')
else
  bash_completion_dir = join_paths(
    get_option('prefix'),
    get_option('datadir'),
    'bash-completion',
    'completions',
  )
endif

install_data(
  'semanage-bash-completion.sh',
  install_dir: bash_completion_dir,
  install_mode: 'rw-r--r--',
  rename: 'semanage',
)

install_man(
  [
    'semanage.8',
    'semanage-boolean.8',
    'semanage-dontaudit.8',
    'semanage-export.8',
    'semanage-fcontext.8',
    'semanage-ibendport.8',
    'semanage-ibpkey.8',
    'semanage-import.8',
    'semanage-interface.8',
    'semanage-login.8',
    'semanage-module.8',
    'semanage-node.8',
    'semanage-permissive.8',
    'semanage-port.8',
    'semanage-user.8',
  ],
)

python = find_program('python3')

test_semanage_py = fs.copyfile('test-semanage.py')

test(
  'test-semanage',
  python,
  args: ['test-semanage.py', '-a'],
  depends: test_semanage_py,
  workdir: meson.current_build_dir(),
)
