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
	*			http://creativecommons.org/licenses/GPL/2.0/
*	@link 		http://thumbnailme.sourceforge.net/
*	@version	3.0
*
*	@filesource	ImageShackUploader.cpp
*	@role	 	The Implementation of the ImageShackUploader class. 
*				This class creates the object which will upload
*				photos to ImageShack.
*
*********************************************************************/
#include "ImageShackUploader.hpp"

/**
*	@brief Constructor of ImageShackUploader
*
*	QString developerKey		the developer key received 
*		      			    	to use APIs
*	QString userName			the user name
*       QString userPassword		the user password
*	QNetworkProxy * prosy	 	the proxy
**/
ImageShackUploader::ImageShackUploader(QString         developerKey ,
                                       QNetworkProxy * proxy	    )
{
    this->developerKey         = developerKey;
    this->userName	       = "";
    this->userPassword	       = "";
    this->proxy				   = proxy;
    this->imageUploadUrl       = "http://www.imageshack.us/upload_api.php" ;
	this->removeInformationBar = true;
    this->authentificationUrl  = "http://www.imageshack.us/auth.php";
    this->nbFilesToUploads     = 0;
    this->nbFilesUploaded      = 0;
    this->uploadsProcessing	   = false;
	this->uploadAborted	   	   = false;
	this->timeoutTimer	       = new QTimer(this);

	connect(timeoutTimer, SIGNAL(timeout()), this, SLOT(handleTimeOut()));

    connect(this,SIGNAL(uploadDone(ImageShackResponse *)),this,SLOT(manageMultiUploads(ImageShackResponse *)));
}

/**
*	@brief Destructor of ImageShackUploader
**/
ImageShackUploader::~ImageShackUploader(void) 
{
}

/**----------
*	Methods
**----------*/

/**
*	@brief Check wether the user password is correct
*
*	@see 	signal authentificationResponse(bool response)
*
*	@param  QString userName			the user name
*	@param  QString userPassword		the user password
*/
void ImageShackUploader::checkUserPassword(QString	userName    ,
                                           QString  userPassword)
{
    QUrl url = QUrl(authentificationUrl + "?username=" + userName + "&password=" + userPassword + "&nocookie=1&format=xml");

    QNetworkRequest request(url);
    QNetworkAccessManager * manager = new QNetworkAccessManager;

	this->uploadAborted = false;

    // manage proxy
    if(this->proxy != NULL)
        manager->setProxy(*this->proxy);

    this->networkReply = manager->get(request);

    connect(this->networkReply, SIGNAL(error(QNetworkReply::NetworkError)),
            this , SLOT(manageUploadError(QNetworkReply::NetworkError)));

    connect(this->networkReply, SIGNAL(finished()), this, SLOT(manageAuthentificationResponse()));
}

/**
*	@brief manage authentification response
*
*	@see 	signal authentificationResponse(bool response)
**/
void ImageShackUploader::manageAuthentificationResponse()
{
    QByteArray httpResponse = networkReply->readAll();
    QDomDocument xmlResponse;
    xmlResponse.setContent(httpResponse);

	if(uploadAborted==false)
	{
        QDomElement rootTag = xmlResponse.documentElement();
        if(rootTag.isNull())
        {
            emit authentificationResponse(false);
            return;
        }

        QDomElement errorTag = rootTag.firstChildElement("error");
        if(!errorTag.isNull())
        {
            emit authentificationResponse(false);
            return;
        }

        QDomElement userNameTag = rootTag.firstChildElement("username");
        if(userNameTag.isNull())
        {
            emit authentificationResponse(false);
            return;
        }
        else
        {
            this->userName = userNameTag.text();
            emit authentificationResponse(true);
        }
	}
}

/**
*	Upload a list of images
*
*	@param QList<ImageShackObject *> images	images to upload
*	@param QString	userName		 		the user name (optional)
*	@param QString  userPassword			the user password (optional)
*/
void ImageShackUploader::uploadImages(QList<ImageShackObject *> images   ,
                                      QString                userName    ,
                                      QString 			     userPassword)
{
    if(this->uploadsProcessing == false) // if a previons mutli-upload is not finished
    {
        this->filesToUpload    = images;
        this->nbFilesToUploads = images.size();
        this->nbFilesUploaded  = 0;

        if(this->filesToUpload.size() > 0) // if there are images to upload
        {
            this->uploadsProcessing = true;
			this->uploadAborted = false;
            this->userName = userName;
            this->userPassword = userPassword;

            //qDebug() << " * Nombre de fichiers a uploader = " << this->filesToUpload.size();

            //ImageShackObject * image = (ImageShackObject *) filesToUpload.takeFirst(); // return and remove the first image
            ImageShackObject * image = (ImageShackObject *) filesToUpload.first(); // return and remove the first image

            //qDebug() << " * Fichier allant etre uploade = " + image->getObjectPath();

            //uploadOneImage(image->getObjectPath()  ,
            //               image->getTags()        ,
            //               image->getResizeOption(),
            //               userName, userPassword );

            uploadOneImage(image, userName, userPassword);

            filesToUpload.removeFirst();

            //qDebug() << " * Nombre de fichiers restant = " << this->filesToUpload.size();
        }
    }
    else // multiupload already started. The method is called as a slot
        emit uploadAlreadyStarted();
}

/**
*	Upload an image to an account
*
*	@param	QString imagePath	the image path
*	@param	QString tags	        image tags
*	@param	QString resizeOption	the resize option,
*					default value is resample
*	@param	QString user		the user ident
*	@param	QString password	    the user password
*	@access	private
*/
void ImageShackUploader::uploadOneImage(ImageShackObject *  image, QString userName, QString userPassword)
{
    QHash<QString, QString> headers;

    //headers["fileupload"] = imageInfos.fileName();
    headers["optsize"]	  = image->getResizeOption();
    headers["optimage"]   = (image->getResizeOption() == "") ? QString("0") : QString("1");
    headers["tags"]       = image->getTags();
    headers["rembar"]	  = (this->removeInformationBar == true) ? QString("yes") : QString("no");
    headers["public"]	  = (image->isPublic()) ? QString("yes") : QString("no");
    headers["key"]        = this->developerKey;
    headers["xml"]	      = QString("yes");

    if(userName != "" )
    {
        headers["a_username"] = userName;
        headers["a_password"] = userPassword;
    }

    sendImage(image,headers);
}

/**
*	Upload an image. This method is called by 
*	userUploadImage and anonymousUploadImage
*	methods	
*
*	@access public
*/
void ImageShackUploader::sendImage(ImageShackObject * imageToUpload ,
                                   QHash<QString, QString>   headers)
{
	QString   imagePath = imageToUpload->getObjectPath();
	QFile     image(imagePath);
	QFileInfo imageInfos(imagePath);

	QNetworkAccessManager * manager = new QNetworkAccessManager;
	QNetworkRequest         request(this->imageUploadUrl);

    QByteArray boundary   = "IMAGESHACKUPLOADER";
    QByteArray cr         = "\r\n";

	QByteArray data;

	if(!image.open(QIODevice::ReadOnly))
	{
		if(uploadAborted==false)
		{
			emit uploadError(ImageShackError::FailedOpeningTheFile);
			this->abortUploads();
		}

		return;
	}

	// build of the header
    data.append("--" + boundary + cr);
    data.append("Content-Disposition: form-data; ");
    data.append( "name=\"fileupload\"; filename=\"" + imageInfos.absoluteFilePath() + "\";" + cr);
    data.append("Content-Type: " + this->mimeType(imagePath) + cr + cr);

	// insertion of the image
    data.append(image.readAll() + cr);

    image.close();

	// build the footer
    QHashIterator<QString, QString> h(headers);
	while (h.hasNext())
	{
	    h.next();

        data.append("--" + boundary + cr);
        data.append("Content-Disposition: form-data; ");
        data.append("name=\"" + h.key() + "\"" + cr + cr);
        data.append(h.value() + cr);
    }

    data.append("--" + boundary + "--" + cr);

	request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data; boundary=" + boundary);
	request.setHeader(QNetworkRequest::ContentLengthHeader, QString::number(data.size()).toAscii());

	// manage proxy
	if(this->proxy != NULL)
		manager->setProxy(*this->proxy);

    this->fileBeingUploaded = imageToUpload;

    //this->uploadsProcessing	   = true;

	timeoutTimer->start(TIMEOUT);

    this->networkReply = manager->post(request, data);

	connect(this->networkReply, SIGNAL(finished())      ,
			this        , SLOT  (imageUploaded()));

	connect(this->networkReply, SIGNAL(error(QNetworkReply::NetworkError))       ,
            this        , SLOT  (manageUploadError(QNetworkReply::NetworkError)));

    connect(this->networkReply, SIGNAL(uploadProgress(qint64,qint64)),
            this	    , SLOT  (manageUploadProgress(qint64,qint64)));

    connect(manager, SIGNAL(authenticationRequired(QNetworkReply*,QAuthenticator*)),
            this   , SLOT  (manageAuthentificationRequired(QNetworkReply*,QAuthenticator*)));

    connect(manager, SIGNAL(proxyAuthenticationRequired(QNetworkProxy,QAuthenticator*)),
            this   , SLOT  (manageProxyAuthentificationRequired(QNetworkProxy,QAuthenticator*)));
}

/**
*	Manage image uploads
*
*	@param  QString fileUploaded	the file uploaded
*	@param	QHash<QString, QString> informations concerning
*								    the uploads
*	@access	private
*/
void ImageShackUploader::manageMultiUploads(ImageShackResponse * uploadResponse)
{
    //qDebug() << " * ManageImageUploads";
    //qDebug() << " * Nombre fichiers restant = " << filesToUpload.size();

    if((this->filesToUpload.size() > 0) && (this->uploadAborted == false))
    {
        //ImageShackObject * file = filesToUpload.takeFirst();
        ImageShackObject * file = (ImageShackObject *) filesToUpload.first();

        //qDebug() << " * Fichier sur le point de partir = " << file->getObjectPath();

		timeoutTimer->stop();

        uploadOneImage(file, this->userName, this->userPassword);

        filesToUpload.removeFirst();

       // qDebug() << " * Nombre de fichiers restant = " << filesToUpload.size();
    }
}

/**
*	Manage replies after the image is uploaded
*
*	@access private	
*/
void ImageShackUploader::imageUploaded()
{
    QHash<QString, QString> usableResponse;
	ImageShackError::UploadError error;

	if(uploadsProcessing)
	{
		usableResponse = ImageShackResponse::makeResponseUsable(this->networkReply);

		//qDebug() << usableResponse;

		if(usableResponse.contains(QString("error")))
		{
			//qDebug() << "* Error in response";
			//this->uploadsProcessing	   = false;

			if(uploadAborted==false)
			{
				error = ImageShackError::getErrorCode(usableResponse);

				if(error != ImageShackError::NoError)
				{
					emit uploadError(error);
				}
					this->abortUploads();
			}
		}
		else
		{
			//qDebug() << "* Image uploadé avec succès : \n " << usableResponse;


			if(uploadAborted==false)
			{
				emit uploadDone(new ImageShackResponse(this->fileBeingUploaded,usableResponse));
				this->nbFilesUploaded ++;
			}

			//qDebug() << "* Nombre de fichiers restant " << filesToUpload.size();

			if(nbFilesUploaded == nbFilesToUploads && uploadAborted == false)
			{
				this->uploadsProcessing	   = false;
				timeoutTimer->stop();
				emit endOfUploads();
			}
		}
	}
}

/**
 * @brief Abort uploads 
 */
void ImageShackUploader::abortUploads()
{
	timeoutTimer->stop();
	this->uploadAborted = true;
	this->uploadsProcessing = false;
	this->networkReply->abort();
}

/**
*	Return the mimeType list
*
*	@access private
*/
QHash<QString, QStringList> ImageShackUploader::mimeTypeList()
{
    QHash<QString, QStringList> mimeTypes;
    QStringList jpeg, png, tiff, gif, bmp;

    jpeg << "jpeg"  << "jpg" << "jpe" << "jfif";
    jpeg << "pjpeg" << "pjp";
    png  << "png" ;
    tiff << "tiff" << "tif";
    gif  << "gif";
    bmp  << "bmp";

    mimeTypes["image/jpeg"] = jpeg;
    mimeTypes["image/png"]  = png ;
    mimeTypes["image/tiff"] = tiff;
    mimeTypes["image/gif"]  = gif;
    mimeTypes["image/bmp"]  = bmp;

    return mimeTypes;
}

/**
*	Return the mimetype basing on the file extension
*	By default, the mimetype returns is image/jpeg
*
*	@return QString the mimetype
*	@access private
*/
QString ImageShackUploader::mimeType(QString imagePath)
{
    QFileInfo imageInfos(imagePath);

    QHashIterator<QString, QStringList> h(this->mimeTypeList());

    while (h.hasNext())
    {
        h.next();

        if(h.value().contains(imageInfos.suffix()))
            return h.key();
    }

    return QString("image/jpeg");
}

/**
*	manage authentification requirements
*
**/
void ImageShackUploader::manageAuthentificationRequired(QNetworkReply  * reply,
                                                        QAuthenticator * authentificator)
{
	if(uploadAborted==false)
	{
		emit authentificationRequired(reply,authentificator);
		this->abortUploads();
	}
}

/**
*	manage proxy authentification requirements
*
**/
void ImageShackUploader::manageProxyAuthentificationRequired(const QNetworkProxy & proxy,
                                                             QAuthenticator      * authenticator)
{
	if(uploadAborted==false)
	{
		emit proxyAuthentificationRequired(proxy,authenticator);
		this->abortUploads();
	}
}

/**
*	Manage upload errors 
*
*	@access private	
*/
void ImageShackUploader::manageUploadError(QNetworkReply::NetworkError errorCode)
{
    //qDebug() << "Error : " << errorCode;
	ImageShackError::UploadError error;

	if(uploadAborted==false)
	{
		error = ImageShackError::getErrorCode(errorCode);

		if(error != ImageShackError::NoError)
		{
			emit uploadError(error);
			this->abortUploads();
		}
	}
}

/**
*	Manage the upload progression
*
*	@access private
**/
void ImageShackUploader::manageUploadProgress(qint64 bytesReceived,qint64 bytesTotal)
{
    //qDebug() << this->fileBeingUploaded->getObjectPath() << " Uploading " << bytesReceived << "/"<< bytesTotal;

	if(uploadAborted==false)
	{
		timeoutTimer->start(TIMEOUT);
		emit uploadProgress(this->fileBeingUploaded,bytesReceived,bytesTotal);
	}
}

/**
* @brief slot handling time out
*/
void ImageShackUploader::handleTimeOut()
{
	if(uploadAborted==false)
	{
		emit uploadError(ImageShackError::TimeoutError);	
		this->abortUploads();
	}
}

/**
* @brief return true if uploads are in progress
*
* @return true/false in uploads are in progress 
*/
bool ImageShackUploader::uploadsInProgress()
{
	return uploadsProcessing;
}

/**
*	set proxy variable to NULL in order to not
*	use any proxy when uploading
*
*	@access public	
*/
void ImageShackUploader::noProxy()
{
	this->proxy = NULL;
}

/**----------
*	Getters and Setters
**----------*/

/**
*	the getter of the boolean removeInformationBar	
*		
*	@return removeInformationBar
*	@access public	
*/
bool ImageShackUploader::getRemoveInformationBar()
{
	return this->removeInformationBar;
}


/**
*	the getter of the proxy
*
*	@return * QNetworkProxy
*	@access	  public
*/
QNetworkProxy * ImageShackUploader::getProxy()
{
	return this->proxy;
}

/**
*	the getter of developerKey 
*		
*	@return developerKey
*	@access public	
*/
QString ImageShackUploader::getDeveloperKey()
{
	return this->developerKey;
}

/**
*	the getter of imageUploadUrl
*		
*	@return developerKey
*	@access public	
*/
QString ImageShackUploader::getImageUploadUrl()
{
	return this->imageUploadUrl;
}

/**
*	the getter of userName
*
*	@return developerKey
*	@access public
*/
QString ImageShackUploader::getLastUserName()
{
    return this->userName;
}

/**
*	the setter of developerKey
*		
*	@param	   developerKey		The developer key needed to upload
*								to unified ImageShack API
*	@access	   public	
*/
void ImageShackUploader::setDeveloperKey(QString developerKey)
{
	this->developerKey = developerKey;
}

/**
*	the setter of imageUploadUrl
*		
*	@param  developerKey	The entry point to upload 
*							images to ImageShack
*	@access	public	
*/
void ImageShackUploader::setImageUploadUrl(QString imageUploadUrl)
{
	this->imageUploadUrl = imageUploadUrl;
}

/**
*	the setter of the proxy use to upload
*
*	@param  QNetworkProxy	the proxy to use
* 	@access public
*/
void ImageShackUploader::setProxy(QNetworkProxy * proxy)
{
	this->proxy = proxy;
}

/**
*	the setter of imageEntryUpload 
*		
*	@param	removeInformationBar	 the boolean to remove/leave 
*			    					 the information bar from
*			 	     				 thumbnails
*	@access	public				 
*/
void ImageShackUploader::setRemoveInformationBar(bool removeInformationBar)
{
	this->removeInformationBar = removeInformationBar;
}
