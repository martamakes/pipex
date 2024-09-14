# Pruebas Manuales para Pipex

Utiliza `create-infile.sh` para crear el archivo `infile` con el contenido necesario para cada caso.

## 1. Contar líneas en un archivo

Pipex:
```bash
./pipex infile "cat" "wc -l" outfile
```

Bash equivalent:
```bash
< infile cat | wc -l > outfile_bash
diff outfile outfile_bash
```

## 2. Buscar una palabra y contar ocurrencias

Pipex:
```bash
./pipex infile "grep hello" "wc -l" outfile
```

Bash equivalent:
```bash
< infile grep hello | wc -l > outfile_bash
diff outfile outfile_bash
```

## 3. Convertir texto a mayúsculas y seleccionar líneas

Pipex:
```bash
./pipex infile "tr a-z A-Z" "sed -n 1,5p" outfile
```

Bash equivalent:
```bash
< infile tr a-z A-Z | sed -n 1,5p > outfile_bash
diff outfile outfile_bash
```

## 4. Ordenar líneas y eliminar duplicados

Pipex:
```bash
./pipex infile "sort" "uniq" outfile
```

Bash equivalent:
```bash
< infile sort | uniq > outfile_bash
diff outfile outfile_bash
```

## 5. Contar palabras únicas

Pipex:
```bash
./pipex infile "tr ' ' '\n'" "sort | uniq -c | sort -nr" outfile
```

Bash equivalent:
```bash
< infile tr ' ' '\n' | sort | uniq -c | sort -nr > outfile_bash
diff outfile outfile_bash
```

## 6. Manejo de errores: comando no existente

Pipex:
```bash
./pipex infile "cat" "nonexistentcmd" outfile
```

Bash equivalent:
```bash
< infile cat | nonexistentcmd > outfile_bash
```

## 7. Manejo de errores: archivo de entrada no existente

Pipex:
```bash
./pipex nonexistentfile "cat" "wc -l" outfile
```

Bash equivalent:
```bash
< nonexistentfile cat | wc -l > outfile_bash
```

## 8. Comando con argumentos complejos

Pipex:
```bash
./pipex infile "awk '{print \$1,\$NF}'" "sort -k2" outfile
```

Bash equivalent:
```bash
< infile awk '{print $1,$NF}' | sort -k2 > outfile_bash
diff outfile outfile_bash
```

## 9. Uso de comillas en los comandos

Pipex:
```bash
./pipex infile "grep 'hello world'" "sed 's/hello/bye/g'" outfile
```

Bash equivalent:
```bash
< infile grep 'hello world' | sed 's/hello/bye/g' > outfile_bash
diff outfile outfile_bash
```

## 10. Manejo de espacios en nombres de archivo

Pipex:
```bash
./pipex "input file.txt" "cat" "wc -l" "output file.txt"
```

Bash equivalent:
```bash
< "input file.txt" cat | wc -l > "output file_bash.txt"
diff "output file.txt" "output file_bash.txt"
```

Para cada prueba, primero ejecuta el comando de Pipex y luego el equivalente en Bash. Compara los resultados usando `diff`. Si no hay diferencias, tu implementación de Pipex está funcionando correctamente para ese caso.


CASOS PERMISOS

Claro, te proporcionaré varios ejemplos para probar diferentes escenarios de permisos de archivos. Estos comandos te ayudarán a simular situaciones comunes que tu programa pipex debería manejar correctamente.

1. Archivo de entrada sin permisos de lectura:

```bash
touch input_file
chmod 000 input_file
./pipex input_file "cat" "wc -l" output_file
```

2. Archivo de salida en un directorio sin permisos de escritura:

```bash
mkdir no_write_dir
chmod 555 no_write_dir
./pipex input_file "cat" "wc -l" no_write_dir/output_file
```

3. Intentar ejecutar un comando sin permisos de ejecución:

```bash
echo "#!/bin/bash" > my_script.sh
echo "echo Hello" >> my_script.sh
chmod -x my_script.sh
./pipex input_file "./my_script.sh" "wc -l" output_file
```

4. Archivo de entrada que es un directorio:

```bash
mkdir input_dir
./pipex input_dir "cat" "wc -l" output_file
```

5. Archivo de salida que es un directorio:

```bash
mkdir output_dir
./pipex input_file "cat" "wc -l" output_dir
```

6. Archivo de entrada que no existe:

```bash
./pipex nonexistent_file "cat" "wc -l" output_file
```

7. Comando que no existe:

```bash
./pipex input_file "nonexistent_command" "wc -l" output_file
```

8. Archivo de entrada simbólico que apunta a un archivo sin permisos:

```bash
touch no_perm_file
chmod 000 no_perm_file
ln -s no_perm_file symlink_file
./pipex symlink_file "cat" "wc -l" output_file
```

9. Intentar escribir en un archivo de solo lectura:

```bash
touch readonly_output
chmod 444 readonly_output
./pipex input_file "cat" "wc -l" readonly_output
```

10. Usar un archivo de dispositivo como entrada:

```bash
./pipex /dev/null "cat" "wc -l" output_file
```

Estos ejemplos cubren una variedad de situaciones que tu programa pipex debería manejar adecuadamente. Asegúrate de probar cada uno y verificar que tu programa maneje los errores correctamente, mostrando mensajes de error apropiados y saliendo con los códigos de estado adecuados.

Recuerda limpiar los archivos y directorios de prueba después de usarlos:

```bash
rm -rf input_file output_file no_write_dir my_script.sh input_dir output_dir nonexistent_file no_perm_file symlink_file readonly_output
```
