name=/tmp/collection1
mkdir -p $name


for ins in Dual2_5000 Primal2_1000 L1_sixm1000obs L2CTA3D \
  degme dlr2 karted set-cover support19 L1_sixm250obs Linf_520c \
  a2864 bdry2 cont1 cont11 datt256 dlr1 ex10 fhnw-bin1 fome13 \
  graph40-40 irish-e neos neos3 neos3025225 neos5052403 neos5251915 \
  ns1687037 ns1688926 nug08-3rd pds-100 psched3-3 qap15 rail02 rail4284 \
  rmine15 s82 s100 s250r10 savsched1 scpm1 shs1023 square41 stat96v2 \
  storm_1000 stp3d support10 tpl-tub-ws woodlands09; do
  ff=$(find -H ./data -name "${ins}.mps.*" -print -quit)
  if [ -z "$ff" ]; then
    echo "unfound $ins";
    echo $ins >> unfound;
  else
    cp $ff $name/
  fi
done



#  wget --directory-prefix="$name" -nv http://www.netlib.org/lp/data/emps.c
#  cc -O3 -o "$name/emps" "$name/emps.c"
#
#  # bzipped "compressed MPS" instances from plato.asu.edu/fp/lptestset.
#  for f in L1_sixm250obs L1_sixm1000obs Linf_520c; do
#     ff=$(find -H ./data -name "${ins}.bz2.*" -print -quit)
#     if [ -z "$ff" ]; then
#         echo "unfound $ins";
#         echo $ins >> unfound;
#     else
#         cp $ff $name/
#     fi
#     bzcat $name/$f* | ${name}/emps | gzip > "$name/${f}.mps.gz"
#  done
