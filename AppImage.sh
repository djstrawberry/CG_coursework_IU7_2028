cd /home/anechka/CG_coursework_IU7_2028/build

# Очистим и пересоберём:
rm -rf *
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)

# Скопируем все нужные библиотеки в папку с программой:
mkdir -p portable
cp PlanetSystemDesigner portable/

# Копируем библиотеки Qt:
ldd PlanetSystemDesigner | grep Qt | awk '{print $3}' | xargs -I {} cp {} portable/

# Создаём скрипт запуска:
cat > portable/run.sh << 'EOF'
#!/bin/bash
DIR="$(cd "$(dirname "$0")" && pwd)"
export LD_LIBRARY_PATH="$DIR:$LD_LIBRARY_PATH"
exec "$DIR/PlanetSystemDesigner"
EOF
chmod +x portable/run.sh

# Архивируем:
cd portable
tar czf ../PlanetSystemDesigner_portable.tar.gz *
cd ..

echo "ГОТОВО! Отправь Максиму файл: PlanetSystemDesigner_portable.tar.gz"