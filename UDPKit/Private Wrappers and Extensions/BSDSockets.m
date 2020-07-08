//
//  BSDSockets.m
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#import "BSDSockets.h"

SA_IN UDPMakeSA(NSString* _Nullable preferredIPAddress, const NSUInteger port) {
    SA_IN addr;
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    if (!preferredIPAddress)
        addr.sin_addr.s_addr = INADDR_ANY;
    else
        inet_pton(AF_INET, [preferredIPAddress UTF8String], &addr.sin_addr);
    return addr;
}

SA_INv6 UDPMakeSAv6(NSString* _Nullable preferredIPAddress, const NSUInteger port) {
    SA_INv6 addr;
    bzero(&addr, sizeof(addr));
    addr.sin6_len = sizeof(addr);
    addr.sin6_family = AF_INET6;
    addr.sin6_flowinfo = 0;
    addr.sin6_port = htons(port);
    if (preferredIPAddress)
        inet_pton(AF_INET6, [preferredIPAddress UTF8String], &addr.sin6_addr);
    else
        addr.sin6_addr = in6addr_any;
    return addr;
}

int UDPMakeSocket(SA_IN* _Nonnull socketAddress) {
    int desc = socket(PF_INET, SOCK_DGRAM, 0);
    if (desc == -1)
        return -1;
    if (bind(desc, (SA*)socketAddress, sizeof(*socketAddress)) == -1) {
        close(desc);
        return -1;
    }
    return desc;
}

int UDPMakeSocketv6(SA_INv6* _Nonnull socketAddress6) {
    int desc = socket(PF_INET6, SOCK_DGRAM, 0);
    if (desc == -1)
        return -1;
    if (bind(desc, (SA*)(socketAddress6), sizeof(*socketAddress6)) == -1) {
        close(desc);
        return -1;
    }
    return desc;
}

NSString* _Nullable UDPSerializeErrno() {
    char* stringForErrno = strerror(errno);
    if (!stringForErrno)
        return nil;
    return [[NSString alloc] initWithCString:stringForErrno encoding:NSUTF8StringEncoding];
}

int UDPMakeClientSocket(SA_IN* _Nonnull socketAddress) {
    int desc = socket(PF_INET, SOCK_DGRAM, 0);
    if (desc == -1)
        return -1;
    if (connect(desc, (SA*)(&socketAddress), sizeof(*socketAddress)) == -1) {
        close(desc);
        return -1;
    }
    return desc;
}
