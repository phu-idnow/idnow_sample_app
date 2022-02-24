//
//  AALDemoConfigurations.h
//  AAL
//
//  Created by Samuel Florian Strupp on 31.10.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

typedef NS_ENUM(NSUInteger, AALDemoConfiguration) {
    AALDemoConfiguration_Default = 0, //PIN=123456; CAN=333333
    AALDemoConfiguration_GoodCaseNoResultToken,
    AALDemoConfiguration_GeneralHTTPError,
    AALDemoConfiguration_InvalidMobileToken,
    AALDemoConfiguration_NewMobileTokenNeeded,
    AALDemoConfiguration_IncompatibleClientVersion,
    AALDemoConfiguration_NFCNotAvailable,
    AALDemoConfiguration_BlockedCard,
    AALDemoConfiguration_PhotoIdent,
    AALDemoConfiguration_CardDeactivated,
    AALDemoConfiguration_CardLost,
    AALDemoConfiguration_CardLostRecoverable,
    AALDemoConfiguration_EidInvalid,
    AALDemoConfiguration_NoEidCard,
    AALDemoConfiguration_EidSessionExpired,
    AALDemoConfiguration_EidAuthenticate,
    AALDemoConfiguration_GoodCaseWithReturnURL,
    AALDemoConfiguration_GoodCaseWithReturnURLAndNoResultToken,
    AALDemoConfiguration_CertificatePinningFailed,
    AALDemoConfiguration_PhotoIdentWithSignature,
    AALDemoConfiguration_PhotoIdentOnlySignature,
    AALDemoConfiguration_PhotoIdentOnlyOCRFields,
    AALDemoConfiguration_PhotoIdentNoGermanIDAllowed,
    AALDemoConfiguration_PhotoIdent_AR_D_2011_NotAllowed
};
