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
#ifndef HEADER_IMAGESHACKOBJECT
#define HEADER_IMAGESHACKOBJECT

#include <QDebug>
#include <QHash>
#include <QHashIterator>
#include <QString>
#include <QWidget>

/**
* 	ImageShackObbject class
*
*	@author Christ Azika-Eros <christ@azika-eros.org>
**/
class ImageShackObject : public QObject
{
    Q_OBJECT

    private : // variables, enums

            /**
            *	the object path
            *
            **/
            QString objectPath;

            /**
            *	comma-separeted list of tags related to the image/video to upload
            *
            **/
            QString tags;

            /**
            *	resize options for image : WxH , exp : "100x100"
            *	no impact on video uploads
            **/
            QString resizeOption;

			/**
			*	if true, the video/picture will be publici (default).
			*   false means private	
			**/
			bool publicObject;

    public : // Public methods

            /**
            *	Constructor
            *
            *	QString imagePath		the object path
            *	QString tags			comma-separeted list of tags related
            *							to the image/video to upload
            *	QString resizeOption    resize option for image, no impact on video
            **/
            ImageShackObject(QString objectPath                 ,
                             QString tags         = ""          ,
							 bool    publicObject = true        ,
                             QString resizeOption = "resample" );

            /**
            *	Constructor
            *
            *	QString imagePath		the object path
            *	QString tags			comma-separeted list of tags related
            *							to the image/video to upload
            *	QString resizeOption    resize option for image, no impact on video
            **/
            ImageShackObject(QString     objectPath                 ,
                             QStringList tags                       ,
							 bool        publicObject       = true  ,
                             QString     resizeOption = "resample" );


            /**
            * 	Destructor
            *
            **/
            ~ImageShackObject(void);
    public : // getters and setters

            /**
            *	Getter of objectPath attribute
            *
            **/
            QString getObjectPath();

            /**
            *	Getter of resizeOption attribute
            *
            **/
            QString getResizeOption();

			/**
			*	Getter of publicObject attribute
			*	@return bool publicObject attribute 
			**/
            QString getTags();


			/**
			*	Getter of 
			*
			**/
			bool isPublic();


            /**
            *	Setter of objectPath attribute
            *
            **/
            void setObjectPath(QString  objectPath);

			/**
			*
			*	Setter of publicObject attribute
			**/
			void setPublic(bool publicObject);

            /**
            *	Setter of tags attribute
            *
            **/
            void setTags(QString tags);

            /**
            *	Setter of tags attribute
            *
            **/
            void setTags(QStringList tags);

            /**
            *	Setter of resizeOption attribute
            *
            **/
            void setResizeOption(QString resizeOption);
};

#endif // HEADER_IMAGESHACKOBJECT
