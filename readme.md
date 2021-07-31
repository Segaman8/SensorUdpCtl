@mainpage
@tableofcontents

# Description

**Sensor Udp Controller** (C) 2021 [**Segaman**](https://segaman.top/)

This project is a shared library.

It used to get sensors vector values ( see [Usage](#markdown-header-usage) ).

@ref Sensor::UdpCtl::init starts separate thread, where udp server runs.

Server will receive vectors from sensors and store it into map.

Created to use inside Unity 3D.

Unit tests provided for all functions.

Doxygen documentation can be compiled ( see [Documentation](#markdown-header-docs) ).

## Table of contents

@ref DataHelper

@ref Sensor::UdpCtl

@ref groupSensor

## Supported Platforms

- Linux

- Windows (not tested yet)

## Building

```
mkdir build
cd build
cmake ..
make
make test
```

<a id="markdown-header-usage"></a>
## Usage

- Execute @ref Sensor::UdpCtl::init

- Retreive sensors ids by executing @ref Sensor::UdpCtl::getKeys

- Then execute @ref Sensor::UdpCtl::getData for every id to retreive vector values

<a id="markdown-header-docs"></a>
## Documentation 

All documentation stored in "html" folder

If you don't have "html" folder:

1. Install "doxygen"

2. Launch "doxygen" inside root folder

3. Open "html/index.html" with your browser

!WARNING! NEVER ADD "html" INTO SOURCES!
