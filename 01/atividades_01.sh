echo "1 * * * * echo 'hello crontab' >> /home/$USER/Documentos/hello_cron.txt" | crontab -
echo "* * 1 * * $(pwd)/atividade_02.sh" | crontab -