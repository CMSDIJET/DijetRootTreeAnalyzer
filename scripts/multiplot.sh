#inclusive
python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijet2016 --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijet2016 -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4
#MT
python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijetbb20160mt --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijetbb20160mt -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4

python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijetbb20161mt --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijetbb20161mt -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4

python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijetbb20162mt --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijetbb20162mt -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4
#MM
python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijetbb20160mm --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijetbb20160mm -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4

python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijetbb20161mm --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijetbb20161mm -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4

python python/GetCombine.py -d cards_gaus10_freq/ -m gaus10 --mass range\(1650,7550,100\) -b PFDijetbb20162mm --xsec 1e-3 -l 36.428
python python/Plot1DLimit.py -d cards_gaus10_freq/ -m gaus10 -b PFDijetbb20162mm -l 36.428 --massMin 1650 --massMax 7500 --xsecMin 1e-5 --xsecMax 1e4
