FROM alpine:3.17.0 AS build

RUN apk update && \
apk add --no-cache \ 
build-base \
cmake


WORKDIR /serverincontainer

COPY source/ ./source/
COPY headers/ ./headers/
COPY CMakeLists.txt .


RUN cat CMakeLists.txt

WORKDIR /serverincontainer/build

RUN cmake -DCMAKE_BUILD_TYPE=Release .. && \
    cmake --build . --parallel 8

FROM alpine:3.17.0

RUN apk update && \
apk add --no-cache \
libstdc++=12.2.1_git20220924-r4 


RUN addgroup -S userok && adduser -S userok -G userok
USER userok

COPY --chown=shs:shs --from=build \
    ./serverincontainer/build/source/http_server \
    ./app/
    
ENTRYPOINT [ "./app/http_server" ]