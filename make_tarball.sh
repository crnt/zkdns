#!/bin/sh

DATE=${1:-$(date +%Y%m%d)}
REVISION=${2:-HEAD}

ORIGINAL_REVISION=$(git rev-parse HEAD)

VERSION="${DATE}+$(git rev-parse ${REVISION})"

git archive --format=tar --prefix=scribe-${VERSION}/ ${REVISION} | gzip -9 > zkdns-${VERSION}.tar.gz

echo "Created zkdns-${VERSION}.tar.gz"
