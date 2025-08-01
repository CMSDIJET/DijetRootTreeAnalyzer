Madgraph cards for the production of signal MC used in the CMS analysis EXO-24-038. The benchmark signal used in this analysis is an Suu diquark decaying into a pair of vector-like quarks, chi, each then decaying into a pair of up quark and gluon: uu->Suu->(chi)(chi)->(ug)(ug). 

In this analysis we consider three widths of the Suu diquark: 1.5% (W-0p015), 5% (W-0p05) and 10% (W-0p1) of its mass. 

As explained in the paper (Eqs. 3-4 and related text), for a given alpha_true = M(chi)/M(S) value we need to change the yuu and ychi couplings accordingly so as to generate the corresponding widths, keeping the relation yuu/ychi=2/3 constant. Due to a factor 2 difference in the lagrangian in 'Suu_diquark_UFO.tar.gz', the couplings yuu and ychi are implemented within Madgraph through the parameters [FRBLOCK 1] = lampbda_uu = yuu/2 and [FRBLOCK 2] = lampbda_chi = ychi/2.

In this directory we provide the following input cards:
SuuDQTemplate_customizecards.dat
SuuDQTemplate_extramodels.dat
SuuDQTemplate_madspin_card.dat
SuuDQTemplate_proc_card.dat
SuuDQTemplate_run_card.dat

These are the same for all widths and alpha_true values, except for 'SuuDQTemplate_customizecards.dat' where we change the [FRBLOCK 1] and [FRBLOCK 2] parameters. In this .dat file we can also define the Suu and chi masses.

These input cards are the same as the ones used by EXO-21-010 with the only difference that in EXO-21-010 we had set yuu = 0.4 ([FRBLOCK 1] = lampbda_uu = 0.2) and ychi = 0.6 ([FRBLOCK 2] = lampbda_chi = 0.3), which generated narrow diquark resonances with widths less than 0.5% of their mass, depending on the alpha_true value.

In EXO-24-038 we also set mass limits on the Sdd diquark model: dd->Sdd->(omega)(omega)->(dg)(dg)

The input MadGraph cards are *the same* as the ones provided here, with the substitution of u->d and chi->omega in all of the .dat files. Everything else is the same but ***please keep in mind***: In the 'Sdd_diquark_UFO.tar.gz' file there is no factor of 2 difference in the lagrangian, so for Sdd we have [FRBLOCK 1] = ydd and [FRBLOCK 2] = yomega.
