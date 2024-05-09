////////////////////////////
//
// SCLS Documentalist -> scls_documentalist.h
//
//******************
//
// SCLS Documentalist description
//
// SCLS Documentalist is a part of the SCLS library.
//
// SLCS is a set of C++ library, made to make C++ development easier.
// For more information, see https://aster-system.github.io/aster-system/projects/scls.html.
//
// The Documentalist part is a part of the library made to handle easily file documentation.
// For that, it uses the SCLS Format "Mary" C++ format.
// For more information, see https://aster-system.github.io/aster-system/scls/documentalist.html.
//
//******************
//
// scls_documentalist.h description
//
// This file includes each needed files in SCLS Documentalist.
//
//******************
//
// License description (GPL V3.0)
//
// This file is part of SCLS Documentalist project.
//
// SCLS Documentalist is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// SCLS Documentalist is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with SCLS Documentalist. If not, see <https://www.gnu.org/licenses/>.
//
//******************
//
// This project uses the Aster System SCLS Format "Mary" code format, in the public domain.
// It is also formatted using the Aster System SCLS Documentalist "Agatha" library under the GPL V3.0 license.
// See https://aster-system.github.io/aster-system/projects/scls.html for more informations.
//
////////////////////////////


////////////////////////////////////////////////////////
//****************************************************//
////////////////////////////////////////////////////////


////////////////////////////
//
// Avoid multiple header repetitions
//
////////////////////////////

#ifndef SCLS_DOCUMENTALIST
#define SCLS_DOCUMENTALIST

////////////////////////////
//
// Included files
//
////////////////////////////

// "scls_foundation.h" -> File containing the core of SCLS.
#ifdef __ASTER_DEV
#include "../../scls-foundation-leonhard/scls_foundation.h"
#else
#include <scls_foundation.h>
#endif // __ASTER_DEV
// "headers/scls_documentalist_core.h" -> File containing the core of the library.
#include "headers/scls_documentalist_core.h"
// "headers/scls_documentalist_project.h" -> File allowing to use complex project.
#include "headers/scls_documentalist_project.h"


////////////////////////////////////////////////////////
//****************************************************//
////////////////////////////////////////////////////////


////////////////////////////
//
// Avoid multiple header repetitions
//
////////////////////////////

#endif // SCLS_DOCUMENTALIST
