x# Pruebas Manuales para Pipex

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