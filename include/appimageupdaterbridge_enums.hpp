#ifndef APPIMAGE_UPDATER_BRIDGE_ENUMS_HPP_INCLUDED
#define APPIMAGE_UPDATER_BRIDGE_ENUMS_HPP_INCLUDED
namespace AppImageUpdaterBridge
{

/* Status codes for all process.*/
enum : short {
    /* Common status. */ 
    Initializing = 0,
    Idle = 1,

    /* AppImage Update Information parser status. */ 
    OpeningAppimage,
    CalculatingAppimageSha1Hash,
    ReadingAppimageMagicBytes,
    ReadingAppimageUpdateInformation,
    FindingAppimageType,
    FindingAppimageArchitecture,
    MappingAppimageToMemory,
    SearchingForUpdateInformationSectionHeader,
    UnmappingAppimageFromMemory,
    FinalizingAppimageEmbededUpdateInformation,

    /* Zsync control file parser status. */
    ParsingAppimageEmbededUpdateInformation = 50,
    RequestingGithubApi,
    ParsingGithubApiResponse,
    RequestingZsyncControlFile,
    RequestingBintray,
    ParsingBintrayRedirectedUrlForLatestPackageUrl,
    ParsingZsyncControlFile,
    SearchingTargetFileChecksumBlockOffsetInZsyncControlFile,
    StoringZsyncControlFileDataToMemory,
    FinalizingParsingZsyncControlFile,

    /* Zsync writer status. */
    WrittingDownloadedBlockRanges = 100,
    EmittingRequiredBlockRanges,
    CheckingChecksumsForDownloadedBlockRanges,
    WrittingDownloadedBlockRangesToTargetFile,
    CalculatingTargetFileSha1Hash,
    ConstructingTargetFile
};

/* Error codes for all process. */
enum : short {
    /* Common error. */
    NoError = 0,

    /* AppImage Update Information parser errors. */
    NoAppimagePathGiven = 1,
    AppimageNotReadable,
    NoReadPermission,
    AppimageNotFound,
    CannotOpenAppimage,
    EmptyUpdateInformation,
    InvalidAppimageType,
    InvalidMagicBytes,
    InvalidUpdateInformation,
    NotEnoughMemory,
    SectionHeaderNotFound,
    UnsupportedElfFormat,
    UnsupportedTransport,

    /* Zsync Control File parser errors. */
    IoReadError = 50,
    ErrorResponseCode,
    GithubApiRateLimitReached,
    NoMarkerFoundInControlFile,
    InvalidZsyncHeadersNumber,
    InvalidZsyncMakeVersion,
    InvalidZsyncTargetFilename,
    InvalidZsyncMtime,
    InvalidZsyncBlocksize,
    InvalidTargetFileLength,
    InvalidHashLengthLine,
    InvalidHashLengths,
    InvalidTargetFileUrl,
    InvalidTargetFileSha1,
    ConnectionRefusedError,
    RemoteHostClosedError,
    HostNotFoundError,
TimeoutError,
OperationCanceledError,
SslHandshakeFailedError,
TemporaryNetworkFailureError,
NetworkSessionFailedError,
BackgroundRequestNotAllowedError,
TooManyRedirectsError,
InsecureRedirectError,
ProxyConnectionRefusedError,
ProxyConnectionClosedError,
ProxyNotFoundError,
ProxyTimeoutError,
ProxyAuthenticationRequiredError,
ContentAccessDenied,
ContentOperationNotPermittedError,
ContentNotFoundError,
AuthenticationRequiredError,
ContentReSendError,
ContentConflictError,
ContentGoneError,
InternalServerError,
OperationNotImplementedError,
ServiceUnavailableError,
ProtocolUnknownError,
ProtocolInvalidOperationError,
UnknownNetworkError,
UnknownProxyError,
UnknownContentError,
ProtocolFailure,
UnknownServerError,

   /* Zsync writer errors. */
    HashTableNotAllocated = 100,
    InvalidTargetFileChecksumBlocks,
    CannotOpenTargetFileChecksumBlocks,
    CannotConstructHashTable,
    QbufferIoReadError,
    SourceFileNotFound,
    NoPermissionToReadSourceFile,
    CannotOpenSourceFile,
    NoPermissionToReadWriteTargetFile,
    CannotOpenTargetFile,
    TargetFileSha1HashMismatch
};
}
#endif // APPIMAGE_UPDATER_BRIDGE_HPP_INCLUDED