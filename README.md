# pedagocical school project
the project consists to re-develop the programs "nm" and "otool" from unix systems

# documentation:
https://github.com/aidansteele/osx-abi-macho-file-format-reference

# libraries:
https://upload.wikimedia.org/wikipedia/commons/6/67/Deb_File_Structure.svg

# implementation
both programs uses the same basic structure : a (t_common*) defined into common.h

this design choice has been made to allow me to use the sames function withous have to re-implement them.
