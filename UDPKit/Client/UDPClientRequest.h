//
//  UDPClientRequest.h
//  UDPKit
//
//  Created by Tim K on 08/07/2020.
//  Copyright © 2020 Tim K. All rights reserved.
//

#ifndef UDPKit_Header_UDPClientRequest
#define UDPKit_Header_UDPClientRequest

#import <Foundation/Foundation.h>
#import <UDPKit/BSDSocketsPublicAbstraction.h>

NS_ASSUME_NONNULL_BEGIN

@interface UDPClientRequest : NSObject
@property (readonly) SA_IN bsdOwner;
@property NSData* data;
@property (readonly) NSDate* timestamp;
- (id)initWithOwner:(SA_IN)owner data:(NSData* _Nonnull)data;
+ (id)requestWithOwner:(SA_IN)owner data:(NSData* _Nonnull)data;
- (NSString* _Nullable)stringDataWithEncoding:(NSStringEncoding)enc;
- (NSString* _Nullable)stringData;
- (NSString*)ipAddress;
@end

NS_ASSUME_NONNULL_END

#endif
