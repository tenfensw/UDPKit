//
//  UDPServer.h
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#ifndef UDPKit_Header_UDPServer
#define UDPKit_Header_UDPServer

#import <Foundation/Foundation.h>
#import <UDPKit/BSDSocketsPublicAbstraction.h>
#import <UDPKit/UDPClientRequest.h>

typedef NSData* _Nullable(^UDPServerCallback)(UDPClientRequest* _Nonnull);

NS_ASSUME_NONNULL_BEGIN

@interface UDPServer : NSObject
@property (readonly) int bsdSocket;
@property (readonly) SA_IN bsdSocketAddress;
@property (readonly) NSString* ipAddress;
@property (readonly) NSUInteger port;
@property NSUInteger maxDataSize;
@property BOOL needAcceptRequests;
- (id)initWithPort:(NSUInteger)port;
- (id)initWithIPv4Address:(NSString* _Nullable)ipAddress port:(NSUInteger)port;
+ (id)serverWithPort:(NSUInteger)port;
+ (id)serverWithIPv4Address:(NSString* _Nullable)ipAddress port:(NSUInteger)port;
- (UDPClientRequest* _Nullable)waitForRequest;
- (void)synchroniouslyAcceptRequestsWithCallback:(UDPServerCallback)callback;
- (void)asynchroniouslyAcceptRequestsWithCallback:(UDPServerCallback)callback;
- (void)sendData:(NSData*)dt target:(SA_IN)who;
- (void)dealloc;
@end

NS_ASSUME_NONNULL_END

#endif
