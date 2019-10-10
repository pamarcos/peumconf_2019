# Inyección de librerías dinámicas

Este es un ejemplo sencillo para entender cómo se puede inyectar una librería para alterar el funcionamiento normal de una aplicación en Linux y macOS.

En este caso, se ha modificado el método `open` de manera que podemos alterar el fichero que en realidad lee una aplicación. En particular, hemos modificado los ficheros de imagen que leerá un visor de imagen cualquiera, aunque puede aplicarse a cualquier tipo de fichero.

Para que funcione, en macOS el SIP tiene que estar deshabilitado. Se hace reiniciando en modo recovery y ejecutando `csrutil disable`. Lo aconsejable es hacer el proceso inverso una vez se haya dejado de probar, ejecutando `csrutil enable` de nuevo en modo recovery. [Documentación de macOS al respecto](https://developer.apple.com/library/archive/documentation/Security/Conceptual/System_Integrity_Protection_Guide/ConfiguringSystemIntegrityProtection/ConfiguringSystemIntegrityProtection.html).

Para compilar, ejecuta `make`. El script `run.sh` es un helper que ayuda a ejecutar procesos tras definir correctamente las variables de entorno que inyectan nuestra librería en el dynamic loader. Esto es, setean `LD_PRELOAD` en Linux y `DYLIB_INSERT_LIBRARIES` en macOS.

e.g. macOS
```
./run.sh /Applications/Preview.app/Contents/MacOS/Preview
```

e.g. Linux
```
./run.sh eog
```