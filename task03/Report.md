### OUTPUT FOR check_format.sh script

This script is about to check chosen catalog by clang-format-21 & clang-format-17.<br>
==CLANG-FORMAT-21==<br>
NOT OK: dummy/include/btrtl.h<br>
NOT OK: dummy/include/btbcm.h<br>
NOT OK: dummy/include/hci_uart.h<br>
NOT OK: dummy/src/hci_aml.c<br>
NOT OK: dummy/src/btrtl.c<br>
NOT OK: dummy/src/btbcm.c<br>
NOT OK: dummy/src/bfusb.c<br>

==CLANG-FORMAT-17==<br>
NOT OK: dummy/include/btrtl.h<br>
NOT OK: dummy/include/btbcm.h<br>
NOT OK: dummy/include/hci_uart.h<br>
NOT OK: dummy/src/hci_aml.c<br>
NOT OK: dummy/src/btrtl.c<br>
NOT OK: dummy/src/btbcm.c<br>
NOT OK: dummy/src/bfusb.c<br>

### OUTPUT FOR check_format.sh script after running ./make_format21.sh


This script is about to check chosen catalog by clang-format-21 & clang-format-17.<br>
==CLANG-FORMAT-21==<br>
OK: dummy/include/btrtl.h<br>
OK: dummy/include/btbcm.h<br>
OK: dummy/include/hci_uart.h<br>
OK: dummy/src/hci_aml.c<br>
OK: dummy/src/btrtl.c<br>
OK: dummy/src/btbcm.c<br>
OK: dummy/src/bfusb.c<br>

==CLANG-FORMAT-17==<br>
OK: dummy/include/btrtl.h<br>
OK: dummy/include/btbcm.h<br>
OK: dummy/include/hci_uart.h<br>
OK: dummy/src/hci_aml.c<br>
OK: dummy/src/btrtl.c<br>
OK: dummy/src/btbcm.c<br>
OK: dummy/src/bfusb.c<br>

### OUTPUT FOR check_format.sh script after running ./make_format17.sh

This script is about to check chosen catalog by clang-format-21 & clang-format-17.<br>
==CLANG-FORMAT-21==<br>
OK: dummy/include/btrtl.h<br>
OK: dummy/include/btbcm.h<br>
OK: dummy/include/hci_uart.h<br>
OK: dummy/src/hci_aml.c<br>
OK: dummy/src/btrtl.c<br>
OK: dummy/src/btbcm.c<br>
OK: dummy/src/bfusb.c<br>

==CLANG-FORMAT-17==<br>
OK: dummy/include/btrtl.h<br>
OK: dummy/include/btbcm.h<br>
OK: dummy/include/hci_uart.h<br>
OK: dummy/src/hci_aml.c<br>
OK: dummy/src/btrtl.c<br>
OK: dummy/src/btbcm.c<br>
OK: dummy/src/bfusb.c<br>

### DIFF 
Порівняння конфігурацій за допомогою diff показало, що між версіями існують відмінності у значеннях окремих параметрів та складі доступних параметрів форматування.

### DIFF after swapping to chromium 17 (AFTER linux .clang-format file)

 task03/dummy/.clang-format      | 1004 ++++------------<br>
 task03/dummy/include/btbcm.h    |  140 ++-<br>
 task03/dummy/include/btrtl.h    |  196 ++-<br>
 task03/dummy/include/hci_uart.h |  141 +--<br>
 task03/dummy/src/bfusb.c        | 1029 ++++++++--------<br>
 task03/dummy/src/btbcm.c        | 1276 ++++++++++----------<br>
 task03/dummy/src/btrtl.c        | 2484 +++++++++++++++++++--------------------<br>
 task03/dummy/src/hci_aml.c      | 1049 ++++++++---------<br>
 task03/linux.clang-format       |  808 +++++++++++++<br>
 9 files changed, 4120 insertions(+), 4007 deletions(-)<br>

### DIFF after swapping from chromium 17 to chromium 21

task03/Report.md           | 13 +++++++++++++<br>
task03/dummy/.clang-format | 82 +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++---------<br>
2 files changed, 86 insertions(+), 9 deletions(-)<br>

### Висновок

Після заміни конфігурації Chromium 17 на Chromium 21 та повторного форматування вихідних файлів додаткових змін у .c та .h файлах не було виявлено.
Це означає, що після форматування за правилами Chromium 17 вихідний код уже відповідав правилам форматування, які застосовує clang-format 21 у цьому випадку.
Відмінності між версіями конфігурації при цьому присутні, але вони не призвели до додаткових змін у вихідному коді.
