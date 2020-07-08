//
//  UDPClient.h
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#ifndef UDPKit_Header_UDPClient
#define UDPKit_Header_UDPClient

#import <Foundation/Foundation.h>
#import <UDPKit/BSDSocketsPublicAbstraction.h>
#import <UDPKit/UDPClientRequest.h>

NS_ASSUME_NONNULL_BEGIN

@interface UDPClient : NSObject
@property (readonly) int bsdSocket;
@property (readonly) SA_IN bsdSocketAddress;
@property (readonly) NSString* ipAddress;
@property (readonly) NSUInteger port;
@property NSUInteger maxDataSize;
- (id)initWithIPv4Address:(NSString* _Nullable)address port:(NSUInteger)port;
- (id)initLocalWithPort:(NSUInteger)port;
+ (id)clientWithIPv4Address:(NSString* _Nullable)address port:(NSUInteger)port;
+ (id)localClientWithPort:(NSUInteger)port;
- (NSData* _Nullable)receiveData;
- (void)sendData:(NSData*)data;
- (void)sendRequest:(UDPClientRequest*)rq;
- (NSData* _Nullable)receiveDataAfterSendingRequest:(UDPClientRequest*)rq;
- (NSData* _Nullable)receiveDataAfterSendingData:(NSData*)data;
- (void)dealloc;
@end

NS_ASSUME_NONNULL_END

#endif
