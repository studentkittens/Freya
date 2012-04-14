#!/usr/bin/ruby
# 
# Creates a C++ source file that creates strings suitable
# for compiling XML (Glade) and Imagefiles in the Freya binary.
#
# It's done by associating each filepath (as key) with it's contents
# (as value) in a hashmap (std::map)
#
# If lookups are succesful those files can be loaded directly from memory
# (though they have to be loaded initially with the binary) 
#
# Images will be Base64 encoded to be able to server as string.
# (gdk-pixbuf-csource produces large uncompressed data strings)
#
# Pros:
#  - Failsafe (no load errors possible)
#  - Bit faster loading, as it's loaded in one block
#  - Will be loaded transparently 
#
# Cons:
#  - Fattens the binary (not even 900K at the moment though)
#  - Images need to be decoded (fast enough though)
#
#  This script is licensed under the Pizzalicense,
#  buy me a pizza if you like it, do what you like otherwise.
#
#  Also, excuse my bad Ruby knowledge.

require 'base64'
require 'thread'

# Header for the .cc file
# CompileSymbols.{cc|hh} already exists
# in the sourcetree, but the hashmap 
# is empty by default.
SOURCE = <<-eos

    #include "CompileSymbols.hh"

    /////////////////////////////
    // Autogenerated Stuff     //
    // generated by:           //
    // scripts/amalgamation.rb //
    // - do not edit! -        //
    /////////////////////////////
    
    namespace Utils 
    {
        CompileSymbols::CompileSymbols()
        {
            %s
        }
    }
eos

# One element that is getting pushed into the hashmap
# (using the path as key, and a const char * as value since
#  we work with literals and no copying is done then)
NODE = <<-eos
            compile_defs.insert(std::pair<std::string,const char*>(%s,
            %s));
            //////////////////////////
eos

# Read an XML File by path and return escaped content
def read_in_content file_path
    content = "\n"
    File.open(file_path).each do |line|
        content += ((" " * 20) + "\"" + line.chomp!.gsub(/\\/,"\\\\").gsub(/"/,'\"') + "\\n\"\n")
    end
    return content
end

# Base64 encode image and align it in nicely viewable rows
# (this is actually useless since nobody will read the file, but well..)
def base64_encode_image img_path
    content = File.open(img_path).read
    enc = Base64.strict_encode64(content)
    
    result = "\""

    counter = 0
    maxlen  = 150
    
    until counter >= enc.length do
        result += (enc[counter,maxlen] + "\"\n\"")
        counter += maxlen
    end
    
    unless result.end_with? "\"\"" then
        result += "\""
    end
    return result
end

# Checks if a string ends with on of the strings
# in the array suffixes
def end_with_one_of? string, suffixes
    suffixes.each do |suff|
        return true if string.end_with? suff
    end
    false
end

# Go through the filetree
def traverse_defs root
    lines = ""
    thread = []
    semaphore = Mutex.new

    Dir.entries(root).each do |file|
        thread << Thread.new do
            path = root + file
            data = ""
            if end_with_one_of?(file,[".glade",".svg"]) then
                data = read_in_content path
            elsif end_with_one_of?(file,[".png",".jpg",".jpeg"]) 
                data = base64_encode_image path
            end
                
            unless data.empty? 
                semaphore.synchronize do
                    lines += NODE % ["\"" + path + "\"",data]
                end
            end
        end
    end

    thread.each { |th| th.join }

    return lines
end

######

result = ""
result += traverse_defs "ui/"
result += traverse_defs("ui/gfx/")
puts (SOURCE % result)
