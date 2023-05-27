#inclusive
mkdir -p fits_2016_11_28/PFDijet2016_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijet2016 -d fits_2016_11_28/PFDijet2016_Full/ --fit-spectrum
#MT
mkdir -p fits_2016_11_28/PFDijetbb20160mt_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijetbb20160mt -d fits_2016_11_28/PFDijetbb20160mt_Full/ --fit-spectrum

mkdir -p fits_2016_11_28/PFDijetbb20161mt_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijetbb20161mt -d fits_2016_11_28/PFDijetbb20161mt_Full/ --fit-spectrum

mkdir -p fits_2016_11_28/PFDijetbb20162mt_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijetbb20162mt -d fits_2016_11_28/PFDijetbb20162mt_Full/ --fit-spectrum
#MM
mkdir -p fits_2016_11_28/PFDijetbb20160mm_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijetbb20160mm -d fits_2016_11_28/PFDijetbb20160mm_Full/ --fit-spectrum

mkdir -p fits_2016_11_28/PFDijetbb20161mm_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijetbb20161mm -d fits_2016_11_28/PFDijetbb20161mm_Full/ --fit-spectrum

mkdir -p fits_2016_11_28/PFDijetbb20162mm_Full/
python python/BinnedFit.py -c config/dijet.config -l 36428 -s inputs/ResonanceShapes_gaus10_13TeV_Spring16.root inputs/moriond16_v1_36fb_jsonFix.root -b PFDijetbb20162mm -d fits_2016_11_28/PFDijetbb20162mm_Full/ --fit-spectrum
