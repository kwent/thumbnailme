/*********************************************************************
*	Thumbnail me 3.0
*
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@package	Thumbnail me 3.0
*	@author		Christ Azika-Eros <christ@azika-eros.org>
*	@copyright	Quentin Rousseau (c) 2010 2009, Quentin Rousseau
*	@license	Creative Commons GNU GPL
*				http://creativecommons.org/licenses/GPL/2.0/
*	@link 		http://thumbnailme.sourceforge.net/
*	@version	3.0
*
*	@filesource	ImageShackResponse.hpp
*	@role	 	The header of the ImageShackResponse class.
*				This class handle ImageShack upload response
*
*********************************************************************/
#ifndef  HEADER_IMAGESHACKERROR
#define  HEADER_IMAGESHACKERROR

#include <QByteArray>
#include <QDebug>
#include <QNetworkReply>
#include <QString>
#include <QWidget>

/**
* 	ImageShackError class
*
**/
class ImageShackError : public QObject
{
    Q_OBJECT

    public  : // variables, enums

            /**
            *	Enumeration specifing the type of error.
            *   Its include the QNetworkReply::NetworkError enumeration
			*   @see QNetworkReply
            **/
            enum UploadError{NoError                     , ConnectionRefusedError,
                             RemoteHostClosedError       , HostNotFoundError,
                             TimeoutError                , OperationCanceledError,
                             SslHandshakeFailedError     , ProxyConnectionRefusedError,
                             ProxyConnectionClosedError  , ProxyNotFoundError,
                             ProxyTimeoutError           , ProxyAuthenticationRequiredError,
                             ContentAccessDenied         , ContentOperationNotPermittedError,
                             ContentNotFoundError        , AuthenticationRequiredError,
                             ProtocolUnknownError        , ProtocolInvalidOperationError,
                             UnknownNetworkError         , UnknownProxyError,
                             UnknownContentError         , ProtocolFailure ,
                             ContentReSendError		     , UnKnownError,
							 TemporaryNetworkFailureError, FailedOpeningTheFile,
							 MaxSizeReached};

    public : // public method
			/**
			*	Return the error code coresponding to the network error
			*
			**/
            static UploadError getErrorCode(QNetworkReply::NetworkError errorCode);

			/**
			 * @brief Return the error code corresponding to an ImageShack error
			 *
			 * @param usableResponse
			 *
			 * @return 
			 */
			static UploadError getErrorCode(QHash<QString, QString> usableResponse);

    //public  : // Setters and Getters
};

#endif
