#!/bin/bash

function except() {
case $1 in
    selinux_file_context_cmp) # ignore
    ;;
    *)
echo "
%exception $1 {
  \$action
  if (result < 0) {
     PyErr_SetFromErrno(PyExc_OSError);
     SWIG_fail;
  }
}"
;;
esac
}

# Make sure that selinux.h is included first in order not to depend on the order
# in which "#include <selinux/selinux.h>" appears in other files.
FILE_LIST=(
    "${LIBSELINUX_SRC}/../include/selinux/selinux.h"
    "${LIBSELINUX_SRC}/../include/selinux/avc.h"
    "${LIBSELINUX_SRC}/../include/selinux/context.h"
    "${LIBSELINUX_SRC}/../include/selinux/get_context_list.h"
    "${LIBSELINUX_SRC}/../include/selinux/get_default_type.h"
    "${LIBSELINUX_SRC}/../include/selinux/label.h"
    "${LIBSELINUX_SRC}/../include/selinux/restorecon.h"
)
if ! cat "${FILE_LIST[@]}" | ${CC:-gcc} -x c -c -I"${LIBSELINUX_SRC}/../include" -o libselinux.temp.o - -aux-info libselinux.temp.aux
then
    # clang does not support -aux-info so fall back to gcc
    cat "${FILE_LIST[@]}" | gcc -x c -c -I"${LIBSELINUX_SRC}/../include" -o libselinux.temp.o - -aux-info libselinux.temp.aux
fi
for i in `awk '/<stdin>.*extern int/ { print $6 }' libselinux.temp.aux`; do except $i ; done
rm -f -- libselinux.temp.aux libselinux.temp.o
