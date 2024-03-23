#include <iostream>
#include <fstream>
#include <elf.h>
#include <vector>
#include "ElfFileParserCreator.hpp"
#include "IElfFileParser.hpp"
#include "FileHeader.hpp"
#include "ProgramHeader.hpp"
#include "SectionHeader.hpp"


int main(int argc, char** argv) //ENDIANES... 
{
    if (argc != 2) {
        std::cerr << "You provided wrong number of arguments...\n";
        return 1;
    }

    std::ifstream* l_fileStream { new std::ifstream(argv[1], std::ios::binary) };
    auto* l_elfFileParser { parser::ElfFileParserCreator::createElfFileParser(l_fileStream) };

    auto l_fileHeader { l_elfFileParser->parseFileHeader() };

    auto l_phnum { 0 };
    auto l_shnum { 0 };
    if (l_fileHeader.discriminator == FileHeaderDiscriminator::SYSTEM_VERSION_32_BIT)
    {
        l_phnum = l_fileHeader.header32.e_phnum; // can be moved to ElfFileParser...?
        l_shnum = l_fileHeader.header32.e_shnum; // can be moved to ElfFileParser...?
    }
    else if (l_fileHeader.discriminator == FileHeaderDiscriminator::SYSTEM_VERSION_64_BIT)
    {
        l_phnum = l_fileHeader.header64.e_phnum; // can be moved to ElfFileParser...?
        l_shnum = l_fileHeader.header64.e_shnum; // can be moved to ElfFileParser...?
    }
    std::vector<ProgramHeader> l_programHeaders { l_elfFileParser->parseProgramHeaders(l_phnum) };
    std::vector<SectionHeader> l_sectionHeaders { l_elfFileParser->parseSectionHeaders(l_shnum) };

    delete l_elfFileParser;
    delete l_fileStream;

    return 0;
}