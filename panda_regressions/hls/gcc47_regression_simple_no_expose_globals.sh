#!/bin/bash
$(dirname $0)/../../etc/scripts/test_panda.py gcc_regression_simple --tool=bambu \
   --args="--configuration-name=GCC47_O0 -O0 -lm --simulate --pretty-print=output.c --do-not-expose-globals --experimental-setup=BAMBU --compiler=I386_GCC47" \
   --args="--configuration-name=GCC47_O1 -O1 -lm --simulate --pretty-print=output.c --do-not-expose-globals --experimental-setup=BAMBU --compiler=I386_GCC47" \
   --args="--configuration-name=GCC47_O2 -O2 -lm --simulate --pretty-print=output.c --do-not-expose-globals --experimental-setup=BAMBU --compiler=I386_GCC47" \
   --args="--configuration-name=GCC47_O3 -O3 -lm --simulate --pretty-print=output.c --do-not-expose-globals --experimental-setup=BAMBU --compiler=I386_GCC47" \
   -o output_gcc47_simple_do_not_expose_globals -b$(dirname $0) --table=output_gcc47_simple.tex --name="Gcc47RegressionSimple" $@
exit $?
