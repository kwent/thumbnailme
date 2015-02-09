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
#include "ImageShackResponse.hpp"

/**
*	Constructor with parameters
*
*	@param	ImageShackObject * fileUploaded - the file uploaded
*	@param  ImageShackResponse              - imageShack response
**/
ImageShackResponse::ImageShackResponse(ImageShackObject  *     fileUploaded      ,
                                       QHash<QString, QString> imageShackResponse)
{
    this->fileUploaded       = fileUploaded;
    this->imageShackResponse = imageShackResponse;
}

ImageShackResponse::~ImageShackResponse()
{
}

/**
*	@brief  Return a QHash containing ImageShack replies
*			(imageUrl...)
*
*	@param  const QByteArray * response the reply after
*	@return a QHash<QString, QString> containing ImageShack
*			answer
*	@access static
**/
QHash<QString, QString> ImageShackResponse::makeResponseUsable(QByteArray response)
{
	//qDebug() << response;

    QHash<QString, QString> hashResponse;
    QHash<QString, QStringList> rootAndSubTags;
    QStringList resolutions, uploader, links;

    resolutions    << "width"       << "height" ;
    uploader       << "ip"          << "cookie"     << "username"   ;
    links   	   << "image_link"  << "image_html" << "image_bb"   ;
    links          << "image_bb2"   << "thumb_link" << "thumb_html" ;
    links          << "thumb_bb"    << "thumb_bb2"  << "yfrog_link" ;
    links          << "yfrog_thumb" << "ad_link"    << "done_page"  ;

    rootAndSubTags["resolution"] = resolutions;
    rootAndSubTags["uploader"]   = uploader;
    rootAndSubTags["links"]      = links;


    QDomDocument xmlResponse;
    xmlResponse.setContent(response);

    QDomElement rootTag = xmlResponse.documentElement();
    if(rootTag.isNull())
    {
        hashResponse["error"] = "Response unusable : the root tag imginfo is absent";
        return hashResponse;
    }

    QDomElement errorTag = rootTag.firstChildElement("error");
    if(!errorTag.isNull())
    {
        hashResponse["error"] = errorTag.text();
        return hashResponse;
    }

    QHashIterator<QString, QStringList> cursor(rootAndSubTags);

    while (cursor.hasNext())
    {
        cursor.next();

        // The tag can't be absent
        QDomElement subRootTag = rootTag.firstChildElement(cursor.key());
        if(subRootTag.isNull())
        {
            hashResponse["error"] = "Response unusable : the tag "+ cursor.key()+" is absent";
            return hashResponse;
        }

        foreach(QString tag, cursor.value())
        {   // Some tags like the user, and the cookie can be absent
            if(!subRootTag.firstChildElement(tag).isNull())
                hashResponse[tag] = subRootTag.firstChildElement(tag).text();
        }
    }

    return hashResponse;
}

/**
*	@brief  Return a QHash containing ImageShack replies
*			(imageLink...)
*
*	@param  const QNetworkReply * response the reply after
*								           the upload
*	@return a QHash<QString, QString> containing ImageShack
*			answer
*	@access static
**/
QHash<QString, QString> ImageShackResponse::makeResponseUsable(QNetworkReply * response)
{
    QByteArray datas = response->readAll();

    return makeResponseUsable(datas);
}

/**----------
*	Getters and Setters
**----------*/

/**
*	the getter of the attribut fileUploaded
*
*	@return ImageShackObject * the file uploaded
*/
ImageShackObject * ImageShackResponse::getFileUploaded()
{
    return this->fileUploaded;
}

/**
*	the getter of the attribut ImageShackResponse
*
*	@return QHash<QString, QString> the imageShack response
*/
QHash<QString, QString> ImageShackResponse::getImageShackResponse()
{
    return this->imageShackResponse;
}

/**
*	the setter of the attribut fileUploaded
*
*	@param ImageShackObject * fileUploaded - the file uploaded
*/
void ImageShackResponse::setFileUploaded(ImageShackObject * fileUploaded)
{
    this->fileUploaded = fileUploaded;
}

/**
*	the setter of the attribut ImageShackResponse
*
*	@param  QHash<QString,QString> imageShackResponse - imageShackResponse response
*/
void ImageShackResponse::setImageShackResponse(QHash<QString, QString> imageShackResponse)
{
    this->imageShackResponse = imageShackResponse;
}
