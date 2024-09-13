#!/bin/bash

# Nombre del archivo
INFILE="infile"

# Crear el archivo y escribir contenido
cat << EOF > $INFILE
Hello, this is a test file for Pipex
This line contains the word hello again
SOME LINES ARE IN UPPERCASE
some lines are in lowercase
1234 This line starts with numbers
    This line has leading spaces
This line has trailing spaces    
This is line number 8
This is line number 9
This is the final line, number 10
EOF

# Añadir algunas líneas duplicadas
echo "This is a duplicate line" >> $INFILE
echo "This is a duplicate line" >> $INFILE

# Añadir una línea con caracteres especiales
echo "Special chars: !@#$%^&*()_+" >> $INFILE

# Añadir una línea muy larga
printf '%*s' 100 | tr ' ' 'a' >> $INFILE
echo "" >> $INFILE

# Añadir algunas líneas con tabulaciones
echo -e "Column1\tColumn2\tColumn3" >> $INFILE
echo -e "Value1\tValue2\tValue3" >> $INFILE

# Añadir una línea vacía
echo "" >> $INFILE

# Añadir una línea con una cita
echo "As Shakespeare said, \"To be or not to be\"" >> $INFILE

# Imprimir mensaje de confirmación
echo "File '$INFILE' has been created successfully."

# Mostrar las primeras líneas del archivo
echo "Here are the first few lines of the file:"
head -n 5 $INFILE