FROM robtry/opencv-420

# Cria o diretório de trabalho
WORKDIR /home/dev/app

# Copia o conteúdo local para o contêiner
COPY . .

# Comando de entrada padrão
CMD ["bash"]