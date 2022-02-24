//
//  AALManagerDelegate.h
//  AuthadaAuthenticationLibrary
//
//  Created by Samuel Florian Strupp on 26.06.19.
//  Copyright © 2019 Authada GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AALBlockTypes.h"
#import "AALIdentInfo.h"

NS_ASSUME_NONNULL_BEGIN

typedef enum : NSUInteger {
    AALInterruptReasonUnknown = 0,
    AALInterruptReasonCardRemoved,
    AALInterruptReasonUserCancelNFC,
    AALInterruptReasonEIDWrongCard
} AALInterruptReason;

typedef enum : NSUInteger {
    AALSecretQuestReasonUnknown = 0,            //reason unknown
    AALSecretQuestReasonUserCancel,             //User aborted previous SecretQuest
    AALSecretQuestReasonIdentPin,               //6-digit PIN needed for ident process
    AALSecretQuestReasonIdentChangeTransportPin, //old 5-digit transport PIN needed for changing PIN in ident process
    AALSecretQuestReasonIdentChangeNewPin,       //new 6-digit PIN needed for changing PIN in ident process
    AALSecretQuestReasonIdentChangeCan,          //CAN needed for changing PIN in ident process
    AALSecretQuestReasonCanWrong,                   //Can was wrong
    AALSecretQuestReasonPinWrongTwoPinTriesLeft,    //Pin was wrong, two PIN tries left
    AALSecretQuestReasonPinWrongOnePinTryLeft,      //Pin was wrong, one PIN try left
    AALSecretQuestReasonOnePinTryLeftCanRequiredToUnlockPin, //CAN needed to unlock last PIN try
    AALSecretQuestReasonCanWrongOnePinTryLeft       //CAN wrong for last PIN try
} AALSecretQuestReason;

@protocol AALManagerIdentDelegate <NSObject>

#pragma mark - Ident

@required

/*!
 @brief Tells the delegate that the ident process finished successfully.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 @param resultToken The resultToken for the process or nil.
 */
-(void) identProcessFinishedSuccessfullyWithResultToken:(nullable NSString*)resultToken;

/*!
 @brief Tells the delegate that the ident process finished with an error.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 @param error This error describes the reason why the process did not complete successfully.
 */
-(void) identProcessFinishedWithError:(NSError*)error;

/*!
 @brief Tells the delegate that the ident process was canceled.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 */
-(void) identProcessCanceled;


/*!
 @brief Tells the delegate which informations should be displayed to the user
 @param info Includes all the information for the user.
 @param continueBlock Continue the process by calling this continue block with the correct parameters.
 */
-(void) identProcessReceivedIdentInfo:(AALIdentInfo*)info continueBlock:(AALContinueBlock)continueBlock;

/*!
 @brief Tells the delegate that a secret like the PIN or CAN is required.
 @param newSecret Use this object to fill in the secret. It also defines which kind of secret is required.
 @param reason The reason why this secret request is called. Use this information to display further information to the user.
 @param completion Continue the process by calling this completion block with the correct parameters.
 */
-(void) identProcessReceivedNewSecretRequest:(EIDSecret*)newSecret
                                    reason:(AALSecretQuestReason)reason
                           completionBlock:(AALSecretCompletionBlock)completion;

/*!
 @brief Tells the delegate that the NFC communication will start directly after calling the continueBlock.
 @discussion Use this method to prepare the user for the card communication process.
 @param continueBlock Continue the process by calling this continue block with the correct parameters.
 */
-(void) identProcessWillStartNFCCommunicationWithContinueBlock:(AALContinueBlock)continueBlock;

/*!
 @brief Tells the delegate that the process was interrupted.
 @discussion Use this method inform the user about the problem.
 @param reason The reason for the interrupt.
 @param continueBlock Continue the process by calling this continue block with the correct parameters.
 */
-(void) identProcessInterruptedWithReason:(AALInterruptReason)reason
                            continueBlock:(AALContinueBlock)continueBlock;

@optional

/*!
 @brief Tells the delegate that server communication is in progress.
 @discussion Can be called several times in a row; The UI can show a loading screen. The process is not paused when this method is called.
 */
-(void) identProcessDidStartServerCommunication;

/*!
 @brief Gives the delegate the option to change the transport PIN while running the ident process.
 @param result Answer the question by calling this result block.
 @param reason The reason why this question is asked. Use this information to display further information to the user.
 */
-(void) identProcessIsChangeTransportPINNeeded:(AALResultBlock)result reason:(AALSecretQuestReason)reason;

/*!
 @brief Tells the delegate that the transport PIN was changed successfully.
 @discussion Use this method to inform the user about the successful PIN change. It also indicates that the ident process will continue.
 @param continueBlock Continue the ident process by calling this continue block with the correct parameters.
 */
-(void) identProcessChangeTransportPINWasSuccessfulWithContinueBlock:(AALContinueBlock)continueBlock;

/*!
@brief Tells the delegate that a returnURL was received.
@discussion This delegate call is not pausing the ident process. Just store the returnURL for later use if you need this parameter.
@param returnURL The returnURL to call after the process finished successfully.
*/
-(void) identProcessReturnURLReceived:(NSURL*)returnURL;

@end

#pragma mark - Change PIN

@protocol AALManagerChangePinDelegate <NSObject>

@required

/*!
 @brief Tells the delegate that the change PIN process finished successfully.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 */
-(void) changePINProcessFinishedSuccessfully;

/*!
 @brief Tells the delegate that the change PIN process finished with an error.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 @param error This error describes the reason why the process does not complete successfully.
 */
-(void) changePINProcessFinishedWithError:(NSError*)error;

/*!
 @brief Tells the delegate that the change PIN process was canceled.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 */
-(void) changePINProcessCanceled;

/*!
 @brief Asks the delegate for the current (old) five- or six-digit PIN of the eID card.
 @discussion The user has to decide if a five or six digit PIN is needed. Use only the required PIN object for the completion block.
 @param sixDigitPIN Use this object to fill in a six-digit PIN.
 @param fiveDigitPIN Use this object to fill in a five-digit transport PIN.
 @param completion Continue the process by calling this completion block with the correct parameters.
 */
-(void) changePINProcessNeedsOldPIN:(EIDSecret*)sixDigitPIN
                       fiveDigitPIN:(EIDSecret*)fiveDigitPIN
                    completionBlock:(AALSecretCompletionBlock)completion;

/*!
 @brief Asks the delegate for the new six-digit PIN for the eID card.
 @param sixDigitPIN Use this object to fill in the new PIN.
 @param completion Continue the process by calling this completion block with the correct parameters.
 */
-(void) changePINProcessNeedsNewPIN:(EIDSecret*)sixDigitPIN
                    completionBlock:(AALSecretCompletionBlock)completion;

/*!
 @brief Asks the delegate for the CAN of the eID card to unlock the last PIN try.
 @param can Use this object to fill in the CAN.
 @param completion Continue the process by calling this completion block with the correct parameters.
 */
-(void) changePINProcessNeedsCAN:(EIDSecret*)can
                 completionBlock:(AALSecretCompletionBlock)completion;

@optional

/*!
 @brief Tells the delegate that the process was interrupted.
 @discussion Use this method inform the user about the problem.
 @param reason The reason for the interrupt.
 @param continueBlock Continue the process by calling this continue block with the correct parameters.
 */
-(void) changePINProcessInterruptedWithReason:(AALInterruptReason)reason
                                continueBlock:(AALContinueBlock)continueBlock;

@end

#pragma mark - Unlock PIN

@protocol AALManagerUnlockPinDelegate <NSObject>

@required

/*!
 @brief Tells the delegate that the unlock PIN process finished successfully.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 */
-(void) unlockPINProcessFinishedSuccessfully;

/*!
 @brief Tells the delegate that the unlock PIN process finished with an error.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 @param error This error describes the reason why the process does not complete successfully.
 */
-(void) unlockPINProcessFinishedWithError:(NSError*)error;

/*!
 @brief Tells the delegate that the unlock PIN process was canceled.
 @discussion After this delegate method is called the process is finished and no other delegate methods for this process will be called.
 */
-(void) unlockPINProcessCanceled;

/*!
 @brief Asks the delegate for the PUK of the eID card to unlock the PIN.
 @param puk Use this object to fill in the PUK.
 @param completion Continue the process by calling this completion block with the correct parameters.
 */
-(void) unlockPINProcessNeedsPUK:(EIDSecret*)puk
                 completionBlock:(AALSecretCompletionBlock)completion;

@end

NS_ASSUME_NONNULL_END
