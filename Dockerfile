FROM ubuntu
RUN apt update && apt install -y clang 
WORKDIR /ocean
COPY . .
RUN clang example/collatz.c ocean/ocean.c -o collatz
EXPOSE 1337
CMD ./collatz
