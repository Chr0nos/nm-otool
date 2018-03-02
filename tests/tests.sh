#!/bin/zsh
make
echo "starting tests"
diff <(./ft_nm bin32bits) <(nm bin32bits)
diff <(./ft_nm libft/build/string/ft_strsplit.o) <(nm libft/build/string/ft_strsplit.o)
diff <(./ft_nm ../scope/scop) <(nm ../scope/scop)
diff <(./ft_nm /usr/local/bin/python3) <(nm /usr/local/bin/python3)
echo "done"
