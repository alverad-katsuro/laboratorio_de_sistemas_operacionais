#!/bin/bash
while getopts b:d:a: flag
do
   case "${flag}" in
      b) backup=${OPTARG};;
      d) dir=${OPTARG};;
      a) archive=${OPTARG};;
   esac
done
if [ -z "$archive" ]; then
  archive=$(pwd)
fi

function copia {
  if [ -d "$itens_back" ]; then
    echo "$dir/$itens_back --> $(date)" >> /home/$USER/diferenca.txt
    $(cp -ru "$itens_back" "$dir/")
  else
    echo "$dir/$itens_back --> $(date)" >> /home/$USER/diferenca.txt
    $(cp -u "$itens_back" "$dir/")
  fi
}

function compara {
  if [ -e "$backup" ] && [ -e "$dir" ]; then
  cd "$backup/"
  local IFS=$(echo -en "\n")
  for itens_back in *; do
    if [ -e "$dir/$itens_back" ]; then
      if [ -d "$itens_back" ]; then
        echo "recursividade"
        local b="$backup/$itens_back"
        local d="$dir/$itens_back"
        #sh $archive/atividades_02.sh -b $b -d $d --> não se reenvoca
        copia
      else
      echo "$backup/$itens_back"
      echo "$dir/$itens_back"
      cmp -s "$backup/$itens_back" "$dir/$itens_back"; echo $?
        if ! cmp -s "$backup/$itens_back" "$dir/$itens_back"; then
          echo "Arquivo diff"
          copia
          #$(mail -s "Arquivos Diferentes encontrados" alverad < diferenca.txt)
        fi
      fi
    else
      copia
    fi
  done
  fi
}
compara