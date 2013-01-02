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
#include "ImageShackObject.hpp"

/**
*	Constructor
*
*	QString imagePath		the object path
*	QString tags			comma-separeted list of tags related
*							to the image/video to upload
*	QString resizeOption    resize option for image, no impact on video
**/
ImageShackObject::ImageShackObject(QString objectPath   ,
                                   QString tags         ,
								   bool    publicObject       ,
                                   QString resizeOption )
{
    this->objectPath   = objectPath;
	this->publicObject = publicObject;
    this->tags         = tags;
    this->resizeOption = resizeOption;
}

/**
*	Constructor
*
*	QString imagePath		the object path
*	QString tags			comma-separeted list of tags related
*							to the image/video to upload
*	QString resizeOption    resize option for image, no impact on video
**/
ImageShackObject::ImageShackObject(QString     objectPath   ,
                                   QStringList tags         ,
								   bool        publicObject ,
                                   QString     resizeOption )
{
    this->objectPath   = objectPath;
	this->publicObject = publicObject;
    this->resizeOption = resizeOption;
    this->tags         = tags.join(",");
}

/**
* 	Destructor
*
**/
ImageShackObject::~ImageShackObject(void)
{

}

/**----------
*	Getters and Setters
**----------*/

/**
*	Getter of objectPath attribute
*
**/
QString ImageShackObject::getObjectPath()
{
    return this->objectPath;
}

/**
*	Getter of resizeOption attribute
*
**/
QString ImageShackObject::getResizeOption()
{
    return this->resizeOption;
}

/**
*	Getter of tags attribute
*
**/
QString ImageShackObject::getTags()
{
    return this->tags;
}

/**
*	Getter of publicObject attribute
*	@return bool publicObject attribute 
**/
bool ImageShackObject::isPublic()
{
	return this->publicObject;
}

/**
*	Setter of objectPath attribute
*
**/
void ImageShackObject::setObjectPath(QString  objectPath)
{
    this->objectPath = objectPath;
}

/**
*
*	Setter of publicObject attribute
**/
void ImageShackObject::setPublic(bool publicObject)
{
	this->publicObject = publicObject;
}

/**
*	Setter of tags attribute
*
**/
void ImageShackObject::setTags(QString tags)
{
    this->tags = tags;
}

/**
*	Setter of tags attribute
*
**/
void ImageShackObject::setTags(QStringList tags)
{
    this->tags = tags.join(",");
}

/**
*	Setter of resizeOption attribute
*
**/
void ImageShackObject::setResizeOption(QString resizeOption)
{
    this->resizeOption = resizeOption;
}
