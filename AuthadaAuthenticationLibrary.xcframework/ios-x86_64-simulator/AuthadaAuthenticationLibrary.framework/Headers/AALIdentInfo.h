//
//  AALIdentInfo.h
//  AuthadaAuthenticationLibrary
//
//  Created by Samuel Florian Strupp on 01.07.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AALIdentInfo : NSObject

/*!
 @brief An array with all the localized field names being accessed on the eID card later in the process.
 @discussion It is mandatory to give this information to the user.
 */
@property(nullable) NSArray<NSString*> *localizedFieldsBeingAccessed;

/*!
 @brief A dictionary with localized key and localized value strings about the fields in the used certificate.
 @discussion It is mandatory to give this information to the user.
 */
@property(nullable) NSDictionary<NSString*,NSString*> *localizedCertificateFields;

/*!
 @brief The business use case for the current ident process.
 @discussion It is optional to show this information to the user.
 */
@property(nullable) NSString *businessUseCase;

/*!
 @brief The service provider for the current ident process.
 @discussion It is optional to show this information to the user.
 */
@property(nullable) NSString *serviceProvider;

@end
