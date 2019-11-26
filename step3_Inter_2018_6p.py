import os

tag = 'PFNo70DijetYearflavorAlgo'

#L = ['signalHistos_bg_JunInter_For2018Scan_DeepJet','Gaussian_bg_JunInter_For2018Scan_DeepJet','signalHistos_bg_JunInter_For2017Scan_DeepJet','Gaussian_bg_JunInter_For2017Scan_DeepJet','signalHistos_bg_JunInter_For2016Scan_DeepJet','Gaussian_bg_JunInter_For2016Scan_DeepJet'] 

L= ['signalHistos_bg_OctInter_For2018Scan_DeepJet','signalHistos_bg_OctInter_For2016Scan_DeepJet','signalHistos_bg_OctInter_For2017Scan_DeepJet']
ns = ''#'ns'
nobtag= ''#'nobtag'

cata=[]
Com_list=[]
Comi=''
index = 0
Total=''

for i in L:
  if 'bg' in i:
    flavor = 'bg'
    model = 'qg'
    cata = ['1b','2b','0b']
    if 'Gaussian' in i:
      cata = ['le1b']

  if 'bb' in i:
    model = 'qq'
    flavor='bb'
    cata = ['Non','le1b','2b']
    if 'Gaussian' in i:
      cata = ['le1b']

  if 'CSVv2' in i:
    Algo = 'CSVv2'
  if 'DeepCSV' in i:
    Algo = 'DeepCSV'
  if 'DeepJet' in i:
    Algo = 'DeepJet'

  if '2016' in i:
    Year = '2016'
  elif '2018' in i:
    Year = '2018'
  else:
    Year = '2017'
  
  for j in cata:
    NewTag = tag.replace('flavor',flavor).replace('model',model).replace('Algo',Algo).replace('Year',Year)
    if 'Gaussian' in i:
      NewTag = NewTag.replace('PF','PFGaus')
    comm1 = 'python python/bTag_ForScan_Inter'+nobtag+'_6p.py -f '+i+'_central_'+j+' -t '+NewTag+' -m '+model+' -c '+j
    comm2 = 'python python/excute2_2018_Inter'+ns+'_6p.py -t '+NewTag+j+' -m '+model+' -p exp -F '+i+'_central_'+j
    Total+=comm1+'\n\n'
    Comi += comm2+'\n\n'
    if index%4 ==0:
       Com_list.append(Comi)
       Comi = ''
    index = index +1
Com_list.append(Comi)
if '' in Com_list:
  Com_list.remove('')
index = 0
for i in Com_list:
   index+=1
   a = open('aloha_Inter2018_'+nobtag+ns+str(index)+'_6p.sh','w+')
   a.write('#!/bin/bash\n\n'+i)
   a.close()
   os.system('chmod 751 aloha_Inter2018_'+nobtag+ns+str(index)+'_6p.sh')
a= open('aloha_Inter2018_'+nobtag+ns+'0_6p.sh','w+')
a.write('#!/bin/bash\n\n'+Total)
a.close()
os.system('chmod 751 aloha_Inter2018_'+nobtag+ns+'0_6p.sh')