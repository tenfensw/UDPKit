//
//  UDPServer.m
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#import "UDPServer.h"
#import "BSDSockets.h"

@implementation UDPServer

- (id)initWithPort:(NSUInteger)port {
    self = [self initWithIPv4Address:@"127.0.0.1" port:port];
    return self;
}

- (id)initWithIPv4Address:(NSString *)ipAddress port:(NSUInteger)port {
    if (self = [super init]) {
        _port = port;
        _ipAddress = ipAddress;
        _maxDataSize = UDPKit_DefaultMaxDataSize;
        if (!ipAddress)
            _ipAddress = @"127.0.0.1";
        _bsdSocketAddress = UDPMakeSA(_ipAddress, port);
        _bsdSocket = UDPMakeSocket(&_bsdSocketAddress);
        _needAcceptRequests = NO;
        if (_bsdSocket == -1) {
            @throw [[NSException alloc] initWithName:@"UDPSocketErrno" reason:UDPSerializeErrno() userInfo:nil];
            return nil;
        }
    }
    return self;
}

- (UDPClientRequest*)waitForRequest {
    SA_IN owner;
    bzero(&owner, sizeof(owner));
    socklen_t ownerLength = sizeof(owner);
    char* buf = calloc(_maxDataSize, sizeof(char));
    int byteSize = recvfrom(_bsdSocket, buf, _maxDataSize, MSG_WAITALL, (SA*)&owner, &ownerLength);
    if (byteSize < 1) {
        free(buf);
        return nil;
    }
    NSData* data = [[NSData alloc] initWithBytes:buf length:byteSize];
    UDPClientRequest* clientRequest = [[UDPClientRequest alloc] initWithOwner:owner data:data];
    free(buf);
    return clientRequest;
}

- (void)asynchroniouslyAcceptRequestsWithCallback:(UDPServerCallback)callback {
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_BACKGROUND, 0), ^{
        [self synchroniouslyAcceptRequestsWithCallback:callback];
    });
}

- (void)synchroniouslyAcceptRequestsWithCallback:(UDPServerCallback)callback {
    _needAcceptRequests = YES;
    UDPClientRequest* request = nil;
    while (_needAcceptRequests) {
        request = [self waitForRequest];
        if (request) {
            NSData* dataToSend = callback(request);
            if (dataToSend)
                [self sendData:dataToSend target:[request bsdOwner]];
        }
    }
}

- (void)sendData:(NSData *)dt target:(SA_IN)who {
    char* dataBuf = calloc([dt length] + 1, sizeof(char));
    [dt getBytes:dataBuf length:[dt length]];
    if (sendto(_bsdSocket, dataBuf, [dt length], 0, (SA*)&who, sizeof(who)) == -1) {
        free(dataBuf);
        @throw [[NSException alloc] initWithName:@"UDPSendSocketErrno" reason:UDPSerializeErrno() userInfo:nil];
    }
    free(dataBuf);
}

- (void)dealloc {
    _needAcceptRequests = NO;
    close(_bsdSocket);
}

+ (id)serverWithPort:(NSUInteger)port {
    return [[UDPServer alloc] initWithPort:port];
}

+ (id)serverWithIPv4Address:(NSString *)ipAddress port:(NSUInteger)port {
    return [[UDPServer alloc] initWithIPv4Address:ipAddress port:port];
}

@end
