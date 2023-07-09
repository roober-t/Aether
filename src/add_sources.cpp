// Copyright 2020, the Aether Development Team (see doc/dev_team.md for members)
// Full license can be found in License.md

#include <iostream>
#include <string>

#include "aether.h"

// -----------------------------------------------------------------------------
// Adds all of the sources to the states. Needs time to get dt.
// -----------------------------------------------------------------------------

void Neutrals::add_sources(Times time, Report &report) {

  std::string function = "add_sources";
  static int iFunction = -1;
  report.enter(function, iFunction);

  precision_t dt = time.get_dt();

  temperature_scgc =
    temperature_scgc +
    dt * (heating_euv_scgc +
          conduction_scgc);
    
  for (int iDir = 0; iDir < 3; iDir++) {
    for (int64_t iSpec = 0; iSpec < nSpecies; iSpec++) {
            
      //calculate velocities based on acceleration:
      species[iSpec].velocity_vcgc[iDir] += dt * species[iSpec].acc_vcgc[iDir];
      species[iSpec].velocity_vcgc[iDir] += dt * species[iSpec].acc_ion_drag[iDir];
      species[iSpec].velocity_vcgc[iDir] += dt * species[iSpec].acc_eddy;
        
    }
  }
    
  calc_bulk_velocity(report);
        

  report.exit(function);
  return;
}
