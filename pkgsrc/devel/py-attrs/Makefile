# $NetBSD: Makefile,v 1.6 2017/09/03 08:36:53 wiz Exp $

DISTNAME=	attrs-17.2.0
PKGNAME=	${PYPKGPREFIX}-${DISTNAME}
CATEGORIES=	devel
MASTER_SITES=	${MASTER_SITE_PYPI:=a/attrs/}

MAINTAINER=	pkgsrc-users@NetBSD.org
#HOMEPAGE=	https://www.attrs.org/
COMMENT=	Attributes without boilerplate
LICENSE=	mit

USE_LANGUAGES=		# none

BUILD_DEPENDS+=		${PYPKGPREFIX}-hypothesis-[0-9]*:../../devel/py-hypothesis

.include "../../lang/python/egg.mk"
.include "../../mk/bsd.pkg.mk"
