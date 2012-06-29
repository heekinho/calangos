gcc script.c -o script
rm -f -r *.egg
rm -f -r result
egg-texture-cards *.png *.jpg output.egg
egg-list-textures output.egg | ./script
rm output.egg
egg-palettize -d result -dm result -dr result -opt -nodb *.egg
rm -f -r *.egg
