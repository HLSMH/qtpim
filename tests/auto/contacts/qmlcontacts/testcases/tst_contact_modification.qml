/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtPim module of the Qt Toolkit.
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

import QtQuick 2.0
import QtTest 1.0
import QtContacts 5.0

TestCase {
    name: "ContactModificationTests"
    id: contactModificationTests

    TestCase {
        name: "ContactModificationTests::UpdateDetail"

        Contact {
            id: contact1
            Name {
                id: contact1Name
                firstName: "old"
            }
        }

        function test_update_to_contact_detail_directly_sets_contact_as_modified() {
            contact1Name.firstName = "new";
            verify(contact1.modified);
        }

        Contact {
            id: contact2
            Name {
                id: contact2Name
                firstName: "old"
            }
        }

        function test_update_to_contact_detail_sets_contact_as_modified() {
            contact2.name.firstName = "new";
            verify(contact2.modified);
        }
    }

    TestCase {
        name: "ContactModificationTests::ThroughDetailAccessors"

        Contact {
            id: contact50
            Name {
                firstName: "old"
            }
        }

        function test_modification_through_detail_modifies_the_contact() {
            var detail = contact50.detail(ContactDetail.Name);
            detail.firstName = "new"
            detail = contact50.detail(ContactDetail.Name);
            compare(detail.firstName, "new");
        }

        Contact {
            id: contact51
            Name {
                firstName: "old"
            }
        }

        function test_modification_through_details_modifies_the_contact() {
            var details = contact51.details(ContactDetail.Name);
            details[0].firstName = "new"
            var detail = contact51.detail(ContactDetail.Name);
            compare(detail.firstName, "new");
        }

        Contact {
            id: contact52
            Name {
                firstName: "old"
            }
        }

        function test_modification_through_detail_emits_contact_changed() {
            var detail = contact52.detail(ContactDetail.Name);
            listenToSignalFromObject("contactChanged", contact52);
            detail.firstName = "new"
            verifySignalReceived();
        }

        Contact {
            id: contact53
            Name {
                firstName: "old"
            }
        }

        function test_modification_through_details_emits_contact_changed() {
            var details = contact53.details(ContactDetail.Name);
            listenToSignalFromObject("contactChanged", contact53);
            details[0].firstName = "new"
            verifySignalReceived();
        }

        property SignalSpy spy

        function init() {
            spy = Qt.createQmlObject("import QtTest 1.0;" +
                                     "SignalSpy {}",
                                     this);
        }

        function listenToSignalFromObject(signalName, object) {
            spy.target = object;
            spy.signalName = signalName;
            spy.clear();
        }

        function verifySignalReceived() {
            spy.wait();
        }

        function verifyNoSignalReceived() {
            verify(spy.count == 0, "no signal was received");
        }

    }
}
