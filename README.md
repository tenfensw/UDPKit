# UDPKit

*A tiny Objective-C framework for building UDP servers and clients embedded into applications*

***Copyright (C) Tim K/RoverAMD <timprogrammer@rambler.ru> 2020.*** Licensed under 2-clause BSD License

## What is UDPKit?

UDPKit is a fairly tiny Objective-C framework that wraps around POSIX BSD sockets API in a (probably) convenient object-oriented layer that allows to build UDP servers and clients that are embedded into your Cocoa application.

## UDPKit Example

Check out [main.m](UDPKitDemo/main.m) file inside the *UDPKitDemo* folder which implements a minimalistic echo UDP server in just ~8-10 lines of code.

## Building UDPKit

UDPKit is meant to be built as a framework included in other applications. The respective Xcode projects for macOS (*UDPKit.xcodeproj*) and iOS/iPadOS (not ready yet, but soon will be *UDPKit_iOS.xcodeproj*) can be added to your Xcode workspace so that the framework could be compiled and distributed in your application without any additional steps.

However, of course you may build UDPKit framework entirely standalone either via Xcode or ``xcodebuild``, just like you would do with any other Xcode project. Building a standalone version might be quite handy if you don't use Xcode workspaces.

## Limitations

Currently, UDPKit does not support IPv6 (while its preliminary wrapper does support UDP server socket creation for IPv6, client creation and well... the classes themselves are not ready).

UDPKit can build on iOS, however, the project file is currently not added to the source repository.

## Documentation

Well... for now, there is none. :P But there will be at least a brief introduction when the first release of the framework gets ready.

## License

UDPKit uses a 2-clause BSD License. Consult the [LICENSE](LICENSE) file for further information.
