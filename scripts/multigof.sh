#inclusive
python python/RunToys.py -b PFDijet2016 --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijet2016_Full/ -i fits_2016_11_28/PFDijet2016_Full/DijetFitResults_PFDijet2016.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijet2016 -c config/dijet.config -d fits_2016_11_28/PFDijet2016_Full/ -t fits_2016_11_28/PFDijet2016_Full/toys_Freq_s0_PFDijet2016.root -l 36428 --data

#MT
python python/RunToys.py -b PFDijetbb20160mt --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijetbb20160mt_Full/ -i fits_2016_11_28/PFDijetbb20160mt_Full/DijetFitResults_PFDijetbb20160mt.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijetbb20160mt -c config/dijet.config -d fits_2016_11_28/PFDijetbb20160mt_Full/ -t fits_2016_11_28/PFDijetbb20160mt_Full/toys_Freq_s0_PFDijetbb20160mt.root -l 36428 --data


python python/RunToys.py -b PFDijetbb20161mt --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijetbb20161mt_Full/ -i fits_2016_11_28/PFDijetbb20161mt_Full/DijetFitResults_PFDijetbb20161mt.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijetbb20161mt -c config/dijet.config -d fits_2016_11_28/PFDijetbb20161mt_Full/ -t fits_2016_11_28/PFDijetbb20161mt_Full/toys_Freq_s0_PFDijetbb20161mt.root -l 36428 --data


python python/RunToys.py -b PFDijetbb20162mt --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijetbb20162mt_Full/ -i fits_2016_11_28/PFDijetbb20162mt_Full/DijetFitResults_PFDijetbb20162mt.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijetbb20162mt -c config/dijet.config -d fits_2016_11_28/PFDijetbb20162mt_Full/ -t fits_2016_11_28/PFDijetbb20162mt_Full/toys_Freq_s0_PFDijetbb20162mt.root -l 36428 --data


#MM
python python/RunToys.py -b PFDijetbb20160mm --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijetbb20160mm_Full/ -i fits_2016_11_28/PFDijetbb20160mm_Full/DijetFitResults_PFDijetbb20160mm.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijetbb20160mm -c config/dijet.config -d fits_2016_11_28/PFDijetbb20160mm_Full/ -t fits_2016_11_28/PFDijetbb20160mm_Full/toys_Freq_s0_PFDijetbb20160mm.root -l 36428 --data


python python/RunToys.py -b PFDijetbb20161mm --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijetbb20161mm_Full/ -i fits_2016_11_28/PFDijetbb20161mm_Full/DijetFitResults_PFDijetbb20161mm.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijetbb20161mm -c config/dijet.config -d fits_2016_11_28/PFDijetbb20161mm_Full/ -t fits_2016_11_28/PFDijetbb20161mm_Full/toys_Freq_s0_PFDijetbb20161mm.root -l 36428 --data


python python/RunToys.py -b PFDijetbb20162mm --freq -c config/dijet.config --lumi 36428 --fit-region Full -d fits_2016_11_28/PFDijetbb20162mm_Full/ -i fits_2016_11_28/PFDijetbb20162mm_Full/DijetFitResults_PFDijetbb20162mm.root -t 1000 -s 0

python python/PlotGOF.py -b PFDijetbb20162mm -c config/dijet.config -d fits_2016_11_28/PFDijetbb20162mm_Full/ -t fits_2016_11_28/PFDijetbb20162mm_Full/toys_Freq_s0_PFDijetbb20162mm.root -l 36428 --data

