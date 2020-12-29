/*
 * A32NX
 * Copyright (C) 2020 FlyByWire Simulations and its contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <MSFS/MSFS.h>

#include "AutopilotInterface.h"
#include "main.h"

AutopilotInterface AutopilotInterface;

__attribute__((export_name("Autopilot_gauge_callback"))) extern "C" bool Autopilot_gauge_callback(FsContext ctx,
                                                                                                  int service_id,
                                                                                                  void* pData) {
  // print event type
  switch (service_id) {
    case PANEL_SERVICE_PRE_INSTALL: {
      // connect to sim connect
      return AutopilotInterface.connect();
    };

    case PANEL_SERVICE_PRE_DRAW: {
      // read data & inputs, step model, write output
      return AutopilotInterface.update(static_cast<sGaugeDrawData*>(pData)->dt);
    };

    case PANEL_SERVICE_PRE_KILL: {
      // disconnect sim connect
      AutopilotInterface.disconnect();
    } break;
  }

  // success
  return true;
}