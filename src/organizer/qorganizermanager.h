/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/


#ifndef QORGANIZERMANAGER_H
#define QORGANIZERMANAGER_H

#include <QObject>

#include <QMap>
#include <QString>
#include <QStringList>
#include <QList>
#include <QDateTime>

#include "qorganizerglobal.h"
#include "qorganizeritem.h"
#include "qorganizeritemid.h"
#include "qorganizeritemsortorder.h"
#include "qorganizeritemfetchhint.h"
#include "qorganizeritemfilter.h"

#include "qorganizercollection.h"
#include "qorganizercollectionid.h"

QTORGANIZER_BEGIN_NAMESPACE

class QOrganizerManagerData;

class Q_ORGANIZER_EXPORT QOrganizerManager : public QObject
{
    Q_OBJECT

public:
#if Q_QDOC // qdoc's parser fails to recognise the default map argument
    explicit QOrganizerManager(const QString& managerName = QString(), const QMap<QString, QString>& parameters = 0, QObject* parent = 0);
    QOrganizerManager(const QString& managerName, int implementationVersion, const QMap<QString, QString>& parameters = 0, QObject* parent = 0);
#else
    explicit QOrganizerManager(const QString& managerName = QString(), const QMap<QString, QString>& parameters = (QMap<QString, QString>()), QObject* parent = 0);
    QOrganizerManager(const QString& managerName, int implementationVersion, const QMap<QString, QString>& parameters = (QMap<QString, QString>()), QObject* parent = 0);
#endif
    explicit QOrganizerManager(QObject* parent);

    static QOrganizerManager* fromUri(const QString& uri, QObject* parent = 0);
    ~QOrganizerManager();

    QString managerName() const;                       // e.g. "Symbian"
    QMap<QString, QString> managerParameters() const;  // e.g. "filename=private.db"
    QString managerUri() const;                        // managerName + managerParameters
    int managerVersion() const;

    static bool parseUri(const QString& uri, QString* managerName, QMap<QString, QString>* params); // replaces the above.
    static QString buildUri(const QString& managerName, const QMap<QString, QString>& params, int implementationVersion = -1);

    // error reporting
    enum Error {
        NoError = 0,
        DoesNotExistError,
        AlreadyExistsError,
        InvalidDetailError,
        LockedError,
        DetailAccessError,
        PermissionsError,
        OutOfMemoryError,
        NotSupportedError,
        BadArgumentError,
        UnspecifiedError,
        VersionMismatchError,
        LimitReachedError,
        InvalidItemTypeError,
        InvalidCollectionError,
        InvalidOccurrenceError,
        TimeoutError
    };

    QOrganizerManager::Error error() const;
    QMap<int, QOrganizerManager::Error> errorMap() const;

    // items
    QOrganizerItem item(const QOrganizerItemId &itemId, const QOrganizerItemFetchHint &fetchHint = QOrganizerItemFetchHint());

    QList<QOrganizerItem> items(const QList<QOrganizerItemId> &itemIds, const QOrganizerItemFetchHint &fetchHint = QOrganizerItemFetchHint());

    QList<QOrganizerItem> items(const QOrganizerItemFilter &filter = QOrganizerItemFilter(),
                                const QDateTime &startDateTime = QDateTime(), const QDateTime &endDateTime = QDateTime(), int maxCount = -1,
                                const QList<QOrganizerItemSortOrder> &sortOrders = QList<QOrganizerItemSortOrder>(),
                                const QOrganizerItemFetchHint &fetchHint = QOrganizerItemFetchHint());

    QList<QOrganizerItemId> itemIds(const QOrganizerItemFilter &filter = QOrganizerItemFilter(),
                                    const QDateTime &startDateTime = QDateTime(), const QDateTime &endDateTime = QDateTime(),
                                    const QList<QOrganizerItemSortOrder> &sortOrders = QList<QOrganizerItemSortOrder>());

    QList<QOrganizerItem> itemOccurrences(const QOrganizerItem &parentItem, const QDateTime &startDateTime = QDateTime(),
                                          const QDateTime &endDateTime = QDateTime(), int maxCount = -1,
                                          const QOrganizerItemFetchHint &fetchHint = QOrganizerItemFetchHint());

    QList<QOrganizerItem> itemsForExport(const QDateTime &startDateTime = QDateTime(), const QDateTime &endDateTime = QDateTime(),
                                         const QOrganizerItemFilter &filter = QOrganizerItemFilter(),
                                         const QList<QOrganizerItemSortOrder> &sortOrders = QList<QOrganizerItemSortOrder>(),
                                         const QOrganizerItemFetchHint &fetchHint = QOrganizerItemFetchHint());

    bool saveItem(QOrganizerItem *item, const QList<QOrganizerItemDetail::DetailType> &detailMask = QList<QOrganizerItemDetail::DetailType>());

    bool saveItems(QList<QOrganizerItem> *items,
                   const QList<QOrganizerItemDetail::DetailType> &detailMask = QList<QOrganizerItemDetail::DetailType>());

    bool removeItem(const QOrganizerItemId &itemId);

    bool removeItems(const QList<QOrganizerItemId>& itemIds);

    // collections
    QOrganizerCollection defaultCollection();
    QOrganizerCollection collection(const QOrganizerCollectionId& collectionId);
    QList<QOrganizerCollection> collections();
    bool saveCollection(QOrganizerCollection* collection);
    bool removeCollection(const QOrganizerCollectionId& collectionId);

    /* Functionality reporting */
    QList<QOrganizerItemFilter::FilterType> supportedFilters() const;
    QList<QOrganizerItemDetail::DetailType> supportedItemDetails(QOrganizerItemType::ItemType itemType) const;
    QList<QOrganizerItemType::ItemType> supportedItemTypes() const;

    /* return a list of available backends for which a QOrganizerManager can be constructed. */
    static QStringList availableManagers();

    static QList<QOrganizerItemId> extractIds(const QList<QOrganizerItem>& items);

    // to be removed
    QList<QOrganizerItemId> itemIds(const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders);
    QList<QOrganizerItem> items(const QOrganizerItemFilter& filter, const QList<QOrganizerItemSortOrder>& sortOrders, const QOrganizerItemFetchHint& fetchHint = QOrganizerItemFetchHint());
    QList<QOrganizerItem> items(const QDateTime& startDate, const QDateTime& endDate, const QOrganizerItemFilter& filter = QOrganizerItemFilter(), const QList<QOrganizerItemSortOrder>& sortOrders = QList<QOrganizerItemSortOrder>(), const QOrganizerItemFetchHint& fetchHint = QOrganizerItemFetchHint());
    QList<QOrganizerItem> items(const QDateTime& startDate, const QDateTime& endDate, int maxCount, const QOrganizerItemFilter& filter = QOrganizerItemFilter(), const QOrganizerItemFetchHint& fetchHint = QOrganizerItemFetchHint());

Q_SIGNALS:
    void dataChanged();
    void itemsAdded(const QList<QOrganizerItemId>& itemIds);
    void itemsChanged(const QList<QOrganizerItemId>& itemIds);
    void itemsRemoved(const QList<QOrganizerItemId>& itemIds);
    void collectionsAdded(const QList<QOrganizerCollectionId>& collectionIds);
    void collectionsChanged(const QList<QOrganizerCollectionId>& collectionIds);
    void collectionsRemoved(const QList<QOrganizerCollectionId>& collectionIds);

private:
    friend class QOrganizerManagerData;
    void createEngine(const QString& managerName, const QMap<QString, QString>& parameters);
    Q_DISABLE_COPY(QOrganizerManager)

    Q_PRIVATE_SLOT(d, void _q_itemsUpdated(const QList<QOrganizerItemId>& ids))
    Q_PRIVATE_SLOT(d, void _q_itemsDeleted(const QList<QOrganizerItemId>& ids))

    // private data pointer
    QOrganizerManagerData* d;
};

QTORGANIZER_END_NAMESPACE

#endif
