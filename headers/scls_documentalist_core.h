//******************
//
// scls_documentalist_test -> headers/scls_documentalist_core.h
//
//******************
//
// scls_documentalist_core description
//
// SCLS Documentalist "Agatha" is a part of the Aster System SCLS project.
// This part is made to easily document C++ files.
// It is made for SCLS, but you can still use it in your project. However, it may be a little less adapted.
// This part is named after one of the most famous author, Agatha Christie.
//
//******************
//
// headers/scls_documentalist_core.h description
//
// This file contains the core of SCLS Documentalist.
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

#ifndef SCLS_DOCUMENTALIST_CORE
#define SCLS_DOCUMENTALIST_CORE

// "scls_foundation.h" -> File containing the core of SCLS.
#ifdef __ASTER_DEV
#include "../../dev_part/dev_part/scls_foundation.h"
#else
#include <scls_foundation.h>
#endif // __ASTER_DEV

// Keyword to define a variable in a balise
#ifndef SCLS_DOCUMENTALIST_VARIABLE_KEYWORD
#define SCLS_DOCUMENTALIST_VARIABLE_KEYWORD "var"
#endif // SCLS_DOCUMENTALIST_VARIABLE_KEYWORD

#define SCLS_DOCUMENTALIST_ERROR_CUTTER std::string("=")
#define SCLS_DOCUMENTALIST_FORCED_USER_DEFINED_VARIABLE_ERROR std::string("-_\"{<;>" )

// Use of the "scls" namespace to be more easily usable
namespace scls {

    struct Text_Pattern_Base_Variable {
        // Struct representing a variable in a text pattern
        // Content if the variable
        std::string content = "";
        // Start of a line if a break of line occurs
        std::string line_start = "";
        // Name of the variable
        std::string name = "";
    };

    // Know easily if a std::vector<Text_Pattern_Base_Variable> contains a variable by name or not
    inline bool _contains_pattern_variable_by_name(std::vector<Text_Pattern_Base_Variable>& to_test, std::string variable_name) {
        for(int i = 0;i<static_cast<int>(to_test.size());i++) {
            if(to_test[i].name == variable_name) return true;
        }
        return false;
    };

    class Text_Pattern {
        // Class representing a complete pattern of a text in a SCLS Documentalist project
    public:
        // Most basic Text_Pattern constructor
        Text_Pattern(String name, String base_text);
        // Text_Pattern destructor
        virtual ~Text_Pattern();

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline String base_text() const {return a_base_text;};
        inline String name() const {return a_name;};
        inline String set_base_text(String new_base_test) {a_base_text = new_base_test;};
    private:
        // Base text
        String a_base_text = "";
        // Name of the pattern
        String a_name = "";
    };
}

#endif
