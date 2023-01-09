FROM ubuntu
RUN apt update && apt install -y clang 
WORKDIR /ocean
COPY . .
EXPOSE 1337
CMD clang example/collatz.c ocean/ocean.c -o collatz && ./collatz
