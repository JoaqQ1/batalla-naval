# GUIA PARA CLONAR UN REPOSITORIO GIT HUB
---
#### Tecnologías nesesarias:
* GIT
* Vscode
---
#### Instalación de Git
Antes de empezar, asegúrate de tener Git instalado en tu computadora.
Puedes descargarlo e instalarlo desde el sitio oficial: [Instalar GIT](https://git-scm.com/).
####  Paso a para clonar repositorio
##### 1. Abrir Git Bash
- Dirígete a la carpeta donde deseas clonar el repositorio.
- **Opción 1:** Haz clic derecho en la carpeta y selecciona "Git Bash Here".
<img src="/images/git_bash.png" alt="Git Bash" width="200" height="200" style='border-radius: 10px;'>

- **Opción 2 (si no aparece Git Bash):**  
     1.Copia la ruta de la carpeta.  
        <img src="/images/ruta_completa.png" alt="Ruta completa" width="300" height="200" style='border-radius: 10px;'>
     2.Abre Git Bash manualmente y navega a esa carpeta con el siguiente comando:  
```
cd ruta_que_copiaron_anteriormente
```
3.Deberías ver algo similar en la terminal:
<img src="/images/ejemplo_cd.png" alt="Ruta completa" width="500" height="100" style='border-radius: 10px;'>

##### 2. Obtener el Link del Repositorio en GitHub
**1.** Ve a la página del repositorio en GitHub.
**2.** Haz clic en el botón "Code" y copia la URL:
<img src="/images/git_hub_ejemplo.png" alt="GitHub Ejemplo" width="500" height="300" style='border-radius: 10px;'>
##### 3. Clonar el repositorio
En Git Bash, escribe el siguiente comando reemplazando el enlace por el de tu repositorio:
``git clone https://github.com/JoaqQ1/batalla-naval.git
``
Esto descargará todos los archivos del repositorio en tu carpeta actual.

---
# Instrucciones de ejecución

Este es un juego de Batalla Naval. A continuación, se indican los pasos para ejecutar el código una vez clonado.

### Tecnologías necesarias:
- **GCC** (GNU Compiler Collection)
- **Visual Studio Code** (o el IDE de tu preferencia)

### Pasos para ejecutar el juego:
**1. Acceder a la carpeta del proyecto:** Dirígete a la carpeta batalla-naval con el siguiente comando:
``
cd batalla-naval
``
 **2.Compilar y ejecutar el código:** Una vez dentro de la carpeta, ingresa el siguiente comando para compilar y ejecutar el juego:
``
gcc -o main main.c && ./main
``
¡Listo! Ahora deberías poder jugar Batalla Naval.
