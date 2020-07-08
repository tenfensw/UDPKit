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

/*! @brief IPv4 UDP client */
@interface UDPClient : NSObject
/*! @brief Read-only property containing the socket descriptor that can be referenced from C methods that can work with socket descriptors directly. */
@property (readonly) int bsdSocket;

/*! @brief Read-only property containing the IPv4 sockaddr_in structure. */
@property (readonly) SA_IN bsdSocketAddress;

/*! @brief Read-only property containing the target IP address. */
@property (readonly) NSString* ipAddress;

/*! @brief Read-only property containing the port number. */
@property (readonly) NSUInteger port;

/*! @brief Property containing the maximum transferred and incoming data size. This value should be consistent with the value on the server-size to prevent buffer overflows. */
@property NSUInteger maxDataSize;

/*!
@brief Initializes a new instance of UDPClient class that connects to a IPv4 UDP server with the specified IP address and port.
@discussion When the <em>address</em> parameter is set to <b>nil</b>, the resulting UDPClient instance will attempt to connect to a locally running UDP server.
@param address The IP address (not a <b>domain</b>) of the target UDP server.
@param port The port number of the target UDP server.
@return id Returns a new instance of UDPClient.
*/
- (id)initWithIPv4Address:(NSString* _Nullable)address port:(NSUInteger)port;

/*!
@brief Initializes a new instance of UDPClient class that connects to a local IPv4 UDP server with the port.
@discussion This is a convenience wrapper and nothing else. Direct equivalent would be @c[UDPClient clientWithIPv4Address:nil port:port]
@param port The port number of the local UDP server.
@return id Returns a new instance of UDPClient.
*/
- (id)initLocalWithPort:(NSUInteger)port;

/*!
@brief Initializes a new instance of UDPClient class that connects to a IPv4 UDP server with the specified IP address and port.
@discussion When the <em>address</em> parameter is set to <b>nil</b>, the resulting UDPClient instance will attempt to connect to a locally running UDP server.
@param address The IP address (not a <b>domain</b>) of the target UDP server.
@param port The port number of the target UDP server.
@return id Returns a new instance of UDPClient.
*/
+ (id)clientWithIPv4Address:(NSString* _Nullable)address port:(NSUInteger)port;

/*!
@brief Initializes a new instance of UDPClient class that connects to a local IPv4 UDP server with the port.
@discussion This is a convenience wrapper and nothing else. Direct equivalent would be @c[UDPClient clientWithIPv4Address:nil port:port]
@param port The port number of the local UDP server.
@return id Returns a new instance of UDPClient.
*/
+ (id)localClientWithPort:(NSUInteger)port;

/*!
@brief Attempts to receive data from the remote UDP server.
@discussion nil or 0-byte data is treated as abscence of responce from the remote host and, as such, <b>nil</b> is returned.
@return NSData* The raw response from the remote UDP server.
*/
- (NSData* _Nullable)receiveData;

/*!
@brief Sends a UDP packet to the remote server with the specified data.
@param data The contents of the sent packet. Must be not <b>nil</b>.
*/
- (void)sendData:(NSData*)data;

/*!
@brief Sends a UDP packet to the remote server represented as a UDPClientRequest.
@param rq A valid instance of UDPClientRequest containing non-nil data. Must be not <b>nil</b>.
*/
- (void)sendRequest:(UDPClientRequest*)rq;

/*!
@brief A convenience wrapper that sends a request and right after that receives the response from the server.
@discussion This method was made to speed up the coding process and is an equivalent to:
<pre>@textblock
            [client sendRequest:rq];
            NSData* matchingData = [client receiveData];
@/textblock </pre>
@param rq A valid instance of UDPClientRequest containing non-nil data and representing the sent request. Must be not <b>nil</b>.
@return NSData* The raw response from the remote UDP server.
*/
- (NSData* _Nullable)receiveDataAfterSendingRequest:(UDPClientRequest*)rq;

/*!
@brief A convenience wrapper that sends a request and right after that receives the response from the server.
@discussion This method was made to speed up the coding process and is an equivalent to:
<pre>@textblock
            [client sendData:data];
            NSData* matchingData = [client receiveData];
@/textblock </pre>
@param data The contents of the sent packet. Must be not <b>nil</b>.
@return NSData* The raw response from the remote UDP server.
*/
- (NSData* _Nullable)receiveDataAfterSendingData:(NSData*)data;
- (void)dealloc;
@end

NS_ASSUME_NONNULL_END

#endif
