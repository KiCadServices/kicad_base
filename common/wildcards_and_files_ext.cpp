/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2018 Jean-Pierre Charras, jp.charras at wanadoo.fr
 * Copyright (C) 2008 Wayne Stambaugh <stambaughw@gmail.com>
 * Copyright (C) 1992-2018 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file wildcards_and_files_ext.cpp
 * Definition of file extensions used in Kicad.
 */
#include <wildcards_and_files_ext.h>

/**
 * Format wildcard extension to support case sensitive file dialogs.
 *
 * The file extension wildcards of the GTK+ file dialog are case sensitive so using all lower
 * case characters means that only file extensions that are all lower case will show up in the
 * file dialog.  The GTK+ file dialog does support regular expressions so the file extension
 * is converted to a regular expression ( sch -> [sS][cC][hH] ) when wxWidgets is built against
 * GTK+.  Please make sure you call this function when adding new file wildcards.
 *
 * @note When calling wxFileDialog with a default file defined, make sure you include the
 *       file extension along with the file name.  Otherwise, on GTK+ builds, the file
 *       dialog will append the wildcard regular expression as the file extension which is
 *       surely not what you want.
 *
 * @param aWildcard is the extension part of the wild card.
 *
 * @return the build appropriate file dialog wildcard filter.
 */
static wxString formatWildcardExt( const wxString& aWildcard )
{
    wxString wc;
#if defined( __WXGTK__ )

    for( auto ch : aWildcard )
    {
        if( wxIsalpha( ch ) )
            wc += wxString::Format( "[%c%c]", wxTolower( ch ), wxToupper( ch ) );
        else
            wc += ch;
    }

    return wc;
#else
    wc = aWildcard;

    return wc;
#endif
}


wxString AddFileExtListToFilter( int aArgCnt, ... )
{
    wxString files_filter = " (";

    va_list args;
    va_start( args, aArgCnt );

    // Add extensions to the info message:
    for( int ii = 0; ii < aArgCnt; ii++)
    {
        const char* ext = va_arg(args, char*);
        files_filter << " *." << ext;
    }

    files_filter << ")|*.";

    va_start( args, aArgCnt );

    // Add extensions to the filter list, using a formated string (GTK specific):
    for( int ii = 0; ii < aArgCnt; ii++)
    {
        const char* ext = va_arg( args, const char* );

        if( ii > 0 )
            files_filter << ";*.";

        files_filter << formatWildcardExt( ext );
    }

    va_end( args );

    return files_filter;
}


const std::string SchematicSymbolFileExtension( "sym" );
const std::string SchematicLibraryFileExtension( "lib" );
const std::string SchematicBackupFileExtension( "bak" );

const std::string VrmlFileExtension( "wrl" );

const std::string ProjectFileExtension( "pro" );
const std::string SchematicFileExtension( "sch" );
const std::string NetlistFileExtension( "net" );
const std::string ComponentFileExtension( "cmp" );
const std::string GerberFileExtension( "gbr" );
const std::string GerberJobFileExtension( "gbrjob" );
const std::string HtmlFileExtension( "html" );

const std::string LegacyPcbFileExtension( "brd" );
const std::string KiCadPcbFileExtension( "kicad_pcb" );
const std::string PageLayoutDescrFileExtension( "kicad_wks" );

const std::string PdfFileExtension( "pdf" );
const std::string MacrosFileExtension( "mcr" );
const std::string DrillFileExtension( "drl" );
const std::string SVGFileExtension( "svg" );
const std::string ReportFileExtension( "rpt" );
const std::string FootprintPlaceFileExtension( "pos" );
const std::string KiCadLib3DShapesPathExtension( "3dshapes" );  ///< 3D shapes default libpath

const std::string KiCadFootprintLibPathExtension( "pretty" );   ///< KICAD PLUGIN libpath
const std::string LegacyFootprintLibPathExtension( "mod" );
const std::string EagleFootprintLibPathExtension( "lbr" );

const std::string KiCadFootprintFileExtension( "kicad_mod" );
const std::string GedaPcbFootprintLibFileExtension( "fp" );
const std::string SpecctraDsnFileExtension( "dsn" );
const std::string IpcD356FileExtension( "d356" );

const std::string PngFileExtension( "png" );
const std::string JpegFileExtension( "jpg" );


const wxString AllFilesWildcard( _( "All files (*)|*" ) );


wxString SchematicSymbolFileWildcard()
{
    return _( "KiCad drawing symbol files" ) + AddFileExtListToFilter( 1, "sym" );
}


wxString SchematicLibraryFileWildcard()
{
    return _( "KiCad symbol library files" ) + AddFileExtListToFilter( 1, "lib" );
}


wxString ProjectFileWildcard()
{
    return _( "KiCad project files" ) + AddFileExtListToFilter( 1, "pro" );
}


wxString SchematicFileWildcard()
{
    return _( "KiCad schematic files" ) + AddFileExtListToFilter( 1, "sch" );
}


wxString EagleSchematicFileWildcard()
{
    return _( "Eagle XML schematic files" ) + AddFileExtListToFilter( 1, "sch" );
}


wxString EagleFilesWildcard()
{
    return _( "Eagle XML files" ) + AddFileExtListToFilter( 2, "sch", "brd" );
}


wxString NetlistFileWildcard()
{
    return _( "KiCad netlist files" ) + AddFileExtListToFilter( 1, "net" );
}


wxString GerberFileWildcard()
{
    return _( "Gerber files" ) + AddFileExtListToFilter( 1, "pho" );
}


wxString LegacyPcbFileWildcard()
{
    return _( "KiCad printed circuit board files" ) + AddFileExtListToFilter( 1, "brd" );
}


wxString EaglePcbFileWildcard()
{
    return _( "Eagle ver. 6.x XML PCB files" ) + AddFileExtListToFilter( 1, "brd" );
}


wxString PCadPcbFileWildcard()
{
    return _( "P-Cad 200x ASCII PCB files" ) + AddFileExtListToFilter( 1, "pcb" );
}


wxString PcbFileWildcard()
{
    return _( "KiCad printed circuit board files" ) + AddFileExtListToFilter( 1, "kicad_pcb" );
}


wxString KiCadFootprintLibFileWildcard()
{
    return _( "KiCad footprint files" ) + AddFileExtListToFilter( 1, "kicad_mod" );
}


wxString KiCadFootprintLibPathWildcard()
{
    return _( "KiCad footprint library paths" ) + AddFileExtListToFilter( 1, "pretty" );
}


wxString LegacyFootprintLibPathWildcard()
{
    return _( "Legacy footprint library files" ) + AddFileExtListToFilter( 1, "mod" );
}


wxString EagleFootprintLibPathWildcard()
{
    return _( "Eagle ver. 6.x XML library files" ) + AddFileExtListToFilter( 1, "lbr" );
}


wxString GedaPcbFootprintLibFileWildcard()
{
    return _( "Geda PCB footprint library files" ) + AddFileExtListToFilter( 1, "fp" );
}


wxString PageLayoutDescrFileWildcard()
{
    return _( "Page layout design files" ) + AddFileExtListToFilter( 1, "kicad_wks" );
}


// Wildcard for cvpcb component to footprint link file
wxString ComponentFileWildcard()
{
    return _( "KiCad symbol footprint link files" ) + AddFileExtListToFilter( 1, "cmp" );
}


// Wildcard for reports and fabrication documents
wxString DrillFileWildcard()
{
    return _( "Drill files" ) + AddFileExtListToFilter( 3, "drl", "nc", "xnc" );
}


wxString SVGFileWildcard()
{
    return _( "SVG files" ) + AddFileExtListToFilter( 1, "svg" );
}


wxString HtmlFileWildcard()
{
    return _( "HTML files" ) + AddFileExtListToFilter( 2, "htm" , "html" );
}


wxString CsvFileWildcard()
{
    return _( "CSV Files" ) + AddFileExtListToFilter( 1, "csv" );
}


wxString PdfFileWildcard()
{
    return _( "Portable document format files" ) + AddFileExtListToFilter( 1, "pdf" );
}


wxString PSFileWildcard()
{
    return _( "PostScript files" ) + AddFileExtListToFilter( 1, "ps" );
}


wxString ReportFileWildcard()
{
    return _( "Report files" ) + AddFileExtListToFilter( 1, "rpt" );
}


wxString FootprintPlaceFileWildcard()
{
    return _( "Footprint place files" ) + AddFileExtListToFilter( 1, "pos" );
}


wxString Shapes3DFileWildcard()
{
    return _( "VRML and X3D files" ) + AddFileExtListToFilter( 2, "wrl", "x3d" );
}


wxString IDF3DFileWildcard()
{
    return _( "IDFv3 footprint files" ) + AddFileExtListToFilter( 1, "idf" );
}


wxString TextFileWildcard()
{
    return _( "Text files" ) + AddFileExtListToFilter( 1, "txt" );
}


wxString ModLegacyExportFileWildcard()
{
    return _( "Legacy footprint export files" ) + AddFileExtListToFilter( 1, "emp" );
}


wxString ErcFileWildcard()
{
    return _( "Electronic rule check file" ) + AddFileExtListToFilter( 1, "erc" );
}


wxString SpiceLibraryFileWildcard()
{
    return _( "Spice library file" ) + AddFileExtListToFilter( 1, "lib" );
}


wxString SpiceNetlistFileWildcard()
{
    return _( "SPICE netlist file" ) + AddFileExtListToFilter( 1, "cir" );
}


wxString CadstarNetlistFileWildcard()
{
    return _( "CadStar netlist file" ) + AddFileExtListToFilter( 1, "frp" );
}


wxString EquFileWildcard()
{
    return _( "Symbol footprint association files" ) + AddFileExtListToFilter( 1, "equ" );
}


wxString ZipFileWildcard()
{
    return _( "Zip file" ) + AddFileExtListToFilter( 1, "zip" );
}


wxString GencadFileWildcard()
{
    return _( "GenCAD 1.4 board files" ) + AddFileExtListToFilter( 1, "cad" );
}


wxString DxfFileWildcard()
{
    return _( "DXF Files" ) + AddFileExtListToFilter( 1, "dxf" );
}


wxString GerberJobFileWildcard()
{
    return _( "Gerber job file" ) + AddFileExtListToFilter( 1, "gbrjob" );
}


wxString SpecctraDsnFileWildcard()
{
    return _( "Specctra DSN file" ) + AddFileExtListToFilter( 1, "dsn" );
}


wxString IpcD356FileWildcard()
{
    return _( "IPC-D-356 Test Files" ) + AddFileExtListToFilter( 1, "d356" );
}


wxString WorkbookFileWildcard()
{
    return _( "Workbook file" ) + AddFileExtListToFilter( 1, "wbk" );
}


wxString PngFileWildcard()
{
    return _( "PNG file" ) + AddFileExtListToFilter( 1, "png" );
}


wxString JpegFileWildcard()
{
    return _( "Jpeg file" ) + AddFileExtListToFilter( 2, "jpg", "jpeg" );
}
