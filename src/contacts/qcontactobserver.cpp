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

#include "qcontactobserver.h"

#include <QtCore/qpointer.h>

#include "qcontactmanager.h"
#include "qcontactmanager_p.h"

QT_BEGIN_NAMESPACE_CONTACTS

class QContactObserverPrivate
{
    public:
        QContactId m_contactId;
        QPointer<QContactManager> m_manager;
};

/*!
  \class QContactObserver
  \brief The QContactObserver class is a simple class that emits a signal when a single particular
  contact is updated or deleted.
  \inmodule QtContacts

  \ingroup contacts-main
 */

/*!
  Constructs a QContactObserver to observe the contact in \a manager with the
  given \a contactId and \a parent object.
 */
QContactObserver::QContactObserver(QContactManager* manager,
                                   QContactId contactId,
                                   QObject* parent)
    : QObject(parent),
      d(new QContactObserverPrivate)
{
    d->m_contactId = contactId;
    d->m_manager = manager;
    QContactManagerData::registerObserver(manager, this);
}

/*!
  Destroys this observer.
 */
QContactObserver::~QContactObserver()
{
    if (!d->m_manager.isNull()) {
        QContactManagerData::unregisterObserver(d->m_manager.data(), this);
    }
    delete d;
}

/*!
  Returns the contact id of the contact that this object observes.
 */
QContactId QContactObserver::contactId() const {
    return d->m_contactId;
}

/*!
  \fn QContactObserver::contactChanged(const QList<QContactDetail::DetailType> &typesChanged)

  This signal is emitted when the observed contact is changed in the manager.

  The set of contact detail types modified in the reported change is a subset of those listed in \a typesChanged,
  unless \a typesChanged is empty, in which case no limitation on the reported changes may be assumed.
 */

/*!
  \fn QContactObserver::contactRemoved()

  This signal is emitted when the observed contact is removed from the manager.
 */

#include "moc_qcontactobserver.cpp"

QT_END_NAMESPACE_CONTACTS
