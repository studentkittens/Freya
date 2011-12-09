require 'find'
require 'tempfile'

$license = <<-eos
/* Cats insert there license here
 * Hmm. Replace this.
 */
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

