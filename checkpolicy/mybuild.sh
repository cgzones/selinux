#!/bin/sh

set -e

if [ "$1x" = "cleanx" ]; then
	make -C ../libsepol/src/ clean
	make clean

	exit 0
fi

CC=${CC:-'ccache clang-12'}
CFLAGS=${CFLAGS:-'-fsanitize=fuzzer -O1 -g -fsanitize=address -fsanitize-address-use-after-scope -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=nullability -fsanitize=implicit-conversion -fsanitize=integer -fsanitize=float-divide-by-zero -fsanitize=local-bounds'}

make -C ../libsepol/src/ CC="$CC" CFLAGS="$CFLAGS -Werror -Wall -Wdeclaration-after-statement -Wextra -Wfloat-equal -Wformat -Winit-self -Wmissing-format-attribute -Wmissing-noreturn -Wnull-dereference -Wpointer-arith -Wshadow -Wstrict-prototypes -Wundef -Wunused -Wwrite-strings" libsepol.a -j4

make clean
make CC="$CC" CFLAGS="-DFUZZING_BUILD_MODE_UNSAFE_FOR_PRODUCTION $CFLAGS -Werror -Wall -Wcast-qual -Wdeclaration-after-statement -Wextra -Wfloat-equal -Wformat=2 -Winit-self -Wmissing-format-attribute -Wmissing-noreturn -Wmissing-prototypes -Wnull-dereference -Wpointer-arith -Wshadow -Wstrict-prototypes -Wundef -Wunused -Wwrite-strings -isystem $(pwd)/../libsepol/include/" LIBSEPOLA="$(pwd)/../libsepol/src/libsepol.a" checkmodule-fuzzer
