#
# This Makefile provides an easy way to generate the configuration
# file and database maps for the sendmail(8) daemon.
#
# The user-driven targets are:
#
# all     - Build cf, maps and aliases
# cf      - Build the .cf file from .mc file
# maps    - Build the feature maps
# aliases - Build the sendmail aliases
# install - Install the .cf file as /etc/mail/sendmail.cf
#
# For acting on both the MTA daemon and MSP queue running daemon:
# start        - Start both the sendmail MTA daemon and MSP queue running
#                daemon with the flags defined in /etc/defaults/rc.conf or
#                /etc/rc.conf
# stop         - Stop both the sendmail MTA daemon and MSP queue running
#                daemon
# restart      - Restart both the sendmail MTA daemon and MSP queue running
#                daemon
#
# For acting on just the MTA daemon:
# start-mta    - Start the sendmail MTA daemon with the flags defined in
#                /etc/defaults/rc.conf or /etc/rc.conf
# stop-mta     - Stop the sendmail MTA daemon
# restart-mta  - Restart the sendmail MTA daemon
#
# For acting on just the MSP queue running daemon:
# start-mspq   - Start the sendmail MSP queue running daemon with the
#                flags defined in /etc/defaults/rc.conf or /etc/rc.conf
# stop-mspq    - Stop the sendmail MSP queue running daemon
# restart-mspq - Restart the sendmail MSP queue running daemon
#
# Calling `make' will generate the updated versions when either the
# aliases or one of the map files were changed.
#
# A `make install` is only necessary after modifying the .mc file. In
# this case one would normally also call `make restart' to allow the
# running sendmail to pick up the changes as well.
#
# ------------------------------------------------------------------------
#
# The Makefile knows about the following maps:
# access, bitdomain, domaintable, genericstable, mailertable, userdb,
# uucpdomain, virtusertable
#

SENDMAIL_MC=		sendmail.mc

SENDMAIL_SUBMIT_MC=	submit.mc

INSTALL_CF=		${SENDMAIL_MC:R}.cf

INSTALL_SUBMIT_CF=	/usr/pkg/share/sendmail/cf/submit.cf

SENDMAIL_ALIASES?=	/etc/mail/aliases

#
# This is the directory where the sendmail configuration files are
# located.
#
SENDMAIL_CF_DIR?=	/usr/pkg/share/sendmail

#
# The sendmail startup script
#
SENDMAIL_START_SCRIPT?=	/etc/rc.d/sendmail

#
# Some useful programs we need.
#
SENDMAIL?=		/usr/sbin/sendmail
MAKEMAP?=		/usr/pkg/sbin/makemap
M4?=			/usr/bin/m4

# Permissions for generated maps
SENDMAIL_MAP_PERMS?=	0640

# Set a reasonable default
.MAIN: all

#
# ------------------------------------------------------------------------
#
# The Makefile picks up the list of files from SENDMAIL_MAP_SRC and
# stores the matching .db filenames in SENDMAIL_MAP_OBJ if the file
# exists in the current directory.  SENDMAIL_MAP_TYPE is the database
# type to use when calling makemap.
#
SENDMAIL_MAP_SRC+=	mailertable domaintable bitdomain uucpdomain \
			genericstable virtusertable access authinfo
SENDMAIL_MAP_OBJ=
SENDMAIL_MAP_TYPE?=	hash

.for _f in ${SENDMAIL_MAP_SRC} userdb
.if exists(${_f})
SENDMAIL_MAP_OBJ+=	${_f}.db
.endif
.endfor

#
# The makemap command is used to generate a hashed map from the textfile.
#
.for _f in ${SENDMAIL_MAP_SRC}
.if (exists(${_f}.sample) && !exists(${_f}))
${_f}: ${_f}.sample
	sed -e 's/^/#/' < ${.OODATE} > ${.TARGET}
.endif

${_f}.db: ${_f}
	${MAKEMAP} ${SENDMAIL_MAP_TYPE} ${.TARGET} < ${.OODATE}
	chmod ${SENDMAIL_MAP_PERMS} ${.TARGET}
.endfor

userdb.db: userdb
	${MAKEMAP} btree ${.TARGET} < ${.OODATE}
	chmod ${SENDMAIL_MAP_PERMS} ${.TARGET}


#
# The .cf file needs to be recreated if the templates were modified.
#
M4FILES!=	find ${SENDMAIL_CF_DIR} -type f -name '*.m4' -print

#
# M4(1) is used to generate the .cf file from the .mc file.
#
.SUFFIXES: .cf .mc

.mc.cf: ${M4FILES}
	${M4} -D_CF_DIR_=${SENDMAIL_CF_DIR}/ ${SENDMAIL_M4_FLAGS} \
	    ${SENDMAIL_CF_DIR}/m4/cf.m4 ${@:R}.mc > ${.TARGET}

#
# Aliases are handled separately since they normally reside in /etc
# and can be rebuild without the help of makemap.
#
.for _f in ${SENDMAIL_ALIASES}
${_f}.db: ${_f}
	${SENDMAIL} -bi -OAliasFile=${.ALLSRC}
	chmod ${SENDMAIL_MAP_PERMS} ${.TARGET}
.endfor

#
# ------------------------------------------------------------------------
#

all: cf maps aliases

clean:

depend:

cf: ${INSTALL_CF} ${INSTALL_SUBMIT_CF}

.ifdef SENDMAIL_SET_USER_ID
install: install-cf
.else
install: install-cf install-submit-cf
.endif

install-cf: ${INSTALL_CF}
.if ${INSTALL_CF} != /etc/mail/sendmail.cf
	${INSTALL} -m ${SHAREMODE} ${INSTALL_CF} /etc/mail/sendmail.cf
.endif


install-submit-cf: ${INSTALL_SUBMIT_CF}
.ifdef SENDMAIL_SET_USER_ID
	@echo ">>> ERROR: You should not create a submit.cf file if you are using a"
	@echo "           set-user-ID sendmail binary (SENDMAIL_SET_USER_ID is set"
	@echo "           in make.conf)."
	@false
.else
.if ! exists(/etc/mail/submit.cf)
	${INSTALL} -m ${SHAREMODE} ${INSTALL_SUBMIT_CF} /etc/mail/submit.cf
.endif
.endif

aliases: ${SENDMAIL_ALIASES:%=%.db}

maps: ${SENDMAIL_MAP_OBJ}

start start-mta start-mspq:
	@if [ -r ${SENDMAIL_START_SCRIPT} ]; then \
		echo -n 'Starting:'; \
		sh ${SENDMAIL_START_SCRIPT} $@; \
		echo '.'; \
	fi

stop stop-mta stop-mspq:
	@if [ -r ${SENDMAIL_START_SCRIPT} ]; then \
		echo -n 'Stopping:'; \
		sh ${SENDMAIL_START_SCRIPT} $@; \
		echo '.'; \
	fi

restart restart-mta restart-mspq:
	@if [ -r ${SENDMAIL_START_SCRIPT} ]; then \
		echo -n 'Restarting:'; \
		sh ${SENDMAIL_START_SCRIPT} $@; \
		echo '.'; \
	fi

# User defined targets
.if exists(Makefile.local)
.include "Makefile.local"
.endif

# For the definition of $SHAREMODE
.include <bsd.own.mk>
