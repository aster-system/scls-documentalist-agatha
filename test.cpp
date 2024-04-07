//******************
//
// SCLS Documentalist -> test.cpp
//
//******************
//
// SCLS Documentalist description
//
// SCLS Documentalist "Agatha" is a part of the Aster System SCLS project.
// This part is made to easily document C++ files.
// It is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.
// This part is named after one of the most famous author, Agatha Christie.
//
//******************
//
// test.cpp description
//
// This file represents a test of the library.
// It also provide a way to document the library.
// Indeed, this documentation is made with SCLS Documentalist.
//
//******************
//
// License (GPLv3)
//
// This file is part of SCLS Documentalist.
//
// SCLS Documentalist is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// SCLS Documentalist is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with SCLS Documentalist. If not, see <https://www.gnu.org/licenses/>.
//

#include <iostream>
#include "scls_documentalist.h"

int main() {
    scls::Project* project = scls::cpp_scls_format_project();

    project->set_description("SCLS Documentalist \"Agatha\" is a part of the Aster System SCLS project.\nThis part is made to easily document C++ files.\nIt is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.\nThis part is named after one of the most famous author, Agatha Christie.");
    project->set_name("scls_documentalist_test");

    // project.save_all("scls_documentalist_test");

    return 0;
}
