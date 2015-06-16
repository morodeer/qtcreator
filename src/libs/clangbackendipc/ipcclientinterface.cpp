/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://www.qt.io/licensing.  For further information
** use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file.  Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/

#include "ipcclientinterface.h"

#include <QVariant>
#include <QtDebug>

#include "cmbechocommand.h"
#include "cmbcodecompletedcommand.h"
#include "translationunitdoesnotexistcommand.h"
#include "projectpartsdonotexistcommand.h"

namespace ClangBackEnd {


void IpcClientInterface::dispatch(const QVariant &command)
{
    static const int aliveCommandType = QMetaType::type("ClangBackEnd::AliveCommand");
    static const int echoCommandType = QMetaType::type("ClangBackEnd::EchoCommand");
    static const int codeCompletedCommandType = QMetaType::type("ClangBackEnd::CodeCompletedCommand");
    static const int translationUnitDoesNotExistCommand = QMetaType::type("ClangBackEnd::TranslationUnitDoesNotExistCommand");
    static const int projectPartsDoNotExistCommand = QMetaType::type("ClangBackEnd::ProjectPartsDoNotExistCommand");

    int type = command.userType();

    if (type == aliveCommandType)
        alive();
    else if (type == echoCommandType)
        echo(command.value<EchoCommand>());
    else if (type == codeCompletedCommandType)
        codeCompleted(command.value<CodeCompletedCommand>());
    else if (type == translationUnitDoesNotExistCommand)
        translationUnitDoesNotExist(command.value<TranslationUnitDoesNotExistCommand>());
    else if (type == projectPartsDoNotExistCommand)
        projectPartsDoNotExist(command.value<ProjectPartsDoNotExistCommand>());
    else
        qWarning() << "Unknown IpcClientCommand";
}

} // namespace ClangBackEnd
