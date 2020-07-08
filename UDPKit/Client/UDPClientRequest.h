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

/*! @brief Class representing UDP client request. Usually generated either when sending requests through UDPClient or when processing incoming connections through UDPServer. */
@interface UDPClientRequest : NSObject
/*! @brief Read-only property containing an instance of <em>sockaddr_in</em> structure which represents basic information about the client (the IP address of the client, the port, etc). */
@property (readonly) SA_IN bsdOwner;
/*! @brief Property containing the request data. */
@property NSData* data;
/*! @brief Read-only property containing an instance of NSDate which represents the timestamp when the request was generated or received. */
@property (readonly) NSDate* timestamp;

/*!
@brief Initializes a new UDP client request with the specified non-nil data.
@param owner A valid instance of <em>sockaddr_in</em> structure containing basic information about the client.
@param data Non-nil and non-zero NSData instance containing the request data.
@return id A valid instance of UDPClientRequest.
*/
- (id)initWithOwner:(SA_IN)owner data:(NSData* _Nonnull)data;

/*!
@brief Initializes a new UDP client request with the specified non-nil data.
@param owner A valid instance of <em>sockaddr_in</em> structure containing basic information about the client.
@param data Non-nil and non-zero NSData instance containing the request data.
@return id A valid instance of UDPClientRequest.
*/
+ (id)requestWithOwner:(SA_IN)owner data:(NSData* _Nonnull)data;

/*!
@brief Converts the raw request data into a string with the specified encoding.
@discussion This method is a convenience wrapper to speed up code writing. It might return <b>nil</b> in cases when the input raw data cannot be encoded into a string.
@param enc The encoding of the raw data.
@return NSString* A valid instance of NSString with the converted request contents or <b>nil</b>.
*/
- (NSString* _Nullable)stringDataWithEncoding:(NSStringEncoding)enc;

/*!
@brief Converts the raw request data into a UTF-8 string.
@discussion This method is a convenience wrapper to speed up code writing. It might return <b>nil</b> in cases when the input raw data cannot be encoded into a Unicode string.
@return NSString* A valid instance of NSString with the converted request contents or <b>nil</b>.
*/
- (NSString* _Nullable)stringData;

/*! @brief Read-only property that returns the stringified form of the client's IP address. */
- (NSString*)ipAddress;
@end

NS_ASSUME_NONNULL_END

#endif
