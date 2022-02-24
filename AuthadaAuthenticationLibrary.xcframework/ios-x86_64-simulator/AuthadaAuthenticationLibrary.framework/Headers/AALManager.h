//
//  AALManager.h
//  AuthadaAuthenticationLibrary
//
//  Created by Samuel Florian Strupp on 24.06.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AALManagerDelegate.h"
#import "AALDemoConfigurations.h"

typedef enum : NSUInteger {
    AALMode_Unknown = 0,
    AALMode_Standard,
    AALMode_Demo
} AALMode;

NS_ASSUME_NONNULL_BEGIN

@interface AALManager : NSObject

/*!
@brief Get the shared AALManager instance.
@return Returns shared AALManager instance.
*/
+(AALManager*) sharedAALManager;

/*!
 @brief Remove the shared AALManager instance.
 @discussion Do not call this method until you have completed all actions with the AAL.
 */
+(void) removeSharedAALManager;

#pragma mark - Mode

/*!
 @brief Get the current defined AAL mode.
 @return Returns the current AALMode.
 */
-(AALMode) mode;

/*!
@brief Set the AALMode to "Standard".
@discussion In this mode the AALManager does not simulate anything.
@param  url defines the endpoint to work with.
@param  hashes defines allowed certificate hashes in base64 format. Please ensure that you use hash values provided by AUTHADA.
@return Returns YES if the mode could be set; otherwise NO.
*/
-(BOOL) setModeToStandardWithURL:(nonnull NSURL*)url hashes:(nonnull NSArray<NSString*>*)hashes;

/*!
 @brief Set the AALMode to "Demo".
 @discussion In this mode the AALManager simulates network and NFC communication. You can use the different demo modes to test your application against different scenarios. Currently, the demo mode does not support change PIN or unlock PIN processes.
 @param  demoConfiguration defines the current demo test case.
 @return Returns YES if the mode could be set; otherwise NO.
 */
-(BOOL) setModeToDemoWithConfiguration:(AALDemoConfiguration)demoConfiguration;


#pragma mark - Delegate Queue

/*!
 @brief Defines the queue where all delegate methods will be called.
 @discussion If you don't set a custom queue all delegate methods will be called on the main queue.
 */
@property(nonatomic, strong) dispatch_queue_t delegateQueue;

#pragma mark - Start Methods

/*!
 @brief Start the ident process.
 @param  mobileToken The input value represents the start token for a specific ident process.
 @param  delegate This delegate needs to implement the AALManagerIdentDelegate protocol. This is needed to communicate with the app.
 @param  error Error information if this method can't start the ident process.
 @return Returns YES if the process could be started; otherwise NO.
 */
-(BOOL) startIdentProcessWithMobileToken:(NSString*)mobileToken
                                delegate:(id<AALManagerIdentDelegate>)delegate
                                   error:(NSError**)error;

/*!
 @brief Start the change PIN process.
 @param  delegate This delegate needs to implement the AALManagerChangePinDelegate protocol. This is needed to communicate with the app.
 @param  error Error information if this method can't start the change PIN process.
 @return Returns YES if the process could be started; otherwise NO.
 */
-(BOOL) startChangePINProcessWithDelegate:(id<AALManagerChangePinDelegate>)delegate
                                    error:(NSError**)error;

/*!
 @brief Start the unlock PIN process.
 @param  delegate  This delegate needs to implement the AALManagerUnlockPinDelegate protocol. This is needed to communicate with the app.
 @param  error Error information if this method can't start the unlock PIN process.
 @return Returns YES if the process could be started; otherwise NO.
 */
-(BOOL) startUnlockPINProcessWithDelegate:(id<AALManagerUnlockPinDelegate>)delegate
                                    error:(NSError**)error;

#pragma mark - Cancel
/*!
 @brief Cancel the current running process.
 @discussion After calling this method no process delegate method will be called anymore.
 @return Returns YES if a process was canceled; otherwise NO.
 */
-(BOOL) cancelRunningProcess;

#pragma mark - Infos

/*!
 @brief Check if the current device, operating system and app configuration supports NFC.
 @return Returns YES if NFC is available; otherwise NO.
 */
+(BOOL) isDeviceNFCSupported;

/*!
 @brief Check if a string is in a compatible mobileToken format. For example you can check if a QR code could represent a valid mobileToken.
 @param  mobileToken The input value representing a possible mobile token string
 @return Returns YES if the format of the string is compatible to the mobileToken format; otherwise NO.
 */
+(BOOL) isValidMobileTokenFormat:(NSString*)mobileToken;

#pragma mark - Version

/*!
 @brief Get the AAL version number.
 @return Returns AAL version number as String.
 */
+(NSString*) aalVersionNumber;

/*!
 @brief Get the AAL build number.
 @return Returns AAL build number as String.
 */
+(NSString*) aalBuildNumber;

#pragma mark - Deprecated Methods

/*!
 @brief Set the AALMode to "Standard".
 @discussion In this mode the AALManager does not simulate anything.
 @param  url defines the endpoint to work with.
 @return Returns YES if the mode could be set; otherwise NO.
 */
-(BOOL) setModeToStandardWithURL:(NSURL*)url DEPRECATED_MSG_ATTRIBUTE("Use setModeToStandardWithURL:hashes: method instead.");

@end

NS_ASSUME_NONNULL_END
