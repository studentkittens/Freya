require 'find'
require 'tempfile'

$license = <<-eos
 /***********************************************************
* This file is part of Freya 
* - A free MPD Gtk3 MPD Client -
* 
* Authors: Christopher Pahl, Christoph Piechula,
*          Eduard Schneider, Marc Tigges
*
* Copyright (C) [2011-2012]
* Hosted at: https://github.com/studentkittens/Freya
*
*              __..--''``---....___   _..._    __
*    /// //_.-'    .-/";  `        ``<._  ``.''_ `. / // /
*   ///_.-' _..--.'_    \                    `( ) ) // //
*   / (_..-' // (< _     ;_..__               ; `' / ///
*    / // // //  `-._,_)' // / ``--...____..-' /// / //  
*  Ascii-Art by Felix Lee <flee@cse.psu.edu>
*
* Freya is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* Freya is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Freya. If not, see <http://www.gnu.org/licenses/>.
**************************************************************/
eos

# Insert license at beginning, using a crappy tmp file.
def do_prepend path
    Tempfile.open File.basename(path) do |tempfile|
        tempfile << $license 

        File.open(path, 'r+') do |file|
            tempfile << file.read
            file.pos = tempfile.pos = 0
            file << tempfile.read
        end
    end
end

# Recurse everything in $pwd
Find.find('./') do |file|
    if file.end_with? ".cc" or file.end_with? ".hh" 
        if File.writable? file
            puts "Adding license to: #{file}"
            do_prepend file
        end
    end
end
