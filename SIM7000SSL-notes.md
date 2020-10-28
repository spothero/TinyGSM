# SIM7000 SSL version dev notes

These are just notes used while writing the SIM7000 SSL version. This file shouldn't make its way into the main repo...

## AT commands

Some commands I tried, not really working yet.

### Connecting to the network

```
at+cnact=1,"dr.m2m.ch"
at+cnact?
```

### Setup TCP and SSL

```
at+cacid=0
at+casslcfg=0,"ssl",1
at+csslcfg="sslversion",0,3
```

### Getting a file

Trying to get this small text file: https://eende.net/test.txt.
It should work if using SSL. When this file is accessed using plain http, a "301 Moved Permanently" error is returned by the server.

The value "10000" means that the timeout for entering the GET request is 10s. It might be that the kind of line ending is important.

```
at+caopen=0,"eende.net",443
AT+CASEND=0,66,10000
GET /test.txt HTTP/1.0
Host: eende.net
Connection: close



```
