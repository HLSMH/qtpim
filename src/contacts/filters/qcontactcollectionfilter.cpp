/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtContacts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qcontactcollectionfilter.h"
#include "qcontactcollectionfilter_p.h"

QT_BEGIN_NAMESPACE_CONTACTS

/*!
    \class QContactCollectionFilter
    \brief The QContactCollectionFilter class provides a filter based around the collection one
           contact belongs to.
    \inmodule QtContacts
    \ingroup contacts-filters

    It may be used to select contacts belonging to certain collections.
 */

Q_IMPLEMENT_CONTACTFILTER_PRIVATE(QContactCollectionFilter)

/*!
    \fn QContactCollectionFilter::QContactCollectionFilter(const QContactCollectionFilter &other)

    Constructs a copy of \a other if possible, otherwise constructs a new contact collection filter.
 */

/*!
    Constructs a new contact collection filter.
 */
QContactCollectionFilter::QContactCollectionFilter()
    : QContactFilter(new QContactCollectionFilterPrivate)
{
}

/*!
    Sets the \a id of the collection, which the contacts should belong to.
 */
void QContactCollectionFilter::setCollectionId(const QContactCollectionId &id)
{
    Q_D(QContactCollectionFilter);
    d->m_ids.clear();
    d->m_ids.insert(id);
}

/*!
    Sets the list of collection \a ids, which the contacts should belong to.
 */
void QContactCollectionFilter::setCollectionIds(const QSet<QContactCollectionId> &ids)
{
    Q_D(QContactCollectionFilter);
    d->m_ids = ids;
}

/*!
    Returns the list of collection IDs of contacts should belong to.
 */
QSet<QContactCollectionId> QContactCollectionFilter::collectionIds() const
{
    Q_D(const QContactCollectionFilter);
    return d->m_ids;
}

QT_END_NAMESPACE_CONTACTS
