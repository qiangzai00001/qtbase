/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/
**
** This file is part of the QtCore module of the Qt Toolkit.
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

#ifndef QFLAGS_H
#define QFLAGS_H

#include <QtCore/qglobal.h>

QT_BEGIN_HEADER

QT_BEGIN_NAMESPACE

class Q_CORE_EXPORT QFlag
{
    int i;
public:
    inline QFlag(int i);
    inline operator int() const { return i; }
};

inline QFlag::QFlag(int ai) : i(ai) {}

class Q_CORE_EXPORT QIncompatibleFlag
{
    int i;
public:
    inline explicit QIncompatibleFlag(int i);
    inline operator int() const { return i; }
};

inline QIncompatibleFlag::QIncompatibleFlag(int ai) : i(ai) {}


#ifndef Q_NO_TYPESAFE_FLAGS

template<typename Enum>
class QFlags
{
    typedef void **Zero;
    int i;
public:
    typedef Enum enum_type;
    // compiler-generated copy/move ctor/assignment operators are fine!
#ifdef qdoc
    inline QFlags(const QFlags &other);
    inline QFlags &operator=(const QFlags &other);
#endif
    Q_DECL_CONSTEXPR inline QFlags(Enum f) : i(f) {}
    Q_DECL_CONSTEXPR inline QFlags(Zero = 0) : i(0) {}
    inline QFlags(QFlag f) : i(f) {}

    inline QFlags &operator&=(int mask) { i &= mask; return *this; }
    inline QFlags &operator&=(uint mask) { i &= mask; return *this; }
    inline QFlags &operator|=(QFlags f) { i |= f.i; return *this; }
    inline QFlags &operator|=(Enum f) { i |= f; return *this; }
    inline QFlags &operator^=(QFlags f) { i ^= f.i; return *this; }
    inline QFlags &operator^=(Enum f) { i ^= f; return *this; }

    Q_DECL_CONSTEXPR  inline operator int() const { return i; }

    Q_DECL_CONSTEXPR inline QFlags operator|(QFlags f) const { return QFlags(Enum(i | f.i)); }
    Q_DECL_CONSTEXPR inline QFlags operator|(Enum f) const { return QFlags(Enum(i | f)); }
    Q_DECL_CONSTEXPR inline QFlags operator^(QFlags f) const { return QFlags(Enum(i ^ f.i)); }
    Q_DECL_CONSTEXPR inline QFlags operator^(Enum f) const { return QFlags(Enum(i ^ f)); }
    Q_DECL_CONSTEXPR inline QFlags operator&(int mask) const { return QFlags(Enum(i & mask)); }
    Q_DECL_CONSTEXPR inline QFlags operator&(uint mask) const { return QFlags(Enum(i & mask)); }
    Q_DECL_CONSTEXPR inline QFlags operator&(Enum f) const { return QFlags(Enum(i & f)); }
    Q_DECL_CONSTEXPR inline QFlags operator~() const { return QFlags(Enum(~i)); }

    Q_DECL_CONSTEXPR inline bool operator!() const { return !i; }

    inline bool testFlag(Enum f) const { return (i & f) == f && (f != 0 || i == int(f) ); }
};

#define Q_DECLARE_FLAGS(Flags, Enum)\
typedef QFlags<Enum> Flags;

#define Q_DECLARE_INCOMPATIBLE_FLAGS(Flags) \
inline QIncompatibleFlag operator|(Flags::enum_type f1, int f2) \
{ return QIncompatibleFlag(int(f1) | f2); }

#define Q_DECLARE_OPERATORS_FOR_FLAGS(Flags) \
Q_DECL_CONSTEXPR inline QFlags<Flags::enum_type> operator|(Flags::enum_type f1, Flags::enum_type f2) \
{ return QFlags<Flags::enum_type>(f1) | f2; } \
Q_DECL_CONSTEXPR inline QFlags<Flags::enum_type> operator|(Flags::enum_type f1, QFlags<Flags::enum_type> f2) \
{ return f2 | f1; } Q_DECLARE_INCOMPATIBLE_FLAGS(Flags)


#else /* Q_NO_TYPESAFE_FLAGS */

#define Q_DECLARE_FLAGS(Flags, Enum)\
typedef uint Flags;
#define Q_DECLARE_OPERATORS_FOR_FLAGS(Flags)

#endif /* Q_NO_TYPESAFE_FLAGS */

QT_END_NAMESPACE

QT_END_HEADER

#endif // QFLAGS_H
