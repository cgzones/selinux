#!/bin/sh

set -eu

POL_VERS=$(${CHECKPOLICY} -V | cut -f 1 -d ' ')

echo "[-] checkpolicy:"
echo ${CHECKPOLICY}
echo "[-] checkpolicy max supported policy version:"
echo ${POL_VERS}
echo "[-] secilc (check for default value of option --policyvers):"
command -v secilc
echo "[-] secilc help:"
secilc --help || true
echo "[-] LD_LIBRARY_PATH:"
echo ${LD_LIBRARY_PATH}
echo "[-] PATH:"
echo ${PATH}

echo "[-] step 1"
secilc policy.cil
echo "[-] step 2"
secilc -c "${POL_VERS}" -O -M 1 -f /dev/null -o opt-actual.bin opt-input.cil
echo "[-] step 3"
checkpolicy -b -C -M -o opt-actual.cil opt-actual.bin >/dev/null
echo "[-] step 4"
diff opt-expected.cil opt-actual.cil
