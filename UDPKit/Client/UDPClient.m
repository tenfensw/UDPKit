//
//  UDPClient.m
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#import "UDPClient.h"
#import "BSDSockets.h"

@implementation UDPClient

- (id)initLocalWithPort:(NSUInteger)port {
    self = [self initWithIPv4Address:@"127.0.0.1" port:port];
    return self;
}

- (id)initWithIPv4Address:(NSString *)address port:(NSUInteger)port {
    if (self = [super init]) {
        _ipAddress = address;
        if (!address)
            _ipAddress = @"127.0.0.1";
        _port = port;
        _maxDataSize = UDPKit_DefaultMaxDataSize;
        _bsdSocketAddress = UDPMakeSA(_ipAddress, _port);
        _bsdSocket = UDPMakeClientSocket(&_bsdSocketAddress);
        if (_bsdSocket == -1) {
            @throw [[NSException alloc] initWithName:@"BSDSocketConnectErrno" reason:UDPSerializeErrno() userInfo:nil];
            return nil;
        }
    }
    return self;
}

- (NSData*)receiveData {
    char* buf = calloc(_maxDataSize, sizeof(char));
    int bytesReceived = recv(_bsdSocket, buf, _maxDataSize, MSG_WAITALL);
    if (bytesReceived < 1) {
        free(buf);
        return nil;
    }
    NSData* data = [[NSData alloc] initWithBytes:buf length:bytesReceived];
    free(buf);
    return data;
}

- (void)sendRequest:(UDPClientRequest *)rq {
    NSData* rawData = [rq data];
    char* buf = calloc([rawData length] + 1, sizeof(char));
    [rawData getBytes:buf length:[rawData length]];
    int result = send(_bsdSocket, buf, [rawData length], 0);
    free(buf);
    if (result == -1)
        @throw [[NSException alloc] initWithName:@"UDPSendErrno" reason:UDPSerializeErrno() userInfo:nil];
}

- (void)sendData:(NSData *)data {
    UDPClientRequest* rq = [[UDPClientRequest alloc] initWithOwner:_bsdSocketAddress data:data];
    [self sendRequest:rq];
}

- (NSData*)receiveDataAfterSendingRequest:(UDPClientRequest *)rq {
    [self sendRequest:rq];
    return [self receiveData];
}

- (NSData*)receiveDataAfterSendingData:(NSData *)data {
    [self sendData:data];
    return [self receiveData];
}

- (void)dealloc {
    close(_bsdSocket);
}

+ (id)localClientWithPort:(NSUInteger)port {
    return [[UDPClient alloc] initLocalWithPort:port];
}

+ (id)clientWithIPv4Address:(NSString *)address port:(NSUInteger)port {
    return [[UDPClient alloc] initWithIPv4Address:address port:port];
}

@end
