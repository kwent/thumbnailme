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
*	@filesource	ImageShackUploader.cpp
*	@role	 	The Implementation of the ImageShackUploader class.
*				This class handle ImageShack upload response
*
*********************************************************************/
#include "ImageShackError.hpp"

/**
*	@brief Return the error code coresponding to the network error
*	@return UploadError the error code	
**/
ImageShackError::UploadError ImageShackError::getErrorCode(QNetworkReply::NetworkError errorCode)
{
	UploadError code = NoError;

	switch(errorCode)
	{
		case QNetworkReply::NoError                           : code=NoError;                           break;
		case QNetworkReply::ConnectionRefusedError            : code=ConnectionRefusedError;            break;
    	case QNetworkReply::RemoteHostClosedError             : code=RemoteHostClosedError;             break;
		case QNetworkReply::HostNotFoundError                 : code=HostNotFoundError;                 break;
    	case QNetworkReply::TimeoutError                      : code=TimeoutError;		   				break;
		case QNetworkReply::OperationCanceledError            : code=OperationCanceledError; 			break;
    	case QNetworkReply::SslHandshakeFailedError           : code=SslHandshakeFailedError;			break;
		case QNetworkReply::ProxyConnectionRefusedError       : code=ProxyConnectionRefusedError; 		break;
    	case QNetworkReply::ProxyConnectionClosedError        : code=ProxyConnectionClosedError;  		break;
		case QNetworkReply::ProxyNotFoundError 			      : code=ProxyNotFoundError;				break;
    	case QNetworkReply::ProxyTimeoutError                 : code=ProxyTimeoutError;					break;
		case QNetworkReply::ProxyAuthenticationRequiredError  : code=ProxyAuthenticationRequiredError;  break;
    	case QNetworkReply::ContentAccessDenied               : code=ContentAccessDenied;               break;
		case QNetworkReply::ContentOperationNotPermittedError : code=ContentOperationNotPermittedError; break;
    	case QNetworkReply::ContentNotFoundError              : code=ContentNotFoundError;		        break;
		case QNetworkReply::AuthenticationRequiredError       : code=AuthenticationRequiredError; 		break;
    	case QNetworkReply::ProtocolUnknownError              : code=ProtocolUnknownError;		 		break;
		case QNetworkReply::ProtocolInvalidOperationError     : code=ProtocolInvalidOperationError; 	break;
    	case QNetworkReply::UnknownNetworkError               : code=UnknownNetworkError; 		   		break;
		case QNetworkReply::UnknownProxyError 			      : code=UnknownProxyError;			   		break;
    	case QNetworkReply::UnknownContentError               : code=UnknownContentError;		   		break;
		case QNetworkReply::ProtocolFailure  			      : code=ProtocolFailure;			   		break;
    	case QNetworkReply::ContentReSendError		          : code=ContentReSendError;			   	break; 
    	case QNetworkReply::TemporaryNetworkFailureError      : code=TemporaryNetworkFailureError;   	break;
	}

	return code;
}


/**
* @brief Return the error code corresponding to an ImageShack error
*
* @param usableResponse
*
* @return 
*/
ImageShackError::UploadError ImageShackError::getErrorCode(QHash<QString, QString> usableResponse)
{
	UploadError code = NoError;

	if(usableResponse["error"].contains(QString("no more than 5 Mb")))
		code = MaxSizeReached;

	//qDebug()  << "error code : " << code;
	return code;
}

