#!/usr/bin/env bash

if ! type "genpac" > /dev/null; then
		pip install --upgrade pip
		pip install genpac
fi

genpac --proxy="SOCKS5 127.0.0.1:1080" \
		--gfwlist-proxy="SOCKS5 127.0.0.1:1080" \
		-o autoproxy.pac \
		--gfwlist-url="https://raw.githubusercontent.com/gfwlist/gfwlist/master/gfwlist.txt" \
		--compress

