/********************************************************************
    Copyright (c) 2013-2014 - QSanguosha-Hegemony Team

    This file is part of QSanguosha-Hegemony.

    This game is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 3.0 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    See the LICENSE file for more details.

    QSanguosha-Hegemony Team
    *********************************************************************/

#include "StyleHelper.h"

#include <QApplication>
#include <QFontDatabase>
#include <QPushButton>
#include <QMap>

StyleHelper *StyleHelper::instance = NULL;

StyleHelper::StyleHelper(QObject *):
    QObject(qApp)
{
    iconFont = getFontByFileName("fontawesome-webfont.ttf");
}

StyleHelper *StyleHelper::getInstance()
{
    static QMutex mutex;
    if (!instance) {
        QMutexLocker locker(&mutex);
        if (!instance) {
            instance = new StyleHelper;
        }
    }
    return instance;
}

QFont StyleHelper::getFontByFileName(const QString &fileName)
{
    static QMap<QString, QFont> loadedFonts;
    if (loadedFonts.keys().contains(fileName)) {
        return loadedFonts.value(fileName);
    } else {
        int fontId = QFontDatabase::addApplicationFont("font/" + fileName);
        Q_ASSERT(fontId != -1);
        QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(fontName);
        loadedFonts[fileName] = font;
        return font;
    }
}

void StyleHelper::setIcon(QPushButton* button, QChar iconId, int size)
{
    iconFont.setPointSize(size);
    button->setFont(iconFont);
    button->setText(iconId);
}