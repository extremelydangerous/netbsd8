# $NetBSD: Makefile,v 1.79 2017/09/07 11:24:29 prlw1 Exp $

DISTNAME=	cups-filters-1.17.2
PKGREVISION=	3
CATEGORIES=	print
MASTER_SITES=	http://openprinting.org/download/cups-filters/
EXTRACT_SUFX=	.tar.xz

MAINTAINER=	pkgsrc-users@NetBSD.org
HOMEPAGE=	http://www.linuxfoundation.org/collaborate/workgroups/openprinting/cups-filters
COMMENT=	Backends, filters, and other software for cups
LICENSE=	gnu-gpl-v2 AND gnu-gpl-v3 AND gnu-lgpl-v2 AND mit

GNU_CONFIGURE=	yes
USE_LIBTOOL=	yes
USE_TOOLS+=	bash:run pkg-config gmake
USE_LANGUAGES=	c c++11

BUILD_DEPENDS+=	gdbus-codegen-[0-9]*:../../devel/gdbus-codegen
DEPENDS+=	poppler-utils-[0-9]*:../../print/poppler-utils

PKGCONFIG_OVERRIDE+=	libcupsfilters.pc.in
PKGCONFIG_OVERRIDE+=	libfontembed.pc.in

CONFLICTS+=	cups<1.6

REPLACE_BASH+=	filter/braille/drivers/generic/brftoembosser.in
REPLACE_BASH+=	filter/braille/drivers/index/imageubrltoindexv3.in
REPLACE_BASH+=	filter/braille/drivers/index/imageubrltoindexv4.in
REPLACE_BASH+=	filter/braille/drivers/index/textbrftoindexv3.in
REPLACE_BASH+=	filter/braille/filters/imagetobrf.in
REPLACE_BASH+=	filter/braille/filters/texttobrf.in

.include "../../mk/bsd.prefs.mk"

.if ${OPSYS} == "Darwin"
CFLAGS+=	-framework IOKit
.endif

BUILD_DEFS+=		VARBASE
CONFIGURE_ARGS+=	--localstatedir=${VARBASE}

RCD_SCRIPTS=		cups-browsed

CONFIGURE_ARGS+=	--disable-braille
CONFIGURE_ARGS+=	--disable-ldap
CONFIGURE_ARGS+=	--disable-mutool
CONFIGURE_ARGS+=	--with-apple-raster-filter=rastertopdf
CONFIGURE_ARGS+=	--with-shell=${TOOLS_PATH.bash}
CONFIGURE_ARGS+=	--with-pdftops-path=${PREFIX}/bin/pdftops
CONFIGURE_ARGS+=	--with-gs-path=${PREFIX}/bin/gs

INSTALL_MAKE_FLAGS+=	sysconfdir=${PREFIX}/share/examples/cups-filters

CONF_FILES=		${PREFIX}/share/examples/cups-filters/fonts/conf.d/99pdftoopvp.conf ${PKG_SYSCONFDIR}/fontconfig/conf.d/99pdftoopvp.conf
CONF_FILES+=		${PREFIX}/share/examples/cups-filters/cups-browsed.conf ${PKG_SYSCONFDIR}/cups/cups-browsed.conf

post-extract:
	${CP} ${FILESDIR}/cups-browsed-daemonize.sh ${WRKSRC}

SUBST_CLASSES+=			daemonize
SUBST_STAGE.daemonize=		pre-configure
SUBST_MESSAGE.daemonize=	Customizing daemonizing script
SUBST_FILES.daemonize=		cups-browsed-daemonize.sh
SUBST_SED.daemonize=		-e 's|@PREFIX@|${PREFIX}|g'
SUBST_SED.daemonize+=		-e 's|@VARBASE@|${VARBASE}|g'

post-install:
	${MV} ${DESTDIR}${PKG_SYSCONFDIR}/cups/cups-browsed.conf ${DESTDIR}${PREFIX}/share/examples/cups-filters/cups-browsed.conf
	# backends that need root access should not have world read and execute permissions
	${CHMOD} go-rwx ${DESTDIR}${PREFIX}/libexec/cups/backend/parallel
	${CHMOD} go-rwx ${DESTDIR}${PREFIX}/libexec/cups/backend/serial
	${INSTALL_SCRIPT} ${WRKSRC}/cups-browsed-daemonize.sh ${DESTDIR}${PREFIX}/libexec/cups-browsed

.include "../../devel/glib2/buildlink3.mk"
.include "../../devel/zlib/buildlink3.mk"
.include "../../fonts/fontconfig/buildlink3.mk"
.include "../../graphics/freetype2/buildlink3.mk"
.include "../../graphics/lcms2/buildlink3.mk"
.include "../../graphics/png/buildlink3.mk"
.include "../../graphics/tiff/buildlink3.mk"
.include "../../net/avahi/buildlink3.mk"
BUILDLINK_ABI_DEPENDS.cups+=	cups>=1.7.4nb1
.include "../../print/cups/buildlink3.mk"
.include "../../print/ghostscript/buildlink3.mk"
.include "../../print/ijs/buildlink3.mk"
.include "../../print/poppler-cpp/buildlink3.mk"
.include "../../print/poppler-glib/buildlink3.mk"
BUILDLINK_ABI_DEPENDS.poppler-includes?=	poppler-includes>=0.26.1nb1
.include "../../print/poppler-includes/buildlink3.mk"
.include "../../print/qpdf/buildlink3.mk"
.include "../../mk/jpeg.buildlink3.mk"
.include "../../mk/bsd.pkg.mk"
