project('SELinux userland', 'c', version: '3.10')

libsepol = subproject('libsepol')
libsepol_shared_dep = libsepol.get_variable('libsepol_shared_dep')
libsepol_static_dep = libsepol.get_variable('libsepol_static_dep')

libselinux = subproject('libselinux')
libselinux_shared_dep = libselinux.get_variable('libselinux_shared_dep')

subproject('secilc')

libsemanage = subproject('libsemanage')
libsemanage_shared_dep = libsemanage.get_variable('libsemanage_shared_dep')

subproject('dbus')

subproject('gui')

subproject('mcstrans')

subproject('policycoreutils')

subproject('python')

subproject('restorecond')

subproject('sandbox')

subproject('semodule-utils')
