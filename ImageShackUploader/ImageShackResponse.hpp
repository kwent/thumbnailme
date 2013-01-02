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
#ifndef  HEADER_IMAGESHACKRESPONSE
#define  HEADER_IMAGESHACKRESPONSE

#include <QByteArray>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QHash>
#include <QHashIterator>
#include <QNetworkReply>
#include <QString>
#include <QWidget>

#include "ImageShackObject.hpp"

/**
* 	ImageShackUploader class
*
*	@author Christ Azika-Eros <christ@azika-eros.org>
**/
class ImageShackResponse : public QObject
{
    Q_OBJECT

    public  : // variables, enums

            /**
            *	Enumeration specifing the type of uploads :
            *	IMAGE or VIDEO
            **/
            enum UploadType{IMAGE,VIDEO};

    public : // public method

            /**
            *	Constructor with parameters
            *
            *	@param	ImageShackObject * fileUploaded - the file uploaded
            *	@param  ImageShackResponse              - imageShack response
            **/
            ImageShackResponse(ImageShackObject  *     fileUploaded       ,
                               QHash<QString, QString> imageShackResponse);

            ~ImageShackResponse();
            /**
            *	@brief  Return a QHash containing ImageShack replies
            *			(imageLink..)
            *
            *	@param  const QByteArray * response the reply after
            *								        the upload
            *	@return a QHash<QString, QString> containing ImageShack
            *			answer
            **/
            static QHash<QString, QString> makeResponseUsable(QByteArray response);
            
            /**
            *	@brief  Return a QHash containing ImageShack replies
            *			(imageUrl...)
            *
            *	@param  const QNetworkReply * response the reply after
            *								           the upload
            *	@param  UploadType uploadType	    the type of the upload
            *	@return a QHash<QString, QString> containing ImageShack
            **/
            static QHash<QString, QString> makeResponseUsable(QNetworkReply * response);

    private : // Private objects or variables

            /**
            *   ImageShackObject *  fileUploaded - the file uploaded
            **/
            ImageShackObject *  fileUploaded;

            /**
            * 	QHash<QString, QString> imageShackResponse - imageShack response
            **/
            QHash<QString, QString> imageShackResponse;

    public  : // Setters and Getters

            /**
            *	the getter of the attribut fileUploaded
            *
            *	@return ImageShackObject * the file uploaded
            */
            ImageShackObject * getFileUploaded();

            /**
            *	the getter of the attribut ImageShackResponse
            *
            *	@return QHash<QString, QString> the imageShack response
            */
            QHash<QString, QString> getImageShackResponse();

            /**
            *	the setter of the attribut fileUploaded
            *
            *	@param ImageShackObject * fileUploaded - the file uploaded
            */
            void setFileUploaded(ImageShackObject * fileUploaded);

            /**
            *	the setter of the attribut ImageShackResponse
            *
            *	@param  QHash<QString,QString> imageShackResponse - imageShackResponse response
            */
            void setImageShackResponse(QHash<QString, QString> imageShackResponse);
};

#endif
