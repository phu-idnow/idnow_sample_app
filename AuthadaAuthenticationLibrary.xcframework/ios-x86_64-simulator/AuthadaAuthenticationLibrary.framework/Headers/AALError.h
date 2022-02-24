//
//  AALError.h
//  AuthadaAuthenticationLibrary
//
//  Created by Samuel Florian Strupp on 04.10.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

#ifndef AALError_h
#define AALError_h

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

//MARK: - Error codes

extern NSErrorDomain const AALErrorDomain;

/*!
 * @enum AALError
 *
 * @discussion  Possible errors returned by AAL framework
 * @constant    AALErrorGeneral                         General AAL error without further information.
 * @constant    AALErrorGeneralHTTPError                Indicates that an unexpected HTTP response from the AUTHADA backend was received.
 * @constant    AALErrorInvalidMobileToken              The provided MobileToken cannot be used for an AUTHADA authentication. MobileToken is invalid or expired.
 * @constant    AALErrorNewMobileTokenNeeded            The provided MobileToken was used too often and is used up. Please fetch a new MobileToken from your backend and restart the process with this new MobileToken.
 * @constant    AALErrorInvalidProcessRequirements      The provided MobileToken is valid but the requirements for the process are not valid or not supported.
 * @constant    AALErrorIncompatibleClientVersion       Your version of the AUTHADA Authentication Library is incompatible to the backend version provided as the endpoint. Update the library or change the used endpoint.
 * @constant    AALErrorNFCNotAvailable                 The device (iPhone, iPad) or the operating system (iOS lower than 13.0) does not support NFC communication.
 * @constant    AALErrorCardBlocked                     The user uses an eID card that has been blocked.
 * @constant    AALErrorWrongPINCardBlocked             The user entered a wrong PIN. Now the eID card is blocked.
 * @constant    AALErrorCardDeactivated                 The eID function of the attached card is deactivated and cannot be used. The eID function can be activated at the responsible authority.
 * @constant    AALErrorCardLost                        The user removed the eID card after the secured card communication phase has been internally started by the library. The process cannot be continued and needs to be restarted.
 * @constant    AALErrorEidInvalid                      The users card is blocked remotely, expired, damaged or invalid and cannot be used.
 * @constant    AALErrorNoEidCard                       A NFC tag has been attached to the device which is not an eID card. The user should be informed that a German ID Card or Residence Permit ("eAT") must be used.
 * @constant    AALErrorEidSessionExpired               The eid session timed out.
 * @constant    AALErrorEidAuthenticate                 An error occurred during the eID communication. After receiving this error you should restart the process with the same MobileToken again. (This error occurs as well when a test eid card is used in a productive environment or a real eid card is used in a test environment.)
 * @constant    AALErrorCertificatePinningFailed        The defined certificate hashs do not match the server certificates.
 * @constant    AALErrorDocumentNotAllowed              The detected document is not allowed in the process.
 * @constant    AALErrorWrongPIN                        The user entered a wrong PIN. The userInfo dictionary includes information about PIN attempts left for key AALErrorRemainingPINAttemptsKey.
 */
typedef NS_ERROR_ENUM(AALErrorDomain, AALError) {
    AALErrorGeneral = 0,
    AALErrorGeneralHTTPError,
    AALErrorInvalidMobileToken,
    AALErrorNewMobileTokenNeeded,
    AALErrorInvalidProcessRequirements,
    AALErrorIncompatibleClientVersion,
    AALErrorNFCNotAvailable,
    AALErrorCardBlocked,
    AALErrorWrongPINCardBlocked,
    AALErrorCardDeactivated,
    AALErrorCardLost,
    AALErrorEidInvalid,
    AALErrorNoEidCard,
    AALErrorEidSessionExpired,
    AALErrorEidAuthenticate,
    AALErrorCertificatePinningFailed,
    AALErrorDocumentNotAllowed,
    AALErrorWrongPIN
};

//MARK: - User info

/** If the key is present the value is a NSNumber representing the remaining attampts to enter the PIN correctly. The values correspond to the enum values in AALRemainingPINAttempts */
extern NSString* const AALErrorRemainingPINAttemptsKey;

typedef NS_ENUM(NSUInteger, AALRemainingPINAttempts) {
    AALRemainingPINAttemptsNone = 0,
    AALRemainingPINAttemptsOneWithCAN = 1,
    AALRemainingPINAttemptsTwo = 2,
};

NS_ASSUME_NONNULL_END

#endif /* AALError_h */
