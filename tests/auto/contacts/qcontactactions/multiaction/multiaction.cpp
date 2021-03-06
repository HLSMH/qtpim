/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ACTIONFACTORYPLUGINTARGET
#define ACTIONFACTORYPLUGINTARGET contacts_multiactionfactory
#endif
#ifndef ACTIONFACTORYPLUGINNAME
#define ACTIONFACTORYPLUGINNAME MultiActionFactory
#endif

#include "multiaction_p.h"

#include <QtContacts/qcontactphonenumber.h>
#include <QtContacts/qcontactemailaddress.h>
#include <QtContacts/qcontactfilters.h>

#include <QMessageBox>
#include <QTimer>

QTCONTACTS_USE_NAMESPACE

//! [Example Contact Action Plugin Implementation]

QObject* QContactMultiActionPlugin::createInstance(const QServiceInterfaceDescriptor& descriptor,
                        QServiceContext* context,
                        QAbstractSecuritySession* session)
{
    Q_UNUSED(context);
    Q_UNUSED(session);

    if (descriptor.interfaceName() == QContactActionFactory::InterfaceName
            && descriptor.serviceName() == QString(QLatin1String("tst_qcontactactions:multiaction"))
            && descriptor.majorVersion() == 1
            && descriptor.minorVersion() == 1
            && descriptor.customAttribute("ActionName") == QString(QLatin1String("call"))) {
        return new QContactMultiActionFactory;
    } else {
        return 0;
    }
}

Q_EXPORT_PLUGIN2(contacts_multiaction, QContactMultiActionPlugin);


QContactMultiActionFactory::QContactMultiActionFactory()
    : QContactActionFactory()
{
    m_actionOneDescriptor = createDescriptor("call", "tst_qcontactactions:multiaction", "sip", 1);
    m_actionTwoDescriptor = createDescriptor("call", "tst_qcontactactions:multiaction", "prop", 1);
}

QContactMultiActionFactory::~QContactMultiActionFactory()
{
}

QList<QContactActionDescriptor> QContactMultiActionFactory::actionDescriptors() const
{
    QList<QContactActionDescriptor> retn;
    retn << m_actionOneDescriptor << m_actionTwoDescriptor;
    return retn;
}

QContactAction* QContactMultiActionFactory::create(const QContactActionDescriptor& which) const
{
    if (which == m_actionOneDescriptor)
        return new QContactActionOne;
    else if (which == m_actionTwoDescriptor)
        return new QContactActionTwo;
    else
        return 0;
}

QSet<QContactActionTarget> QContactMultiActionFactory::supportedTargets(const QContact& contact, const QContactActionDescriptor& which) const
{
    QSet<QContactActionTarget> retn;
    if (which == m_actionOneDescriptor || which == m_actionTwoDescriptor) {
        // in this example, they support the same targets.
        QList<QContactPhoneNumber> pndets = contact.details<QContactPhoneNumber>();
        for (int i = 0; i < pndets.size(); ++i) {
            QContactActionTarget curr;
            curr.setContact(contact);
            curr.setDetails(QList<QContactDetail>() << pndets.at(i));
            retn << curr;
        }
    }

    return retn;
}

QContactFilter QContactMultiActionFactory::contactFilter(const QContactActionDescriptor& which) const
{
    if (which == m_actionOneDescriptor || which == m_actionTwoDescriptor) {
        QContactDetailFilter retn;
        retn.setDetailDefinitionName(QContactPhoneNumber::DefinitionName, QContactPhoneNumber::FieldNumber);
        return retn;
    }

    return QContactFilter();
}

QVariant QContactMultiActionFactory::metaData(const QString& key, const QList<QContactActionTarget>& targets, const QVariantMap& parameters, const QContactActionDescriptor& which) const
{
    Q_UNUSED(targets)
    Q_UNUSED(parameters)

    if (key == QContactActionDescriptor::MetaDataLabel)
        return QString("Call with VoIP");
    // Label etc

    if (key == QLatin1String("Provider")) {// our custom metadata - just return which.actionIdentifier
        return which.actionIdentifier();
    }

    return QVariant();
}

bool QContactMultiActionFactory::supportsContact(const QContact& contact, const QContactActionDescriptor& which) const
{
    if (which == m_actionOneDescriptor || which == m_actionTwoDescriptor)
        return !contact.details<QContactPhoneNumber>().isEmpty();
    return false;
}


QContactActionOne::QContactActionOne()
{

}

QContactActionOne::~QContactActionOne()
{

}

bool QContactActionOne::invokeAction(const QContactActionTarget& target, const QVariantMap& params)
{
    Q_UNUSED(params)
    // this action only works on (contact + phone number) targets.
    if (target.details().size() > 1 || target.details().at(0).definitionName() != QContactPhoneNumber::DefinitionName)
        return false;

    QTimer::singleShot(1, this, SLOT(performAction()));
    return true;
}

bool QContactActionOne::invokeAction(const QList<QContactActionTarget>& targets, const QVariantMap& params)
{
    Q_UNUSED(params)
    foreach (const QContactActionTarget& target, targets) {
        if (target.details().size() > 1 || target.details().at(0).definitionName() != QContactPhoneNumber::DefinitionName) {
            return false;
        }
    }

    QTimer::singleShot(1, this, SLOT(performAction()));
    return true;
}

QVariantMap QContactActionOne::results() const
{
    return QVariantMap();
}

QContactAction::State QContactActionOne::state() const
{
    return QContactAction::FinishedState;
}

void QContactActionOne::performAction()
{
    QMessageBox::information(0, "ActionOne", "This is action one!");
    emit stateChanged(QContactAction::FinishedState);
}

QContactActionTwo::QContactActionTwo()
{

}

QContactActionTwo::~QContactActionTwo()
{

}

bool QContactActionTwo::invokeAction(const QContactActionTarget& target, const QVariantMap& params)
{
    Q_UNUSED(params)
    // this action only works on (contact + phone number) targets.  Note that it doesn't
    // have to be the same as QContactActionOne -- it could have an entirely different implementation!
    if (target.details().size() > 1 || target.details().at(0).definitionName() != QContactPhoneNumber::DefinitionName)
        return false;

    QTimer::singleShot(1, this, SLOT(performAction()));
    return true;
}

bool QContactActionTwo::invokeAction(const QList<QContactActionTarget>& targets, const QVariantMap& params)
{
    Q_UNUSED(params)
    foreach (const QContactActionTarget& target, targets) {
        if (target.details().size() > 1 || target.details().at(0).definitionName() != QContactPhoneNumber::DefinitionName) {
            return false;
        }
    }

    QTimer::singleShot(1, this, SLOT(performAction()));
    return true;
}

QVariantMap QContactActionTwo::results() const
{
    return QVariantMap();
}

QContactAction::State QContactActionTwo::state() const
{
    return QContactAction::FinishedState;
}

void QContactActionTwo::performAction()
{
    QMessageBox::information(0, "ActionTwo", "This is action two!");
    emit stateChanged(QContactAction::FinishedState);
}

//! [Example Contact Action Plugin Implementation]
