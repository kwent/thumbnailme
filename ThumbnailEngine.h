/***************************************************************************//**
*	@brief Thumbnail me 3.0
*	Thumbnail me is a user interface for Movie thumbnailer.
* 	Generate thumbnails from any movie is now easier !
*
*	@file	ThumbnailEngine.h
*       @class  ThumbnailEngine
*	Cette classe est le moteur de ThumbnailMe, c'est dans cette classe que le processus est exécuté.
*
*	@author Quentin Rousseau\n
*	@note   Copyright (C) 2011-2012 Quentin Rousseau\n
*               License: GNU General Public License version 2 (GPLv2) - http://www.gnu.org/licenses/gpl-2.0.html\n
*               Site web: www.thumbnailme.com\n
*               Email: quentin.rousseau@thumbnailme.com
*
*       @since      3.0
*	@version    3.0
*       @date       2011-2012
*******************************************************************************/

#ifndef HEADER_THUMBNAILENGINE
#define HEADER_THUMBNAILENGINE

#include <QObject>
#include <QSettings>
#include <QProcess>
#include <QSignalMapper>
#include <QLinkedList>
#include <QThreadPool>

class MainWindow;
class ThumbnailItem;


class ThumbnailEngine : public QObject
{
    Q_OBJECT

    public:
    /**
    * SIMPLEMOD:          Conversion simple.\n
    * PREVIEWMOD:         Preview.
    */
    enum Mode
    {
        SIMPLEMOD,
        PREVIEWMOD
    };

    public:
    explicit ThumbnailEngine(MainWindow *main_window);
    virtual ~ThumbnailEngine();

    private:
    MainWindow    *main_window;
    QSettings	  *settings;

    QLinkedList <ThumbnailItem*> listInputFile;
    QThreadPool *pool;
    QProcess                     *process;
    QImage                       *img;
    QStringList                  currentOutput;
    ThumbnailItem                *currentItem;
    int                          current;
    QSignalMapper                *convertSignalMapper;
    Mode                         modeConversion;

    private:
    void launchProcess(QLinkedList <ThumbnailItem*> listInputFile);

    private slots:
    void convertToFormat(QObject *o);
    void initSuccessDialog(QLinkedList <ThumbnailItem*> listInputFile);
    void start(int exitCode, QProcess::ExitStatus exitStatus);
    void success();

    public:
    QString  absoluteFilePathOutput(QString pathOutput, QString absoluteOutputPath,QString suffix,QString format = QString());
    bool     isBinaryExists();
    Mode     mode() const;
    void     setMode(Mode mode);

    public slots:
    void buildOutput();
    void deleteTemporaryFiles();
    void detectShortDuration();
    void run(int mode);
    void successDialogItemRemove(ThumbnailItem *item);

    signals:
    /**
    *@brief Lève le signal lorsque la durée de l'item est trop court.
    *@param item - Thumbnail item.
    */
    void itemTooShortDuration(ThumbnailItem *item);
};

#endif // HEADER_THUMBNAILENGINE
