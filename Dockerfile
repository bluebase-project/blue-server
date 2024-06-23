FROM alpine:3.15.0 AS build
# crypto++-dev is in edge/testing
RUN apk add --no-cache --repository http://dl-cdn.alpinelinux.org/alpine/edge/testing/ \
  binutils \
  boost-dev \
  build-base \
  clang \
  cmake \
  crypto++-dev \
  fmt-dev \
  gcc \
  gmp-dev \
  luajit-dev \
  make \
  mariadb-connector-c-dev \
  pugixml-dev

COPY cmake /usr/src/blueserver/cmake/
COPY src /usr/src/blueserver/src/
COPY CMakeLists.txt /usr/src/blueserver/
WORKDIR /usr/src/blueserver/build
RUN cmake .. && make

FROM alpine:3.15.0
# crypto++ is in edge/testing
RUN apk add --no-cache --repository http://dl-cdn.alpinelinux.org/alpine/edge/testing/ \
  boost-iostreams \
  boost-system \
  boost-filesystem \
  crypto++ \
  fmt \
  gmp \
  luajit \
  mariadb-connector-c \
  pugixml

COPY --from=build /usr/src/blueserver/build/blueserver /bin/blueserver
COPY data /srv/data/
COPY LICENSE README.md *.dist *.sql key.pem /srv/

EXPOSE 7171 7172
WORKDIR /srv
VOLUME /srv
ENTRYPOINT ["/bin/blueserver"]
