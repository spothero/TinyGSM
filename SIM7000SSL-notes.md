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

### Using the integrated HTTPS client

This will not be used in the TinyGSM implementation, but shows that there is hope for SSL to work.
```
at+cnact=1,"dr.m2m.ch"
at+cnact?
at+cacid=0
at+csslcfg="sslversion",0,3
at+casslcfg=0,ssl,1
at+shconf="BODYLEN",350
at+shconf="HEADERLEN",350
at+shconf="URL","https://eende.net:443"
at+shconn
at+shbod="FOOBAR",6
at+shreq="https://eende.net/test.txt",1 --> should return +SHREQ: "GET",200,65
at+shread=0,65
at+shdisc
```
