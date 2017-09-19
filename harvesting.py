# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: step5 --conditions auto:phase1_2017_realistic -s HARVESTING:@standardValidation+@standardDQM+@miniAODValidation+@miniAODDQM --era Run2_2017 --filein file:step3_RAW2DIGI_L1Reco_RECO_DQM_inDQM.root --scenario pp --filetype DQM --geometry DB:Extended --mc -n 100
# import FWCore.ParameterSet.Config as cms
import sys

from Configuration.StandardSequences.Eras import eras

process = cms.Process('HARVESTING',eras.Run2_2017)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.DQMSaverAtRunEnd_cff')
process.load('Configuration.StandardSequences.Harvesting_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(42) # not needed
)


input_list = []
for i in range(2,len(sys.argv)):
	input_list.append(str(sys.argv[i]))


# Input source
process.source = cms.Source("DQMRootSource",
	fileNames = cms.untracked.vstring(input_list)
)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    fileMode = cms.untracked.string('FULLMERGE')
)

# Additional output definition

# Other statements
from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2017_realistic', '')

# Path and EndPath definitions
process.dqmsave_step = cms.Path(process.DQMSaver)

# Schedule definition
process.schedule = cms.Schedule(process.dqmHarvesting,
								process.dqmsave_step)



# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion