#!/usr/bin/python3

import selinux
import unittest


IS_SELINUX_ENABLED: bool = False


class TestSelinux(unittest.TestCase):

    def test_constants(self):
        self.assertEqual(selinux.AVC_CACHE_STATS, 1)
        self.assertEqual(selinux.AVC_CALLBACK_AUDITALLOW_DISABLE, 0x20)
        self.assertEqual(selinux.AVC_CALLBACK_AUDITALLOW_ENABLE, 0x10)
        self.assertEqual(selinux.AVC_CALLBACK_AUDITDENY_DISABLE, 0x80)
        self.assertEqual(selinux.AVC_CALLBACK_AUDITDENY_ENABLE, 0x40)
        self.assertEqual(selinux.AVC_CALLBACK_GRANT, 0x1)
        self.assertEqual(selinux.AVC_CALLBACK_RESET, 0x8)
        self.assertEqual(selinux.AVC_CALLBACK_REVOKE, 0x4)
        self.assertEqual(selinux.AVC_CALLBACK_TRY_REVOKE, 0x2)
        self.assertEqual(selinux.AVC_OPT_SETENFORCE, 1)
        self.assertEqual(selinux.AVC_OPT_UNUSED, 0)
        self.assertEqual(selinux.DELETED_MATCH, 2)
        self.assertEqual(selinux.DELETED_NOMATCH, 3)
        self.assertEqual(selinux.DISABLED, -1)
        self.assertEqual(selinux.ENFORCING, 1)
        self.assertEqual(selinux.ERROR, 4)
        self.assertEqual(selinux.MATCH, 0)
        self.assertEqual(selinux.MATCHPATHCON_BASEONLY, 0x1)
        self.assertEqual(selinux.MATCHPATHCON_NOTRANS, 0x2)
        self.assertEqual(selinux.MATCHPATHCON_VALIDATE, 0x4)
        self.assertEqual(selinux.NOMATCH, 1)
        self.assertEqual(selinux.PERMISSIVE, 0)
        self.assertEqual(selinux.SELABEL_CTX_ANDROID_PROP, 4)
        self.assertEqual(selinux.SELABEL_CTX_ANDROID_SERVICE, 5)
        self.assertEqual(selinux.SELABEL_CTX_DB, 3)
        self.assertEqual(selinux.SELABEL_CTX_FILE, 0)
        self.assertEqual(selinux.SELABEL_CTX_MEDIA, 1)
        self.assertEqual(selinux.SELABEL_CTX_X, 2)
        self.assertEqual(selinux.SELABEL_DB_BLOB, 8)
        self.assertEqual(selinux.SELABEL_DB_COLUMN, 4)
        self.assertEqual(selinux.SELABEL_DB_DATABASE, 1)
        self.assertEqual(selinux.SELABEL_DB_DATATYPE, 12)
        self.assertEqual(selinux.SELABEL_DB_EXCEPTION, 11)
        self.assertEqual(selinux.SELABEL_DB_LANGUAGE, 10)
        self.assertEqual(selinux.SELABEL_DB_PROCEDURE, 7)
        self.assertEqual(selinux.SELABEL_DB_SCHEMA, 2)
        self.assertEqual(selinux.SELABEL_DB_SEQUENCE, 5)
        self.assertEqual(selinux.SELABEL_DB_TABLE, 3)
        self.assertEqual(selinux.SELABEL_DB_TUPLE, 9)
        self.assertEqual(selinux.SELABEL_DB_VIEW, 6)
        self.assertEqual(selinux.SELABEL_EQUAL, 1)
        self.assertEqual(selinux.SELABEL_INCOMPARABLE, 3)
        self.assertEqual(selinux.SELABEL_NOPT, 6)
        self.assertEqual(selinux.SELABEL_OPT_BASEONLY, 2)
        self.assertEqual(selinux.SELABEL_OPT_DIGEST, 5)
        self.assertEqual(selinux.SELABEL_OPT_PATH, 3)
        self.assertEqual(selinux.SELABEL_OPT_SUBSET, 4)
        self.assertEqual(selinux.SELABEL_OPT_UNUSED, 0)
        self.assertEqual(selinux.SELABEL_OPT_VALIDATE, 1)
        self.assertEqual(selinux.SELABEL_SUBSET, 0)
        self.assertEqual(selinux.SELABEL_SUPERSET, 2)
        self.assertEqual(selinux.SELABEL_X_CLIENT, 3)
        self.assertEqual(selinux.SELABEL_X_EVENT, 4)
        self.assertEqual(selinux.SELABEL_X_EXT, 2)
        self.assertEqual(selinux.SELABEL_X_POLYPROP, 6)
        self.assertEqual(selinux.SELABEL_X_POLYSELN, 7)
        self.assertEqual(selinux.SELABEL_X_PROP, 1)
        self.assertEqual(selinux.SELABEL_X_SELN, 5)
        self.assertEqual(selinux.SELINUX_AVC, 3)
        self.assertEqual(selinux.SELINUX_AVD_FLAGS_PERMISSIVE, 0x1)
        self.assertEqual(selinux.SELINUX_CB_AUDIT, 1)
        self.assertEqual(selinux.SELINUX_CB_LOG, 0)
        self.assertEqual(selinux.SELINUX_CB_POLICYLOAD, 4)
        self.assertEqual(selinux.SELINUX_CB_SETENFORCE, 3)
        self.assertEqual(selinux.SELINUX_CB_VALIDATE, 2)
        self.assertEqual(selinux.SELINUX_DEFAULTUSER, 'user_u')
        self.assertEqual(selinux.SELINUX_ERROR, 0)
        self.assertEqual(selinux.SELINUX_INFO, 2)
        self.assertEqual(selinux.SELINUX_POLICYLOAD, 4)
        self.assertEqual(selinux.SELINUX_RESTORECON_ABORT_ON_ERROR, 0x200)
        self.assertEqual(selinux.SELINUX_RESTORECON_ADD_ASSOC, 0x100)
        self.assertEqual(selinux.SELINUX_RESTORECON_CONFLICT_ERROR, 0x10000)
        self.assertEqual(selinux.SELINUX_RESTORECON_COUNT_ERRORS, 0x20000)
        self.assertEqual(selinux.SELINUX_RESTORECON_IGNORE_DIGEST, 0x1)
        self.assertEqual(selinux.SELINUX_RESTORECON_IGNORE_MOUNTS, 0x2000)
        self.assertEqual(selinux.SELINUX_RESTORECON_IGNORE_NOENTRY, 0x1000)
        self.assertEqual(selinux.SELINUX_RESTORECON_LOG_MATCHES, 0x800)
        self.assertEqual(selinux.SELINUX_RESTORECON_MASS_RELABEL, 0x4000)
        self.assertEqual(selinux.SELINUX_RESTORECON_NOCHANGE, 0x2)
        self.assertEqual(selinux.SELINUX_RESTORECON_PROGRESS, 0x20)
        self.assertEqual(selinux.SELINUX_RESTORECON_REALPATH, 0x40)
        self.assertEqual(selinux.SELINUX_RESTORECON_RECURSE, 0x8)
        self.assertEqual(selinux.SELINUX_RESTORECON_SET_SPECFILE_CTX, 0x4)
        self.assertEqual(selinux.SELINUX_RESTORECON_SKIP_DIGEST, 0x8000)
        self.assertEqual(selinux.SELINUX_RESTORECON_SYSLOG_CHANGES, 0x400)
        self.assertEqual(selinux.SELINUX_RESTORECON_VERBOSE, 0x10)
        self.assertEqual(selinux.SELINUX_RESTORECON_XATTR_DELETE_ALL_DIGESTS, 0x4)
        self.assertEqual(selinux.SELINUX_RESTORECON_XATTR_DELETE_NONMATCH_DIGESTS, 0x2)
        self.assertEqual(selinux.SELINUX_RESTORECON_XATTR_IGNORE_MOUNTS, 0x8)
        self.assertEqual(selinux.SELINUX_RESTORECON_XATTR_RECURSE, 0x1)
        self.assertEqual(selinux.SELINUX_RESTORECON_XDEV, 0x80)
        self.assertEqual(selinux.SELINUX_SETENFORCE, 5)
        self.assertEqual(selinux.SELINUX_TRANS_DIR, '/var/run/setrans')
        self.assertEqual(selinux.SELINUX_WARNING, 1)


    def test_is_enabled(self):
        self.assertIn(selinux.is_selinux_enabled(), [0, 1])
        self.assertIn(selinux.is_selinux_mls_enabled(), [0, 1])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getenforce(self):
        self.assertIn(selinux.security_getenforce(), [-1, 0, 1])


    def test_getcon(self):
        with open('/proc/self/attr/current', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getcon_raw(), [0, file_contents])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getexeccon(self):
        with open('/proc/self/attr/exec', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getexeccon_raw(), [0, file_contents])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getprevcon(self):
        with open('/proc/self/attr/prev', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getprevcon_raw(), [0, file_contents])


    def test_getpidcon(self):
        with open('/proc/1/attr/current', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getpidcon_raw(1), [0, file_contents])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getfscreatecon(self):
        with open('/proc/self/attr/fscreate', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getfscreatecon_raw(), [0, file_contents])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getkeycreatecon(self):
        with open('/proc/self/attr/keycreate', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getkeycreatecon_raw(), [0, file_contents])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getpidprevcon(self):
        with open('/proc/1/attr/prev', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getpidprevcon_raw(1), [0, file_contents])


    @unittest.skipIf(not IS_SELINUX_ENABLED, "only works with SELinux enabled")
    def test_getsockcreatecon(self):
        with open('/proc/self/attr/sockcreate', 'r') as file:
            file_contents = file.read()

        self.assertEqual(selinux.getsockcreatecon_raw(), [0, file_contents])


if __name__ == '__main__':
    IS_SELINUX_ENABLED = selinux.is_selinux_enabled()
    unittest.main()


# TODO:
# [ 'SELboolean', 'av_decision', 'avc_audit', 'avc_av_stats', 'avc_cache_stats', 'avc_cleanup', 'avc_compute_create', 'avc_compute_member', 'avc_context_to_sid', 'avc_context_to_sid_raw', 'avc_destroy', 'avc_entry_ref', 'avc_get_initial_sid', 'avc_has_perm', 'avc_has_perm_noaudit', 'avc_init', 'avc_lock_callback', 'avc_log_callback', 'avc_memory_callback', 'avc_netlink_close', 'avc_netlink_loop', 'avc_netlink_open', 'avc_open', 'avc_reset', 'avc_sid_stats', 'avc_sid_to_context', 'avc_sid_to_context_raw', 'avc_thread_callback', 'chcon', 'checkPasswdAccess', 'context_free', 'context_new', 'context_range_get', 'context_range_set', 'context_role_get', 'context_role_set', 'context_s_t', 'context_str', 'context_type_get', 'context_type_set', 'context_user_get', 'context_user_set', 'copytree', 'dir_xattr', 'fgetfilecon', 'fgetfilecon_raw', 'fini_selinuxmnt', 'fsetfilecon', 'fsetfilecon_raw', 'get_default_context', 'get_default_context_with_level', 'get_default_context_with_role', 'get_default_context_with_rolelevel', 'get_default_type', 'get_ordered_context_list', 'get_ordered_context_list_with_level', 'getcon', 'getexeccon', 'getfilecon', 'getfilecon_raw', 'getfscreatecon', 'getkeycreatecon', 'getpeercon', 'getpeercon_raw', 'getpidcon', 'getpidprevcon', 'getprevcon', 'getseuser', 'getseuserbyname', 'getsockcreatecon', 'install', 'is_context_customizable', 'lgetfilecon', 'lgetfilecon_raw', 'lsetfilecon', 'lsetfilecon_raw', 'manual_user_enter_context', 'matchmediacon', 'matchpathcon', 'matchpathcon_checkmatches', 'matchpathcon_filespec_add', 'matchpathcon_filespec_destroy', 'matchpathcon_filespec_eval', 'matchpathcon_fini', 'matchpathcon_index', 'matchpathcon_init', 'matchpathcon_init_prefix', 'mode_to_security_class', 'print_access_vector', 'query_user_context', 'realpath_not_final', 'restorecon', 'security_av_perm_to_string', 'security_av_string', 'security_canonicalize_context', 'security_canonicalize_context_raw', 'security_check_context', 'security_check_context_raw', 'security_class_mapping', 'security_class_to_string', 'security_commit_booleans', 'security_compute_av', 'security_compute_av_flags', 'security_compute_av_flags_raw', 'security_compute_av_raw', 'security_compute_create', 'security_compute_create_name', 'security_compute_create_name_raw', 'security_compute_create_raw', 'security_compute_member', 'security_compute_member_raw', 'security_compute_relabel', 'security_compute_relabel_raw', 'security_compute_user', 'security_compute_user_raw', 'security_deny_unknown', 'security_disable', 'security_get_boolean_active', 'security_get_boolean_names', 'security_get_boolean_pending', 'security_get_checkreqprot', 'security_get_initial_context', 'security_get_initial_context_raw', 'security_id', 'security_load_booleans', 'security_load_policy', 'security_policyvers', 'security_reject_unknown', 'security_set_boolean', 'security_set_boolean_list', 'security_setenforce', 'security_validatetrans', 'security_validatetrans_raw', 'selabel_close', 'selabel_cmp', 'selabel_digest', 'selabel_get_digests_all_partial_matches', 'selabel_hash_all_partial_matches', 'selabel_lookup', 'selabel_lookup_best_match', 'selabel_lookup_best_match_raw', 'selabel_lookup_raw', 'selabel_open', 'selabel_partial_match', 'selabel_stats', 'selinux_binary_policy_path', 'selinux_boolean_sub', 'selinux_booleans_path', 'selinux_booleans_subs_path', 'selinux_callback', 'selinux_check_access', 'selinux_check_passwd_access', 'selinux_check_securetty_context', 'selinux_colors_path', 'selinux_contexts_path', 'selinux_current_policy_path', 'selinux_customizable_types_path', 'selinux_default_context_path', 'selinux_default_type_path', 'selinux_failsafe_context_path', 'selinux_file_context_cmp', 'selinux_file_context_homedir_path', 'selinux_file_context_local_path', 'selinux_file_context_path', 'selinux_file_context_subs_dist_path', 'selinux_file_context_subs_path', 'selinux_file_context_verify', 'selinux_flush_class_cache', 'selinux_get_callback', 'selinux_getenforcemode', 'selinux_getpolicytype', 'selinux_homedir_context_path', 'selinux_init_load_policy', 'selinux_lsetfilecon_default', 'selinux_lxc_contexts_path', 'selinux_media_context_path', 'selinux_mkload_policy', 'selinux_netfilter_context_path', 'selinux_openrc_contexts_path', 'selinux_openssh_contexts_path', 'selinux_opt', 'selinux_path', 'selinux_policy_root', 'selinux_raw_context_to_color', 'selinux_raw_to_trans_context', 'selinux_removable_context_path', 'selinux_reset_config', 'selinux_restorecon', 'selinux_restorecon_default_handle', 'selinux_restorecon_get_skipped_errors', 'selinux_restorecon_parallel', 'selinux_restorecon_set_alt_rootpath', 'selinux_restorecon_set_exclude_list', 'selinux_restorecon_set_sehandle', 'selinux_restorecon_xattr', 'selinux_securetty_types_path', 'selinux_sepgsql_context_path', 'selinux_set_callback', 'selinux_set_mapping', 'selinux_set_policy_root', 'selinux_snapperd_contexts_path', 'selinux_status_close', 'selinux_status_deny_unknown', 'selinux_status_getenforce', 'selinux_status_open', 'selinux_status_policyload', 'selinux_status_updated', 'selinux_systemd_contexts_path', 'selinux_trans_to_raw_context', 'selinux_translations_path', 'selinux_user_contexts_path', 'selinux_users_path', 'selinux_usersconf_path', 'selinux_virtual_domain_context_path', 'selinux_virtual_image_context_path', 'selinux_x_context_path', 'selinuxfs_exists', 'set_matchpathcon_flags', 'set_selinuxmnt', 'setcon', 'setcon_raw', 'setexeccon', 'setexeccon_raw', 'setexecfilecon', 'setfilecon', 'setfilecon_raw', 'setfscreatecon', 'setfscreatecon_raw', 'setkeycreatecon', 'setkeycreatecon_raw', 'setsockcreatecon', 'setsockcreatecon_raw', 'shutil', 'sidget', 'sidput', 'string_to_av_perm', 'string_to_security_class']

