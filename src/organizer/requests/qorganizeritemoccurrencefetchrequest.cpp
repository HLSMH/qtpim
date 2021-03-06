/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtOrganizer module of the Qt Toolkit.
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

#include "qorganizeritemoccurrencefetchrequest.h"

#include "qorganizeritemrequests_p.h"

QT_BEGIN_NAMESPACE_ORGANIZER

/*!
    \class QOrganizerItemOccurrenceFetchRequest
    \brief The QOrganizerItemOccurrenceFetchRequest class allows a client to asynchronously fetch
           occurrences generated by a recurring item.
    \inmodule QtOrganizer
    \ingroup organizer-requests

    This request will fetch both generated occurrences and persisted occurrences, which match the
    specified criteria, of the given parent item.
 */

/*!
    Constructs a new organizer item occurrence fetch request whose parent is the specified \a parent.
*/
QOrganizerItemOccurrenceFetchRequest::QOrganizerItemOccurrenceFetchRequest(QObject *parent)
    : QOrganizerAbstractRequest(new QOrganizerItemOccurrenceFetchRequestPrivate, parent)
{
}

/*!
    Frees memory in use by this request.
*/
QOrganizerItemOccurrenceFetchRequest::~QOrganizerItemOccurrenceFetchRequest()
{
}

/*!
    Sets the parent item, whose occurrences are to be fetched to \a item.
*/
void QOrganizerItemOccurrenceFetchRequest::setParentItem(const QOrganizerItem &item)
{
    Q_D(QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_generator = item;
}

/*!
    Sets the start period of the request to \a date.

    A default-constructed (invalid) start date time specifies an open start date time (matches anything
    which occurs up until the end date time).
*/
void QOrganizerItemOccurrenceFetchRequest::setStartDate(const QDateTime &date)
{
    Q_D(QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_startDate = date;
}

/*!
    Sets the end period of the request to \a date.

    A default-constructed (invalid) end date time specifies an open end date time (matches anything
    which occurs after the start date time).
*/
void QOrganizerItemOccurrenceFetchRequest::setEndDate(const QDateTime &date)
{
    Q_D(QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_endDate = date;
}

/*!
    Sets the maximum number of occurrences to fetch to \a maxCount.

    Note that backends will decide how many items are fetched if \a maxCount is negative.
 */
void QOrganizerItemOccurrenceFetchRequest::setMaxOccurrences(int maxCount)
{
    Q_D(QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_maxOccurrences = maxCount;
}

/*!
    Sets the fetch hint which may be used by the backend to optimize item retrieval to \a fetchHint.

    A client should not make changes to a item which has been retrieved using a fetch hint other than
    the default fetch hint.  Doing so will result in information loss when saving the item back to
    the manager (as the "new" restricted item will replace the previously saved item in the backend).
 */
void QOrganizerItemOccurrenceFetchRequest::setFetchHint(const QOrganizerItemFetchHint &fetchHint)
{
    Q_D(QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    d->m_fetchHint = fetchHint;
}

/*!
    Returns the parent item, whose occurrences are to be fetched.
*/
QOrganizerItem QOrganizerItemOccurrenceFetchRequest::parentItem() const
{
    Q_D(const QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_generator;
}

/*!
    Returns the date-time which is the lower bound for the range in which occurrences will be returned.
 */
QDateTime QOrganizerItemOccurrenceFetchRequest::startDate() const
{
    Q_D(const QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_startDate;
}

/*!
    Returns the date-time which is the upper bound for the range in which occurrences will be returned.
 */
QDateTime QOrganizerItemOccurrenceFetchRequest::endDate() const
{
    Q_D(const QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_endDate;
}

/*!
    Returns the maximum number of occurrences to return for the request.
 */
int QOrganizerItemOccurrenceFetchRequest::maxOccurrences() const
{
    Q_D(const QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_maxOccurrences;
}

/*!
    Returns the list of organizer item occurrences retrieved by this request.
*/
QList<QOrganizerItem> QOrganizerItemOccurrenceFetchRequest::itemOccurrences() const
{
    Q_D(const QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_organizeritems;
}

/*!
    Returns the fetch hint which may be used by the backend to optimize item retrieval.

    A client should not make changes to a item which has been retrieved using a fetch hint other than
    the default fetch hint.  Doing so will result in information loss when saving the item back to
    the manager (as the "new" restricted item will replace the previously saved item in the backend).
 */
QOrganizerItemFetchHint QOrganizerItemOccurrenceFetchRequest::fetchHint() const
{
    Q_D(const QOrganizerItemOccurrenceFetchRequest);
    QMutexLocker ml(&d->m_mutex);
    return d->m_fetchHint;
}

QT_END_NAMESPACE_ORGANIZER

#include "moc_qorganizeritemoccurrencefetchrequest.cpp"
