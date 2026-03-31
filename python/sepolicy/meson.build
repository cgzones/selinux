py = import('python').find_installation(pure: false)

sources = files(
  'sepolicy/__init__.py',
  'sepolicy/booleans.py',
  'sepolicy/communicate.py',
  'sepolicy/generate.py',
  'sepolicy/gui.py',
  'sepolicy/interface.py',
  'sepolicy/manpage.py',
  'sepolicy/network.py',
  'sepolicy/sedbus.py',
  'sepolicy/sepolicy.glade',
  'sepolicy/transition.py',
)

py.install_sources(
  sources,
  subdir: 'sepolicy',
)

help_sources = files(
  'sepolicy/help/__init__.py',
  'sepolicy/help/booleans.png',
  'sepolicy/help/booleans.txt',
  'sepolicy/help/booleans_more.png',
  'sepolicy/help/booleans_more.txt',
  'sepolicy/help/booleans_more_show.png',
  'sepolicy/help/booleans_more_show.txt',
  'sepolicy/help/booleans_toggled.png',
  'sepolicy/help/booleans_toggled.txt',
  'sepolicy/help/file_equiv.png',
  'sepolicy/help/file_equiv.txt',
  'sepolicy/help/files_apps.png',
  'sepolicy/help/files_apps.txt',
  'sepolicy/help/files_exec.png',
  'sepolicy/help/files_exec.txt',
  'sepolicy/help/files_write.png',
  'sepolicy/help/files_write.txt',
  'sepolicy/help/lockdown.png',
  'sepolicy/help/lockdown.txt',
  'sepolicy/help/lockdown_permissive.png',
  'sepolicy/help/lockdown_permissive.txt',
  'sepolicy/help/lockdown_ptrace.png',
  'sepolicy/help/lockdown_ptrace.txt',
  'sepolicy/help/lockdown_unconfined.png',
  'sepolicy/help/lockdown_unconfined.txt',
  'sepolicy/help/login.png',
  'sepolicy/help/login.txt',
  'sepolicy/help/login_default.png',
  'sepolicy/help/login_default.txt',
  'sepolicy/help/ports_inbound.png',
  'sepolicy/help/ports_inbound.txt',
  'sepolicy/help/ports_outbound.png',
  'sepolicy/help/ports_outbound.txt',
  'sepolicy/help/start.png',
  'sepolicy/help/start.txt',
  'sepolicy/help/system.png',
  'sepolicy/help/system.txt',
  'sepolicy/help/system_boot_mode.png',
  'sepolicy/help/system_boot_mode.txt',
  'sepolicy/help/system_current_mode.png',
  'sepolicy/help/system_current_mode.txt',
  'sepolicy/help/system_export.png',
  'sepolicy/help/system_export.txt',
  'sepolicy/help/system_policy_type.png',
  'sepolicy/help/system_policy_type.txt',
  'sepolicy/help/system_relabel.png',
  'sepolicy/help/system_relabel.txt',
  'sepolicy/help/transition_file.png',
  'sepolicy/help/transition_file.txt',
  'sepolicy/help/transition_from.png',
  'sepolicy/help/transition_from.txt',
  'sepolicy/help/transition_from_boolean.png',
  'sepolicy/help/transition_from_boolean.txt',
  'sepolicy/help/transition_from_boolean_1.png',
  'sepolicy/help/transition_from_boolean_1.txt',
  'sepolicy/help/transition_from_boolean_2.png',
  'sepolicy/help/transition_from_boolean_2.txt',
  'sepolicy/help/transition_to.png',
  'sepolicy/help/transition_to.txt',
  'sepolicy/help/users.png',
  'sepolicy/help/users.txt',
)

py.install_sources(
  help_sources,
  subdir: 'sepolicy' / 'help',
)

templates_sources = files(
  'sepolicy/templates/__init__.py',
  'sepolicy/templates/boolean.py',
  'sepolicy/templates/etc_rw.py',
  'sepolicy/templates/executable.py',
  'sepolicy/templates/network.py',
  'sepolicy/templates/rw.py',
  'sepolicy/templates/script.py',
  'sepolicy/templates/semodule.py',
  'sepolicy/templates/spec.py',
  'sepolicy/templates/test_module.py',
  'sepolicy/templates/tmp.py',
  'sepolicy/templates/unit_file.py',
  'sepolicy/templates/user.py',
  'sepolicy/templates/var_cache.py',
  'sepolicy/templates/var_lib.py',
  'sepolicy/templates/var_log.py',
  'sepolicy/templates/var_run.py',
  'sepolicy/templates/var_spool.py',
)

py.install_sources(
  templates_sources,
  subdir: 'sepolicy' / 'templates',
)

install_data(
  'sepolicy.py',
  install_dir: get_option('bindir'),
  install_mode: 'rwxr-xr-x',
  rename: 'sepolicy',
)

install_symlink('sepolgen', install_dir: get_option('bindir'), pointing_to: 'sepolicy')

install_man(
  [
    'sepolgen.8',
    'sepolicy.8',
    'sepolicy-booleans.8',
    'sepolicy-communicate.8',
    'sepolicy-generate.8',
    'sepolicy-gui.8',
    'sepolicy-interface.8',
    'sepolicy-manpage.8',
    'sepolicy-network.8',
    'sepolicy-transition.8',
  ],
)

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
  'sepolicy-bash-completion.sh',
  install_dir: bash_completion_dir,
  install_mode: 'rw-r--r--',
  rename: 'sepolicy',
)

python = find_program('python3')

test_semanage_py = fs.copyfile('test_sepolicy.py')

test(
  'test-sepolicy',
  python,
  args: ['test_sepolicy.py', '-v'],
  depends: test_semanage_py,
  workdir: meson.current_build_dir(),
)
