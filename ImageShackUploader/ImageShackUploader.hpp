/*********************************************************************
*	@brief ImageShack Qt lib	
*
* 	An open source Qt lib to upload photos and videos to ImageShack.
*	This lib was first created to be plugged on Thumbnail me projet,	
* 	a software generating thumbnails from many types of movies.
*	
*	@file		ImageShackUploader.hpp	
*	@class		ImageShackUploader
*		 		The header of the ImageShackUploader class. 
*				This class interacts with the application and uploads
*				photos and videos to ImageShack web site
*
*	@author		Christ "Supm4n" Azika-Eros <christ@azika-eros.org>	
*	@note		Copyright (C) 2010-2011 Christ Azika-Eros
*				License  : Creative Commons GNU GPL
*						   http://creativecommons.org/licenses/GPL/2.0/ 
*	 			Web site : http://github.com/Supm4n/ImageShackUploader.git
*	@version	0.1
*********************************************************************/
#ifndef  HEADER_IMAGESHACKUPLOADER
#define  HEADER_IMAGESHACKUPLOADER

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QHashIterator>
#include <QImage>
#include <QMimeData>
#include <QNetworkAccessManager>
#include <QNetworkProxy>
#include <QNetworkReply>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QUrl>
#include <QWidget>
 
#include "ImageShackError.hpp"
#include "ImageShackObject.hpp"
#include "ImageShackResponse.hpp"

#define  TIMEOUT 10000

/**
 * @brief ImageShackUploader
 */
class ImageShackUploader : public QObject
{
	Q_OBJECT

    public  : // Public methods

			/**
			 * @brief constructor of ImageShackUploader class
			 *
			 * @param developerKey	the developer key received by ImageShack to
			 * 						use  their APIs (optional for the constructor)
			 * @param userName		the user name (optional)
			 * @param userPassword	the user password (optional)
			 * @param proxy			the proxy settings to use (optional) 
			 */
            ImageShackUploader(QString         developerKey =  ""   ,
                               QNetworkProxy * proxy		= NULL );

			/**
			 * @brief destructor of ImageShackUploader class 
			 */
            ~ImageShackUploader(void);

			/**
			 * @brief public method uploading a list of images
			 *
			 * If uploads are in progress, the signal uploadAlreadyStarted
			 * is emitted
			 *
			 * @see   signal uploadAlreadyStarted()
			 * @see   signal authentificationResponse()
			 * @see	  signal uploadError(ImageShackError::UploadError)
			 * @see   signal uploadProgress(ImageShackObject    ,
			 * 								  qint64 bytesreceived,
			 * 								  qint64 bytesTotal   )
			 * @see	  signal uploadDone(ImageShackResponse) 
			 * @see	  signal endOfUploads()
			 * @see   signal authentificationRequired(QNetworkReply ,
			 * 					  					  QAuthenticator)
			 * @see	  signal proxyAuthentificationRequired(QNetworkProxy   ,
		 	 *                                             QAuthentificator)
			 *
			 * @param images		images' list to upload 
			 * @param userName		the user name (optional)
			 * @param userPassword  the user password (optional)
			 */
            void uploadImages(QList<ImageShackObject *> images            , 
                              QString                 	userName     = "" ,
                              QString 			    	userPassword = "");

			/**
			 * @brief disable the use of the proxy
			 *
			 * set proxy attribut to NULL. No proxy will be 
			 * used when uploading files
			 */
            void noProxy();

			/**
			 * @brief check the user's login and password
			 *
			 * @see   signal authentificationResponse()

			 * @param userName     the user name 
			 * @param userPassword the user password
			 */
            void checkUserPassword(QString	userName     ,
                                   QString   userPassword);

    signals : // Signals

			/**
			 * @brief this signal is emitted when each image/video is uploaded
			 *
			 * return the results of the upload 

			 * @see method ImageShackResponse::getImageShackResponse()
			 *
			 * @param uploadResponse the results of the upload
			 */
            void uploadDone(ImageShackResponse * uploadResponse);


			/**
			 * @brief this signal notifies the end of uploads
			 *
			 * it is emitted when the upload of a list of image/video
			 * submitted is finished
			 */
            void endOfUploads();

			/**
			 * @brief this signal is emitted when uploads have already started
			 **/
            void uploadAlreadyStarted();

			/**
			 * @brief this signal notifies uploads' progress
			 *
			 * @param fileUploaded	the being uploaded
			 * @param bytesReceived number of bytes sent
			 * @param bytesTotal 	total bytes to send
			 */
            void uploadProgress(ImageShackObject * fileUploaded,
								qint64 bytesReceived		   , 
								qint64 bytesTotal			  );

			/**
			 * @brief this signal is emitted when an error occured
			 * 		  during uploads
			 *
			 * @see ImageShackError::UploadError
			 *
			 * @param error	the error type
			 */
            void uploadError(ImageShackError::UploadError error);

            /**
            *	@see QNetworkAccessManager signal
            *
            **/
            void authentificationRequired(QNetworkReply  * reply		   ,
                                          QAuthenticator * authentificator);

            /**
            *	@see QNetworkAccessManager signal
            *
            **/
            void proxyAuthentificationRequired(const QNetworkProxy & proxy,
                                               QAuthenticator      * authenticator);

            /**
            *	The authentification response
            *
            **/
            void authentificationResponse(bool response);
	
	public slots :

			/**
			 * @brief Aborts uploads
			 */
			void abortUploads();


	private : // Private objects or variables

            QList<ImageShackObject *> filesToUpload;
            /**
            *	QString fileBeingUploaded the file being uploading
            *
            *	@access private
            **/
            ImageShackObject * fileBeingUploaded;

            /**
			*	QString imageUploadUrl	The entry point to upload 
			*						    images to ImageShack
			*	@access private
			**/
            QString imageUploadUrl;

            /**
            *	QString authentificationUrl the url to test the user password
            *	http://www.imageshack.us/auth.php?username=kwentakill&password=rousseau
            *
            **/
            QString authentificationUrl;

			/**
			*	bool	removeInformationBar boolean to leave/remove
			*			    				 information bar on the thumbnail
			*			    				 image generated by ImageShack	
			*	@access	private
			**/	
			bool	removeInformationBar;

            /**
            *	bool uploadsProcessing	equals true when a file is being uploaded.
            *							no upload can start in this case
            *
            *	@access	private
            **/
            bool	uploadsProcessing;

			/**
			 * @brief set to true when an error occured. 
			 *
			 * This is use to not emit multiple signals
			 */
            bool	uploadAborted;

            /**
			*	QNetworkAccessManager	networkManager	the network manager	
			*
			*	@access	private
			**/	
			QNetworkAccessManager * networkManager;

			/**
			*	QNetworkProxy		the	proxy to use when uploading
			*
			*	@access private
			**/
			QNetworkProxy * proxy;

			/**
			*	QNetworkReply	response	ImageShack response
			*
			*	@access private
			**/	
			QNetworkReply * networkReply;	

			/**
			*	QString developerKey	the developer key received 
			*		      			    to use APIs
			*	@access private
			**/	
			QString developerKey;	

			/**
            *	QString	lastUserName	the user name. Only required to upload
			*						to a specific account (userUploadImage)
			*	@access	private
			**/
            QString userName;

            /**
            *	QString	userPassword	the user name. Only required to upload
            *						to a specific account (userUploadImage)
            *	@access	private
            **/
            QString userPassword;

			/**
			 * @brief timer to detect time out processes
			 */
			QTimer * timeoutTimer;

            int nbFilesToUploads;

            int nbFilesUploaded;

	private slots : // private slots	

            /**
			*	Manage replies after the image is uploaded
			*
			*	@access private	
            **/
			void imageUploaded();

			/**
			*	Manage image uploads
			*
			*	@param  QString fileUploaded	the file uploaded
			*	@param	QHash<QString, QString> informations concerning
			*								    the uploads
			*	@access	private
			*/
			void manageMultiUploads(ImageShackResponse * uploadResponse);

            /**
            *	manage authentification requirements
            *
            **/
            void manageAuthentificationRequired(QNetworkReply  * reply,
                                                QAuthenticator * authentificator);

            /**
            *	manage proxy authentification requirements
            *
            **/
            void manageProxyAuthentificationRequired(const QNetworkProxy & proxy,
                                                     QAuthenticator      * authenticator);

            /**
            *	manage authentification response
            *
            **/
            void manageAuthentificationResponse();

            /**
			*	Manage upload errors 
			*
			*	@access private	
            **/
            void manageUploadError(QNetworkReply::NetworkError errorCode);

            /**
            *	Manage the upload progression
            *
            *	@access private
            **/
            void manageUploadProgress(qint64 bytesReceived,qint64 bytesTotal);


			/**
			 * @brief slot handling time out
			 */
			void handleTimeOut();

	private : // private methods
			
            /**
            *	Upload an image to an account
            *
            *	@param	QString imagePath	    the image path
            *	@param	QString tags	        image tags
            *	@param	QString resizeOption	the resize option,
            *									default value is resample
            *	@param	QString user		    the user ident
            *	@param	QString password	    the user password
            *	@access	private
            */
            void uploadOneImage(ImageShackObject *   image,
                                QString userName     = "" ,
                                QString userPassword = "");

            /**
			*	Upload an image. This method is called by 
			*	userUploadImage and anonymousUploadImage
			*	methods	
			*
			*	@access private	
			*/
            void sendImage(ImageShackObject *     imageToUpload,
                           QHash<QString, QString>   headers  );

            /**
            *	Return the mimetype basing on the file extension
            *
            *	@access private
            */
            QString mimeType(QString imagePath);

            /**
            *	Return the mimeType list
            *
            *	@access private
            */
            QHash<QString, QStringList> mimeTypeList();

	public  : // Setters and Getters

			/**
			*	the getter of the boolean removeInformationBar	
			*		
			*	@return removeInformationBar
			*	@access public	
			*/
			bool getRemoveInformationBar();

			/**
			 * @brief return true if uploads are in progress
			 *
			 * @return true/false in uploads are in progress 
			 */
			bool uploadsInProgress();

			/**
			*	the getter of the proxy
			*
			*	@return * QNetworkProxy
			*	@access	  public
			*/
			QNetworkProxy * getProxy();

			/**
			*	the getter of developerKey 
			*		
			*	@return developerKey
			*	@access public	
			*/
			QString getDeveloperKey();

			/**
			*	the getter of imageUploadUrl
			*		
			*	@return developerKey
			*	@access public	
			*/
			QString getImageUploadUrl();

            /**
            *	the getter of userName
            *
            *	@return developerKey
            *	@access public
            */
            QString getLastUserName();

			/**
			*	the setter of developerKey
			*		
			*	@param  developerKey	the developer key needed to upload
			*							to unified ImageShack API
			*	@access	public	
			*/
			void setDeveloperKey(QString developerKey);

			/**
			*	the setter of imageUploadUrl
			*		
			*	@param  developerKey	The entry point to upload 
			*							images to ImageShack
			*	@access	public	
			*/
			void setImageUploadUrl(QString imageUploadUrl);

			/**
			*	the setter of the proxy use to upload
			*
			*	@param  QNetworkProxy	the proxy to use
			* 	@access public
			*/
			void setProxy(QNetworkProxy * proxy);
			
			/**
			*	the setter of imageEntryUpload 
			*		
			*	@param	removeInformationBar	 the boolean to remove/leave 
			*			    					 the information bar from
			*			 	     				 thumbnails
			*	@access	public				 
			*/
			void setRemoveInformationBar(bool removeInformationBar);

};

#endif // HEADER_IMAGESHACKUPLOADER
