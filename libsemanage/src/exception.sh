#!/bin/bash

function except() {
echo "
%exception $1 {
  \$action
  if (result < 0) {
     PyErr_SetFromErrno(PyExc_OSError);
     SWIG_fail;
  }
}"
}
if ! ${CC:-gcc} -x c -c -I"${LIBSEMANAGE_SRC}/../include" -o libsemanage.temp.o - -aux-info libsemanage.temp.aux < "${LIBSEMANAGE_SRC}/../include/semanage/semanage.h"
then
    # clang does not support -aux-info so fall back to gcc
    gcc -x c -c -I"${LIBSEMANAGE_SRC}/../include" -o libsemanage.temp.o - -aux-info libsemanage.temp.aux < "${LIBSEMANAGE_SRC}/../include/semanage/semanage.h"
fi
for i in `awk '/extern int/ { print $6 }' libsemanage.temp.aux`; do except $i ; done
rm -f -- libsemanage.temp.aux libsemanage.temp.o
