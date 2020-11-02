touch myFIX myfix
LD_PRELOAD=`pwd`/libunlinkat_wrapper.so rm myFIX myfix || true
test -f myFIX 
! test -f myfix
