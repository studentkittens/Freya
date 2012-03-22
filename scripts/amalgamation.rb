#!/usr/bin/ruby
require 'base64'
require 'thread'


SOURCE = <<-eos

    #include "CompileSymbols.hh"

    /////////////////////////////
    // Autogenerated Stuff     //
    // generated by:           //
    // scripts/amalgamation.rb //
    // - do not edit!          //
    /////////////////////////////
    
    namespace Utils 
    {
        CompileSymbols::CompileSymbols()
        {
            %s
        }
    }
eos

NODE = <<-eos
            compile_defs.insert(std::pair<std::string,const char*>(%s,
            %s));
            //////////////////////////
eos

def read_in_content file_path
    content = "\n"
    File.open(file_path).each do |line|
        content += ((" " * 20) + "\"" + line.chomp!.gsub(/"/,'\"') + "\"\n")
    end
    return content
end

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

def end_with_one_of? string, suffixes
    suffixes.each do |suff|
        return true if string.end_with? suff
    end
    false
end

def traverse_defs root
    lines = ""
    thread = []
    semaphore = Mutex.new

    Dir.entries(root).each do |file|
        thread << Thread.new do
            path = root + file
            data = ""
            if file.end_with? ".glade" then
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

def compose 
    result = ""
    result += traverse_defs "ui/"
    result += traverse_defs("ui/gfx/")
    return SOURCE % result
end

puts compose 
