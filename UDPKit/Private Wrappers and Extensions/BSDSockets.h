//
//  BSDSockets.h
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#ifndef UDPKit_Header_BSDSocketsWrapper
#define UDPKit_Header_BSDSocketsWrapper

#import <Foundation/Foundation.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

static const unsigned UDPKit_DefaultMaxDataSize = 6148;

typedef struct sockaddr SA;
typedef struct sockaddr_in SA_IN;
typedef struct sockaddr_in6 SA_INv6;

SA_IN UDPMakeSA(NSString* _Nullable preferredIPAddress, const NSUInteger port);
SA_INv6 UDPMakeSAv6(NSString* _Nullable preferredIPAddress, const NSUInteger port);

int UDPMakeSocket(SA_IN* _Nonnull socketAddress);
int UDPMakeSocketv6(SA_INv6* _Nonnull socketAddress6);

int UDPMakeClientSocket(SA_IN* _Nonnull socketAddress);

NSString* _Nullable UDPSerializeErrno(void);

#endif /* UDPKit_Header_BSDSocketsWrapper */
