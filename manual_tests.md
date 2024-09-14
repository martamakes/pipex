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
./pipex infile "tr ' ' '\n'" "sort -nr" outfile
```

Bash equivalent:
```bash
< infile tr ' ' '\n' | sort -nr > outfile_bash
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

# Pruebas de permisos para pipex

## Preparación
1. Asegúrate de que tu programa `pipex` esté compilado y listo para usar.
2. Crea un directorio de pruebas y navega a él:
   ```bash
   mkdir pipex_test && cd pipex_test
   ```

## Casos de prueba

1. Archivo de entrada sin permisos de lectura:
   ```bash
   echo "Contenido de prueba" > input_file
   chmod 000 input_file
   ./pipex input_file "cat" "wc -l" outfile
   < input_file cat | wc -l > out_perm_bash
   ```

2. Archivo de salida en un directorio sin permisos de escritura:
   ```bash
   mkdir no_write_dir
   chmod 555 no_write_dir
   ./pipex input_file "cat" "wc -l" no_write_dir/outfile
   < input_file cat | wc -l > no_write_dir/out_perm_bash
   ```

3. Intentar ejecutar un comando sin permisos de ejecución:
   ```bash
   echo '#!/bin/bash\necho "Hola"' > my_script.sh
   chmod -x my_script.sh
   ./pipex input_file "./my_script.sh" "wc -l" outfile
   < input_file ./my_script.sh | wc -l > out_perm_bash
   ```

4. Archivo de entrada que es un directorio:
   ```bash
   mkdir input_dir
   ./pipex input_dir "cat" "wc -l" outfile
   < input_dir cat | wc -l > out_perm_bash
   ```

5. Archivo de salida que es un directorio:
   ```bash
   mkdir output_dir
   ./pipex input_file "cat" "wc -l" output_dir
   < input_file cat | wc -l > output_dir
   ```

6. Archivo de entrada que no existe:
   ```bash
   ./pipex nonexistent_file "cat" "wc -l" outfile
   < nonexistent_file cat | wc -l > out_perm_bash
   ```

7. Archivo de entrada simbólico que apunta a un archivo sin permisos:
   ```bash
   echo "Contenido de prueba" > no_perm_file
   chmod 000 no_perm_file
   ln -s no_perm_file symlink_file
   ./pipex symlink_file "cat" "wc -l" outfile
   < symlink_file cat | wc -l > out_perm_bash
   ```

8. Intentar escribir en un archivo de solo lectura:
   ```bash
   echo "Contenido inicial" > readonly_output
   chmod 444 readonly_output
   ./pipex input_file "cat" "wc -l" readonly_output
   < input_file cat | wc -l > readonly_output
   ```

## Verificación
Después de cada prueba, compara el comportamiento de tu programa `pipex` con el comportamiento de Bash:
1. Verifica los códigos de salida:
   ```bash
   echo $?  # Para el comando de Bash
   ```
2. Compara los contenidos de los archivos de salida (si se crearon):
   ```bash
   diff outfile out_perm_bash
   ```
3. Verifica los mensajes de error en la salida estándar de error.

## Notas
- Asegúrate de limpiar los archivos y directorios creados entre pruebas.
- Presta atención a los mensajes de error y los códigos de salida, ya que son cruciales en el manejo de errores de permisos.
- Tu programa `pipex` debería manejar estos casos de manera similar a como lo hace Bash, incluyendo la generación de mensajes de error apropiados.

Recuerda limpiar los archivos y directorios de prueba después de usarlos:

```bash
rm -rf input_file output_file no_write_dir my_script.sh input_dir output_dir nonexistent_file no_perm_file symlink_file readonly_output
```
