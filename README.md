## Demo

**Server side**

*Using Docker*
```
$ docker build . -t ocean_srv

$ docker run -p 1337:1337 -it ocean_srv

```

*On Host*
```
$ clang example/collatz.c ocean/ocean.c -o collatz && ./collatz
```

**Client Side**

```
$ clang example/client.c ocean/ocean.c -o client && ./client #Insert number here (default: 10)
```
