#include "QtHelper.h"

/**
*@brief Centre au milieu de l'écran le widget passé en paramètre.
*@param *widgetToMove    Pointeur du widget à centrer.
*/
void QtHelper::centerWidget(QWidget *widgetToMove)
{
    widgetToMove->adjustSize();
    widgetToMove->move(QApplication::desktop()->screenGeometry(QApplication::desktop()->primaryScreen()).center() - widgetToMove->rect().center());
}

/**
*@brief  Construit un séparateur horizontal.
*@return QFrame* - Pointeur vers le nouveau séparateur horizontal.
*/
QFrame* QtHelper::addHSeparator()
{
    QFrame * f = new QFrame;
    f->setFrameShape(QFrame::HLine);
    f->setFrameShadow(QFrame::Sunken);
    return f;
}

/**
*@brief  Construit un séparateur vertical.
*@return QFrame* - Pointeur vers le nouveau séparateur vertical.
*/
QFrame* QtHelper::addVSeparator()
{
    QFrame * f = new QFrame;
    f->setFrameShape(QFrame::VLine);
    f->setFrameShadow(QFrame::Sunken);
    return f;
}

/**
*@brief  Retourne tous les items d'une QListWidget.
*@param  *listwidget Pointeur vers le QListWidget.
*@return QStringList - Liste des items.
*/
QStringList QtHelper::getItemsListWidget(QListWidget *listWidget)
{
    QStringList listeItems;

    for(int i = 0 ; i < listWidget->count() ; i++)
        listeItems << listWidget->item(i)->text();

    return listeItems;
}

/**
*@brief  Retourne tous les items dans l'état Checkstate d'une QListWidget.
*@param  *listwidget Pointeur vers le QListWidget.
*@return QStringList - Liste des items.
*/
QStringList QtHelper::getItemsListWidget(QListWidget *listWidget, Qt::CheckState state)
{
    QStringList listeItems;

    for(int i = 0 ; i < listWidget->count() ; i++)
        if(listWidget->item(i)->checkState() == state)
            listeItems << listWidget->item(i)->text();

    return listeItems;
}

/**
*@brief  Retire les items sélectionnés d'une QListWidget.
*@param  *listwidget Pointeur vers le QListWidget.
*@return Faux si aucun item est séléctionné.
*/
bool QtHelper::removeSelectedItems(QListWidget *listWidget)
{
    QList <QListWidgetItem *> selectedFiles= listWidget->selectedItems();

    if(selectedFiles.size())
    {
            foreach(QListWidgetItem *i, selectedFiles)
            {
                    delete i;
            }
    return true;
    }
    else return false;
}

/**
* @brief  Convertie un QColor en un code couleur hexadécimal sans "#".
* @param  color    Couleur à convertir.
* @return QString - Code hexadécimal sans "#".
*/
QString QtHelper::qColor2rgbNoSharp(QColor color)
{
    return color.name().remove(QChar('#'), Qt::CaseInsensitive);
}

///**
//* @brief  Convertie un QColor en struct rgb_color
//* @param  color    Couleur à convertir.
//* @return rgb_color - Struct.
//*/
//rgb_color QtHelper::qColor2RGB(QColor color)
//{
//    rgb_color a;
//    a.b = color.blue();
//    a.r = color.red();
//    a.g = color.green();
//    return a;
//}

/**
* @brief  Convertie un code couleur hexadécimal sans "#" en QColor.
* @param  rgbNoSharp  Code couleur hexadécimal sans "#".
* @return QColor - Couleur.
*/
QColor QtHelper::rgbNoSharp2qColor(QString rgbNoSharp)
{
    return QColor("#"+rgbNoSharp);
}

/**
* @brief  Convertie des millisecondes en format h:m:s.
* @param  msecs  Millisecondes.
* @return QString - Format h:m:s.
*/
QString QtHelper::msecs2Hmn(qint64 msecs)
{
    QTime time;
    time = time.addMSecs(msecs);
    return time.toString(Qt::TextDate);
}

/**
* @brief  Convertie des millisecondes en format h:m:s.
* @param  secs  Secondes.
* @return QString - Format h:m:s.
*/
QString QtHelper::secs2Hmn(int secs)
{
    QTime time;
    time = time.addSecs(secs);
    return time.toString(Qt::TextDate);
}

/**
*@brief  Scanne les polices (TrueType Font) d'un dossier.
*@param  path    Chemin du dossier à scanner.
*@return QMap<QString,QString> - Tableau contenant les noms des polices (TrueType Font) et leurs chemins. Retourne une liste vide si aucune police trouvée.
*/
QMap <QString,QString> QtHelper::exploreTTFDir(QStringList dirPath)
{
        QMap <QString,QString> hash;
        QFontDatabase fontsDatabase;
        QDir fontsFolder;
            fontsFolder.setNameFilters(QStringList("*.ttf"));

        for(int i=0;i < dirPath.count();i++)
        {
            fontsFolder.setPath(dirPath.at(i));

            foreach(QFileInfo fontname, fontsFolder.entryInfoList(QDir::Files,QDir::IgnoreCase | QDir::Name))
            {
                int i = fontsDatabase.addApplicationFont(fontname.absoluteFilePath());
                hash.insert(fontsDatabase.applicationFontFamilies(i).first(),fontname.absoluteFilePath());
                QCoreApplication::processEvents();
            }
        QCoreApplication::processEvents();
        }
        return hash;
}

/**
*@brief  Lit les chemins de police contenus dans le fichier de configuration.
*@return QStringList - Liste des chemins lus.
*/
QStringList QtHelper::readPathsFontsValueIni(QSettings *settings)
{
        settings->sync();
        settings->beginGroup("Font_Paths");
        QStringList current_child = settings->childKeys();
        QStringList current_path;

        for(int i= 0;i < settings->childKeys().count();i++)
        {
                if(QFile::exists(settings->value(current_child.at(i)).toString()))
                    current_path << settings->value(current_child.at(i)).toString();
                else settings->remove(current_child.at(i));
        }

        settings->endGroup();
        return current_path;
}
