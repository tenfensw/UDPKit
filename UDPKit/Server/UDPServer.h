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
/// @brief Read-only property containing the socket descriptor that can be referenced from C methods that can work with socket descriptors directly.
@property (readonly) int bsdSocket;

/// @brief Read-only property containing the IPv4 sockaddr_in structure.
@property (readonly) SA_IN bsdSocketAddress;

/// @brief Read-only property containing the server IP address.
@property (readonly) NSString* ipAddress;

/// @brief Read-only property containing the port number.
@property (readonly) NSUInteger port;

/// @brief Property containing the maximum transferred and incoming data size. This value should be consistent with the value on the client-size to prevent buffer overflows.
@property NSUInteger maxDataSize;

/// @brief Property controlling the server when it is running in asynchronious mode.
/// @discussion When the <em>asynchroniouslyAcceptRequestsWithCallback:</em> method is called, this property is automatically set to <b>YES</b>. When set to <b>NO</b>, the async run loop of the server stops.
@property BOOL needAcceptRequests;

/*!
@brief Initializes a new UDP server listening for connections on the specified port.
@discussion By default, when an instance of UDPServer is constructed this way, the resulting server will be listening on the local interface by default (on IP 127.0.0.1).
@param port The port number.
@return id A new valid instance of UDPServer.
*/
- (id)initWithPort:(NSUInteger)port;

/*!
@brief Initializes a new UDP server listening for connections on the specified port and IP address.
@discussion When the <i>ipAddress</i> is set to <b>nil</b>, the resulting server starts listening on the local interface (on IP 127.0.0.1).
@param ipAddress The IP address or <b>nil</b>.
@param port The port number.
@return id A new valid instance of UDPServer.
*/
- (id)initWithIPv4Address:(NSString* _Nullable)ipAddress port:(NSUInteger)port;

/*!
@brief Initializes a new UDP server listening for connections on the specified port.
@discussion By default, when an instance of UDPServer is constructed this way, the resulting server will be listening on the local interface by default (on IP 127.0.0.1).
@param port The port number.
@return id A new valid instance of UDPServer.
*/
+ (id)serverWithPort:(NSUInteger)port;

/*!
@brief Initializes a new UDP server listening for connections on the specified port and IP address.
@discussion When the <i>ipAddress</i> is set to <b>nil</b>, the resulting server starts listening on the local interface (on IP 127.0.0.1).
@param ipAddress The IP address or <b>nil</b>.
@param port The port number.
@return id A new valid instance of UDPServer.
*/
+ (id)serverWithIPv4Address:(NSString* _Nullable)ipAddress port:(NSUInteger)port;

/*!
@brief Single-shot method that waits for the first client connection and processes it.
@discussion This method will block the thread and wait for the first client connection with a valid request and then processes that request into a UDPClientRequest instance. If an error occurs, <b>nil</b> is returned.
@return id The client request represented as an instance of UDPClientRequest or <b>nil</b>.
*/
- (UDPClientRequest* _Nullable)waitForRequest;

/*!
@brief Continuous run loop that listens for client connections, processes them and responds to them.
@discussion After the connection is processed into an instance of UDPClientRequest, the specified callback block is called. That block may return <b>nil</b> if no response is assumed from the server or a non-zero instance of NSData if a response needs to be sent.
*/
- (void)synchroniouslyAcceptRequestsWithCallback:(UDPServerCallback)callback;

/*!
@brief Continuous run loop that listens for client connections, processes them and responds to them (asynchronous).
@discussion After the connection is processed into an instance of UDPClientRequest, the specified callback block is called. That block may return <b>nil</b> if no response is assumed from the server or a non-zero instance of NSData if a response needs to be sent.

         @code
         UDPServer* server = [UDPServer serverWithPort:7070];
         [server asynchroniouslyAcceptRequestsWithCallback:^NSData* _Nullable (UDPClientRequest* request) {
            NSLog(@"Request from %@: %@", [request ipAddress], [request stringData]);
            NSString* reversedString = [[request stringData] lowercaseString];
            return [reversedString dataUsingEncoding:NSUTF8StringEncoding];
         }];
         @endcode
The run loop can be controlled via the <em>needAcceptRequests</em> property. A simple @c[server setNeedAcceptRequests:NO] will stop the run loop right after it finishes processing the last received request.
@param callback An non-nil Objective-C block returning nil or a valid instance of NSData that will be called on each received request from clients.
*/
- (void)asynchroniouslyAcceptRequestsWithCallback:(UDPServerCallback)callback;

/*!
@brief Sends a response packet with the specified non-nil data directly to the specified connected client.
@discussion This method is automatically called when in a continuous run loop and the only reason to call it manually is when the connection handling is done manually.
        @code
        UDPServer* server = [UDPServer serverWithPort:7070];
        UDPClientRequest* firstRequest = [server waitForRequest];
        if (firstRequest)
         [server sendData:[@"GOODBYE" dataUsingEncoding:NSUTF8StringEncoding] target:[firstRequest bsdOwner]];
        @endcode
@param dt Non-nil and non-zero data to be sent.
@param who <em>sockaddr_in</em> structure instance containing the information about the client.
*/
- (void)sendData:(NSData*)dt target:(SA_IN)who;
- (void)dealloc;
@end

NS_ASSUME_NONNULL_END

#endif
