# $NetBSD: Makefile,v 1.13 2017/06/12 08:16:57 maya Exp $
#

DISTNAME=	LWP-Online-1.08
PKGNAME=	p5-${DISTNAME}
PKGREVISION=	6
CATEGORIES=	www net perl5
MASTER_SITES=	${MASTER_SITE_PERL_CPAN:=LWP/}

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://search.cpan.org/dist/LWP-Online/
COMMENT=	Does your process have access to the web
LICENSE=	${PERL5_LICENSE}

DEPENDS+=	p5-libwww-[0-9]*:../../www/p5-libwww
DEPENDS+=	p5-URI-[0-9]*:../../www/p5-URI

USE_LANGUAGES=		# empty
MAKE_ENV+=		PERL_USE_UNSAFE_INC=1
PERL5_PACKLIST=		auto/LWP/Online/.packlist

.include "../../lang/perl5/module.mk"
.include "../../mk/bsd.pkg.mk"
