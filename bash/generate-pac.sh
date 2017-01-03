#!/usr/bin/env bash

genpac --proxy="SOCKS5 127.0.0.1:1080" \
		--gfwlist-proxy="SOCKS5 127.0.0.1:1080" \
		-o autoproxy.pac \
		--gfwlist-url="https://raw.githubusercontent.com/gfwlist/gfwlist/master/gfwlist.txt" \
		--compress

