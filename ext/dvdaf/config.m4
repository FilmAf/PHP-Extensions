PHP_ARG_ENABLE(dvdaf, whether to enable dvdaf support,
[  --enable-dvdaf           Enable dvdaf support])

if test "$PHP_DVDAF" != "no"; then
  PHP_NEW_EXTENSION(dvdaf, dvdaf.c dstring.c field.c format.c ipc.c search.c template.c utils.c vsql.c vstring.c, $ext_shared)
fi

