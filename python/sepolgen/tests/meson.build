python = find_program('python3')

run_tests_py = fs.copyfile('run-tests.py')
test_access_py = fs.copyfile('test_access.py')
test_audit_py = fs.copyfile('test_audit.py')
test_interfaces_py = fs.copyfile('test_interfaces.py')
test_matching_py = fs.copyfile('test_matching.py')
test_module_py = fs.copyfile('test_module.py')
test_objectmodel_py = fs.copyfile('test_objectmodel.py')
test_policygen_py = fs.copyfile('test_policygen.py')
test_refparser_py = fs.copyfile('test_refparser.py')
test_refpolicy_py = fs.copyfile('test_refpolicy.py')
audit_txt = fs.copyfile('audit.txt')
perm_map = fs.copyfile('perm_map')
module_compile_test_te = fs.copyfile('module_compile_test.te')

test(
  'test-sepolgen',
  python,
  args: ['run-tests.py'],
  depends: [
    run_tests_py,
    test_access_py,
    test_audit_py,
    test_interfaces_py,
    test_matching_py,
    test_module_py,
    test_objectmodel_py,
    test_policygen_py,
    test_refparser_py,
    test_refpolicy_py,
    audit_txt,
    perm_map,
    module_compile_test_te,
  ],
  workdir: meson.current_build_dir(),
)
