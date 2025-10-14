# https://stackoverflow.com/a/27206982
# Creates C resources file from files in given directory
function(create_resources dir output)
    file(WRITE ${output} "")
    file(GLOB bins ${dir}/*)
    foreach(bin ${bins})
        string(REGEX MATCH "([^/]+)$" filename ${bin})
        string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
        file(READ ${bin} filedata HEX)
        string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
        file(APPEND ${output} "const unsigned char ${filename}[] = {${filedata}};\nconst unsigned ${filename}_size = sizeof(${filename});\n")
    endforeach()
endfunction()
