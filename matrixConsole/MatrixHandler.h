/*
 Copyright 2014 OpenMarket Ltd
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

#import <MatrixSDK/MatrixSDK.h>

extern NSString *const kMatrixHandlerUnsupportedMessagePrefix;

typedef enum : NSUInteger {
    MatrixHandlerStatusLoggedOut = 0,
    MatrixHandlerStatusLogged,
    MatrixHandlerStatusStoreDataReady,
    MatrixHandlerStatusServerSyncDone
} MatrixHandlerStatus;

@interface MatrixHandler : NSObject

@property (strong, nonatomic) MXRestClient *mxRestClient;
@property (strong, nonatomic) MXSession *mxSession;

@property (strong, nonatomic) NSString *homeServerURL;
@property (strong, nonatomic) NSString *homeServer;
@property (strong, nonatomic) NSString *userLogin;
@property (strong, nonatomic) NSString *userId;
@property (strong, nonatomic, readonly) NSString *localPartFromUserId;
@property (strong, nonatomic) NSString *accessToken;

// The type of events to display
@property (strong, nonatomic) NSArray *eventsFilterForMessages;

// Matrix user's settings
@property (nonatomic) MXPresence userPresence;

@property (nonatomic,readonly) MatrixHandlerStatus status;
@property (nonatomic,readonly) BOOL isResumeDone;
// return the MX cache size in bytes
@property (nonatomic,readonly) NSUInteger MXCacheSize;
// return the sum of the caches (MX cache + media cache ...)
@property (nonatomic,readonly) NSUInteger cachesSize;

+ (MatrixHandler *)sharedHandler;

- (void)pauseInBackgroundTask;
- (void)resume;
- (void)logout;

// Flush and restore Matrix data
- (void)forceInitialSync:(BOOL)clearCache;

- (void)enableInAppNotifications:(BOOL)isEnabled;

- (BOOL)isSupportedAttachment:(MXEvent*)event;
- (BOOL)isEmote:(MXEvent*)event;

// Note: the room state expected by the 3 following methods is the room state right before handling the event
- (NSString*)senderDisplayNameForEvent:(MXEvent*)event withRoomState:(MXRoomState*)roomState;
- (NSString*)senderAvatarUrlForEvent:(MXEvent*)event withRoomState:(MXRoomState*)roomState;
- (NSString*)displayTextForEvent:(MXEvent*)event withRoomState:(MXRoomState*)roomState inSubtitleMode:(BOOL)isSubtitle;

// search if a 1:1 conversation has been started with this member
- (NSString*) getRoomStartedWithMember:(MXRoomMember*)roomMember;

- (CGFloat)getPowerLevel:(MXRoomMember *)roomMember inRoom:(MXRoom *)room;

// provide a non empty display name
- (NSString*) getMXRoomMemberDisplayName:(MXRoomMember*)roomMember;

// return YES if the text contains a bing word
- (BOOL)containsBingWord:(NSString*)text;

@end
