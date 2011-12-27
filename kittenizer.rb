def randomize str
    out = ""

    pos = (0..str.length-1).to_a
    pos.each do |num|
        new_pos = rand(str.length-1)

        # Swap
        tmp = pos[num]
        pos[num] = pos[new_pos]
        pos[new_pos] = tmp;
    end

    pos.each do |num|
        out += str[num]
    end

    return out
end

def kittenize txt
    out = ""
    txt.split.each do |word| 
        out += ( word[0] + 
                 randomize(word[1...(word.length-1)]) + 
                 word[-1] +
                 " "
               )
               randomize word
    end
    return out
end

puts kittenize ARGV[0] unless ARGV.size < 1
