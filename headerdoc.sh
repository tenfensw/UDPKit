#!/bin/sh -e
docfiles="UDPKit/Server/UDPServer.h UDPKit/Client/UDPClient.h UDPKit/Client/UDPClientRequest.h"
test -d docs && rm -rfv docs
mkdir -v docs
headerdoc2html -o docs $docfiles
gatherheaderdoc docs
exit 0
