#!/bin/sh

set -eu

mkdir -p "${WORKDIR}/policies/test-downgrade"

${CHECKPOLICY} -M "${WORKDIR}/refpolicy-base.conf" -o "${WORKDIR}/policies/test-downgrade/policy.hi"
