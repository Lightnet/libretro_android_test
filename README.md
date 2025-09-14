


```
termux-setup-storage
```
access storage


```
chmod +x build.sh
```

```
cp test_lib.so ~/storage/shared/Download
```

```
cp build/test_lib.so ~/storage/shared/retroarch/downloads
```

# ftp

## Install Required Packages:
```
pkg update
pkg install busybox termux-services
```

## Enable and Start the Service:
```
sv-enable ftpd
sv up ftpd
```

## Verify It's Running:
```
sv status ftpd
```


## Stop the Server
```
sv down ftpd
```

