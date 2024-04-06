//******************
//
// scls_documentalist_test -> headers/scls_documentalist_cpp_ressources.h
//
//******************
//
// scls_documentalist_test description
//
// SCLS Documentalist "Agatha" is a part of the Aster System SCLS project.
// This part is made to easily document C++ files.
// It is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.
// This part is named after one of the most famous author, Agatha Christie.
//
//******************
//
// headers/scls_documentalist_cpp_ressources.h description
//
// This file contains the ressources to use properly C++ with Documentalist.
//
//******************
//
// License (GPLv3)
//
// This file is part of scls_documentalist_test.
//
// scls_documentalist_test is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
//
// scls_documentalist_test is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with scls_documentalist_test. If not, see <https://www.gnu.org/licenses/>.
//

#ifndef SCLS_DOCUMENTALIST_CPP_RESSOURCES
#define SCLS_DOCUMENTALIST_CPP_RESSOURCES

#include <scls_foundation.h>

// Use of the "scls" namespace to be more easily usable
namespace scls {
    // Base text
    static std::string source_cpp_description_text = "This file is the source file of *.";

    // Enumeration of each supported macro types
    enum Preprocessor_Directive_Types { Define, Endif, Ifdef, Ifndef, Include, Unknow };
    struct Preprocessor_Directive {
        // Struct representing datas about macros in a file

        // Description of the macro
        std::string content = "";
        // Name of the macro
        std::string name = "";
        // Type of the defined macro (without the #)
        Preprocessor_Directive_Types type = Preprocessor_Directive_Types::Define;
    };

    // Convert a std::string to a Preprocessor_Directive_Types
    inline Preprocessor_Directive_Types string_to_preprocessor_directive_type(std::string str) {
        if(str == "define") return Preprocessor_Directive_Types::Define;
        else if(str == "endif") return Preprocessor_Directive_Types::Endif;
        else if(str == "ifdef") return Preprocessor_Directive_Types::Ifdef;
        else if(str == "ifndef") return Preprocessor_Directive_Types::Ifndef;
        else if(str == "include") return Preprocessor_Directive_Types::Include;

        return Preprocessor_Directive_Types::Unknow;
    }

    struct Included_File {
        // Struct representing datas about included files

        // Description of the included file
        std::string description = "Iostream is a standart C++ library.\nIt allows the program to communicate with the user easily.";
        // If the included file is a system included file or not
        bool is_system = true;
        // Name of the included file
        std::string name = "iostream";
    };
}

#endif // SCLS_DOCUMENTALIST_CPP_RESSOURCES
