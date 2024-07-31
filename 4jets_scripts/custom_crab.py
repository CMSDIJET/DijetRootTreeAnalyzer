def custom_crab(config):
  print ('>> Customising the crab config')
 
  config.section_('General')

  #config.General.workArea = 'output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/gofs/'
  config.General.workArea = 'output/Wide_Resonances_Run2_Final/combine_rootfiles_alpha0p25/HN_limits/'
  #config.General.instance = 'preprod'

  config.section_("Site")

  config.Site.storageSite = 'T2_CH_CERN'

  config.section_("JobType")

  config.JobType.allowUndistributedCMSSW = True

  config.section_("Data")

  #config.Data.outLFNDirBase = '/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/GOF/Final'
  config.Data.outLFNDirBase = '/store/group/phys_exotica/dijet/Dijet13TeV/ilias/4jets_Run2/Wide_Resonance_Search/HN_limits/'
  #config.Data.unitsPerJob = 50
  #config.Data.totalUnits = 4
