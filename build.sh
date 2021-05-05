#!/bin/sh

set -e

if [ "$1x" = "cleanx" ]; then
	make -C libsepol/src/ clean
	make -C secilc/ clean

	exit 0
fi

CC=${CC:-'ccache clang-12'}
CFLAGS=${CFLAGS:-'-O1 -g -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=nullability -fsanitize=implicit-conversion -fsanitize=integer -fsanitize=float-divide-by-zero -fsanitize=local-bounds'}

make -C libsepol/src/ CC="$CC" CFLAGS="$CFLAGS -Werror -Wall -Wdeclaration-after-statement -Wextra -Wfloat-equal -Wformat -Winit-self -Wmissing-format-attribute -Wmissing-noreturn -Wmissing-prototypes -Wnull-dereference -Wpointer-arith -Wshadow -Wstrict-prototypes -Wundef -Wunused -Wwrite-strings" -j4 libsepol.a

make -C secilc/ clean
make -C secilc/ CC="$CC" CFLAGS="$CFLAGS -Werror -Wall -Wcast-align -Wcast-qual -Wdeclaration-after-statement -Wextra -Wfloat-equal -Wformat=2 -Winit-self -Wmissing-format-attribute -Wmissing-noreturn -Wmissing-prototypes -Wnull-dereference -Wpointer-arith -Wshadow -Wstrict-prototypes -Wundef -Wunused -Wwrite-strings -isystem ../libsepol/include/ -isystem ../libsepol/cil/include/ -DANDROID" LDLIBS="../libsepol/src/libsepol.a" -j4 secilc secil2conf secil2tree
