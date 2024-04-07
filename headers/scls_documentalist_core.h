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

#include <scls_foundation.h>

// Use of the "scls" namespace to be more easily usable
namespace scls {

    class Text_Pattern {
        // Class representing a pattern of a text in a SCLS Documentalist project
    public:
        // Most basic Text_Pattern constructor
        Text_Pattern(std::string name, std::string base_text);

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::string base_text() const {return a_base_text;};
        inline std::string name() const {return a_name;};
    private:
        // Base text
        std::string a_base_text = "";
        // Name of the pattern
        std::string a_name = "";
    };

    class Text_Piece {
        // Class representing a text of pieces in a SCLS Documentalist project
    public:
        // Most basic Text_Piece constructor
        Text_Piece(Text_Pattern& pattern);

        // Getters and setters (ONLY WITH ATTRIBUTES)
        inline std::map<std::string, Text_Piece*>& children() {return a_children;};
        inline Text_Pattern& pattern() const {return a_pattern;};
    private:
        // Children of this text
        std::map<std::string, Text_Piece*> a_children = std::map<std::string, Text_Piece*>();
        // Pattern linked to the text
        Text_Pattern& a_pattern;
    };
}

#endif
