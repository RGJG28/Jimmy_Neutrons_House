# Jimmy_Neutrons_House
Recreación de espacios en 3D de la casa de Jimmy Neutron

El proyecto consiste en recrear un espacio tridimensional utilizando OpenGL proporcionando imágenes de referencia del entorno ficticio seleccionado, en este caso la casa de Jimmy Neutron. Se debieron recrear al menos siete objetos de la imagen de referencia con precisión y crear una ambientación coherente. Se incluyó documentación en español e inglés:
- Un manual de usuario detallando las interacciones en el ambiente virtual
- Un manual técnico con objetivos, diagramas, metodología
- Código documentado

Autor: 
- Jimenez Garcia Rodrigo Gaudencio @RGJG28

## Instalación de dependencias
Es importante que el usuario cuente con las siguientes bibliotecas:
- MSVCP140D.dll
- ucrtbased.dll
- VCRUNTIME140D.dll

Las cuales se incluyen en el paquete redistribuible de Microsoft Visual C++, el cual puedes descargar desde el siguiente link:

[Paquete C++](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist?view=msvc-170)

## Instrucciones
1. Clone o descargue el repositorio desde el enlace proporcionado.
2. Abra la carpeta "Ejecutable".
3. Localice el archivo "ProyectoFinal.exe" y haga doble clic izquierdo para ejecutarlo.
4. Si aparecen mensajes de error sobre archivos faltantes, descargue las bibliotecas necesarias de internet y añádalas a la carpeta "Ejecutable".
5. Una vez ejecutado, se abrirán dos ventanas: una terminal y otra con el programa en blanco.
6. Espere unos segundos o minutos (dependiendo del equipo) hasta que la ventana en blanco desaparezca y aparezca una ventana con contenido de color café. Esto indicará que los objetos se han cargado correctamente y podrá comenzar a explorar los escenarios y sus animaciones.

## Solucion alternativa a bibliotecas .dll faltantes
Copia los archivos DLL manualmente

Si no puedes instalar el paquete redistribuible de Visual C++, puedes intentar copiar los archivos DLL manualmente. Los archivos DLL se encuentran en las siguientes carpetas:

- C:\Windows\System32 (para sistemas de 32 bits)
- C:\Windows\SysWOW64 (para sistemas de 64 bits)
  
Copia los archivos MSVCP140D.dll, ucrtbased.dll y VCRUNTIME140D.dll de estas carpetas a la carpeta del programa.
## Notas

Se modelaron y texturizaron solo algunos objetos de las dos habitaciones mencionadas. Es posible que falten objetos en estas habitaciones y en la casa en general. Además, hay áreas sin texturizar y con errores de modelado. Por lo tanto, el usuario podría encontrar algunos problemas durante su experiencia, similares a los que se encontraban en los videojuegos antiguos.

Desarrollar este proyecto representó un desafío para mí. La falta de planos de la casa me obligó a revisar episodios de la serie para esbozar algunos. Sin embargo, estos planos resultaron ser desproporcionados; las dimensiones del interior no concuerdan con las del exterior. Además, la propia serie presenta inconsistencias, como objetos de diferentes tamaños o ubicaciones cambiantes, e incluso ventanas que no coinciden con la disposición externa.

## Imagenes
### Referencias
Fachada:
![Fachada](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/house.png)
Cuarto deJN:

![JN1](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/Jimmys_room_01.png)
![JN2](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/Jimmys_room_02.png)

Cocina:

![Cocina1](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/kitchen_01.png)
![Cocina2](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/kitchen_02.png)
### Planos
En caso de que alguien decida retormar este proyectom dejo los bosquejos que realicé de la casa, no tienen nada más que lo basico, pero ayudan bastante cuando no se tiene información, solo me hizo falta añadir donde hay ventanas, puertas y la cochera que esta se encuentra del lado de la cocina y el comedor.
- Planta baja
![Planta baja](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/Plano_pb.png)
- Primer piso
![Planta alta](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/Plano_pa.png)
### Resultados
- Fachada y Cuarto de JN
![FyCJN](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/results_01.png)
- Cocina
![Cocina](https://github.com/RGJG28/Jimmy_Neutrons_House/blob/main/Images/results_02.png)
