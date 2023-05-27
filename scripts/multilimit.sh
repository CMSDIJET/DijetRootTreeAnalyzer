mkdir -p cards_gaus10_freq
#inclusive
python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijet2016_Full/DijetFitResults_PFDijet2016.root -b PFDijet2016 --rMax 20 --xsec 1e-3 -l 36.428 --no-sys
#MT
python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijetbb20160mt_Full/DijetFitResults_PFDijetbb20160mt.root -b PFDijetbb20160mt --rMax 20 --xsec 1e-3 -l 36.428 --no-sys

python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijetbb20161mt_Full/DijetFitResults_PFDijetbb20161mt.root -b PFDijetbb20161mt --rMax 20 --xsec 1e-3 -l 36.428 --no-sys

python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijetbb20162mt_Full/DijetFitResults_PFDijetbb20162mt.root -b PFDijetbb20162mt --rMax 20 --xsec 1e-3 -l 36.428 --no-sys

#MM
python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijetbb20160mm_Full/DijetFitResults_PFDijetbb20160mm.root -b PFDijetbb20160mm --rMax 20 --xsec 1e-3 -l 36.428 --no-sys

python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijetbb20161mm_Full/DijetFitResults_PFDijetbb20161mm.root -b PFDijetbb20161mm --rMax 20 --xsec 1e-3 -l 36.428 --no-sys

python python/RunCombine.py -m gaus10 -d cards_gaus10_freq/ --mass range\(1650,7550,100\) -c config/dijet.config -i fits_2016_11_28/PFDijetbb20162mm_Full/DijetFitResults_PFDijetbb20162mm.root -b PFDijetbb20162mm --rMax 20 --xsec 1e-3 -l 36.428 --no-sys

