#!/bin/sh
#
# $Id: test_fcast_objaggr_mode.sh,v 1.3 2004/12/21 14:43:46 roca Exp $
#
#  Copyright (c) 1999-2004 INRIA - All rights reserved
#  (main authors: Julien Laboure - julien.laboure@inrialpes.fr
#                 Vincent Roca - vincent.roca@inrialpes.fr
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
#  USA.


#
# fcast validation script #3 : Fcast options and MCL Modes Tests
#
#
host_name=`uname -s`


echo "Running FCAST object aggregation test"
case ${host_name} in
Linux)
	fcast_path="../../bin/linux/fcast"
	;;

SunOS)
	fcast_path="../../bin/solaris/fcast"
	;;

FreeBSD)
	fcast_path="../../bin/freebsd/fcast"
	;;
# other OS???? todo
esac

# for debug...
#verbosity_recv='-v5'		# receiver part
verbosity_recv=''
#verbosity_send='-v1'		# sender part
verbosity_send=''

echo ""
echo "${fcast_path} ${verbosity_recv} -recv -a225.1.2.3/9991 -never -phigh "
echo "${fcast_path} ${verbosity_send} -send -a225.1.2.3/9991 -ospeed -phigh -objaggr -R ./"
echo ""

recv_val=1
send_val=1
rm -Rf ./fcast_test/recv/*
cd fcast_test/recv
../../${fcast_path} ${verbosity_recv} -recv -a225.1.2.3/9991 -never -phigh &
fcast_recv_pid=$!

cd ../send
../../${fcast_path} ${verbosity_send} -send -a225.1.2.3/9991 -ospeed -phigh -objaggr -R ./ &
fcast_send_pid=$!

wait ${fcast_recv_pid}
recv_val=$?

wait ${fcast_send_pid}
send_val=$?
# TODO : what if Sender has finished before receiver ??

cd ../..
diff ./fcast_test/send/${file} ./fcast_test/recv/${file}
diff_val=$?


if [ ${recv_val} -ne 0 ]
then
        echo "FCAST Recv Failed"
        exit 1

elif [ ${send_val} -ne 0 ]
then
        echo "FCAST Send Failed"
        exit 1

elif [ ${diff_val} -ne 0 ]
then
        echo "Test failed: received files do not match sent files!"
        exit 1

else
        echo "-- Test OK!"
	exit 0
fi

