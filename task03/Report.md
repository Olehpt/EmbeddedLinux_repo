#OUTPUT FOR check_format.sh script

This script is about to check chosen catalog by clang-format-21 & clang-format-17.
==CLANG-FORMAT-21==
NOT OK: dummy/include/btrtl.h
NOT OK: dummy/include/btbcm.h
NOT OK: dummy/include/hci_uart.h
NOT OK: dummy/src/hci_aml.c
NOT OK: dummy/src/btrtl.c
NOT OK: dummy/src/btbcm.c
NOT OK: dummy/src/bfusb.c

==CLANG-FORMAT-17==
NOT OK: dummy/include/btrtl.h
NOT OK: dummy/include/btbcm.h
NOT OK: dummy/include/hci_uart.h
NOT OK: dummy/src/hci_aml.c
NOT OK: dummy/src/btrtl.c
NOT OK: dummy/src/btbcm.c
NOT OK: dummy/src/bfusb.c

#OUTPUT FOR check_format.sh script after running ./make_format21.sh


This script is about to check chosen catalog by clang-format-21 & clang-format-17.
==CLANG-FORMAT-21==
OK: dummy/include/btrtl.h
OK: dummy/include/btbcm.h
OK: dummy/include/hci_uart.h
OK: dummy/src/hci_aml.c
OK: dummy/src/btrtl.c
OK: dummy/src/btbcm.c
OK: dummy/src/bfusb.c

==CLANG-FORMAT-17==
OK: dummy/include/btrtl.h
OK: dummy/include/btbcm.h
OK: dummy/include/hci_uart.h
OK: dummy/src/hci_aml.c
OK: dummy/src/btrtl.c
OK: dummy/src/btbcm.c
OK: dummy/src/bfusb.c

#OUTPUT FOR check_format.sh script after running ./make_format17.sh

This script is about to check chosen catalog by clang-format-21 & clang-format-17.
==CLANG-FORMAT-21==
OK: dummy/include/btrtl.h
OK: dummy/include/btbcm.h
OK: dummy/include/hci_uart.h
OK: dummy/src/hci_aml.c
OK: dummy/src/btrtl.c
OK: dummy/src/btbcm.c
OK: dummy/src/bfusb.c

==CLANG-FORMAT-17==
OK: dummy/include/btrtl.h
OK: dummy/include/btbcm.h
OK: dummy/include/hci_uart.h
OK: dummy/src/hci_aml.c
OK: dummy/src/btrtl.c
OK: dummy/src/btbcm.c
OK: dummy/src/bfusb.c

#DIFF 
Порівняння конфігурацій за допомогою diff показало, що між версіями існують відмінності у значеннях окремих параметрів та складі доступних параметрів форматування.
