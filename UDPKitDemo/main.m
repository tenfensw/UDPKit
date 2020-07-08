//
//  main.m
//  UDPKitDemo
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UDPKit/UDPKit.h>

static const NSUInteger k_serverPort = 7078;

int main(void) {
    UDPServer* server = [UDPServer serverWithPort:k_serverPort];
    NSLog(@"Will start UDP server on port %lu", k_serverPort);
    [server synchroniouslyAcceptRequestsWithCallback:^NSData* _Nullable(UDPClientRequest* request) {
        NSLog(@"Received request from %@: %@", [request ipAddress], [request stringData]);
        NSString* response = [NSString stringWithFormat:@"[%@] %@", [request ipAddress], [request stringData]];
        NSData* responseData = [response dataUsingEncoding:NSUTF8StringEncoding];
        return responseData;
    }];
    return 0;
}
