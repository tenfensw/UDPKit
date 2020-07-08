//
//  UDPClientRequest.m
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#import "UDPClientRequest.h"
#import "BSDSockets.h"

@implementation UDPClientRequest

- (id)initWithOwner:(SA_IN)owner data:(NSData *)data {
    if (self = [super init]) {
        _bsdOwner = owner;
        _data = data;
        _timestamp = [[NSDate alloc] init];
    }
    return self;
}

+ (id)requestWithOwner:(SA_IN)owner data:(NSData *)data {
    return [[UDPClientRequest alloc] initWithOwner:owner data:data];
}

- (NSString*)stringData {
    return [self stringDataWithEncoding:NSUTF8StringEncoding];
}

- (NSString*)stringDataWithEncoding:(NSStringEncoding)enc {
    return [[NSString alloc] initWithData:_data encoding:enc];
}

- (NSString*)ipAddress {
    char* dest = calloc(INET_ADDRSTRLEN, sizeof(char));
    inet_ntop(AF_INET, &_bsdOwner.sin_addr, dest, INET_ADDRSTRLEN);
    NSString* result = [[NSString alloc] initWithCString:dest encoding:NSUTF8StringEncoding];
    free(dest);
    return result;
}

@end
