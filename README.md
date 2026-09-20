# Playcampus

PlayCampus es una aplicación de escritorio desarrollada como proyecto académico
para la gestión de competiciones deportivas universitarias.

El sistema permite gestionar ligas, equipos, jugadores, partidos y jornadas,
además de ofrecer funcionalidades de seguimiento y consulta de estadísticas.

## Funcionalidades

La aplicación contempla diferentes roles de usuario:

- Administrador
- Capitán
- Estudiante / Jugador

Entre las principales funcionalidades se encuentran:

- Registro e inicio de sesión
- Gestión de equipos y jugadores
- Creación y gestión de ligas y temporadas
- Gestión de jornadas y partidos
- Convocatoria y asignación de jugadores
- Consulta de estadísticas
- Seguimiento de ligas
- Consulta de calendarios
- Gestión de jugadores y fichajes
- Abandono y seguimiento de ligas

## Tecnologías

- **Lenguaje:** C++/CLI
- **Interfaz:** Windows Forms
- **Base de datos:** MariaDB
- **Control de versiones:** Git / GitHub
- **Gestión del proyecto:** Taiga
- **Testing:** Google Test
- **Análisis de código:** SonarCloud

## Arquitectura

El sistema utiliza una arquitectura por capas:

### Capa de presentación
Formularios desarrollados con Windows Forms encargados de la
interacción con el usuario.

### Capa de dominio
Contiene los controladores de los casos de uso y las principales
clases del dominio.

### Capa de acceso a datos
Incluye las clases encargadas de comunicarse con la base de datos
MariaDB mediante buscadores y pasarelas.

Esta separación permite mantener responsabilidades diferenciadas
y facilita el mantenimiento y evolución del sistema.

## Metodología de trabajo

El proyecto fue desarrollado por un equipo de 7 estudiantes siguiendo
una metodología ágil basada en iteraciones.

Para la gestión del proyecto se utilizó **Taiga**, donde se gestionaron:

- Product backlog
- Iteration backlog
- User stories
- Tasks
- Acceptance criteria

Para el control de versiones se utilizó **GitHub**, utilizando una
estrategia de ramas basada en:

- `main`
- `develop`
- ramas específicas para funcionalidades y tareas

## Calidad y testing

Durante el desarrollo se utilizaron diferentes herramientas y técnicas
para mejorar la calidad del software:

- Pruebas unitarias y funcionales con **Google Test**
- Pruebas manuales de diferentes flujos de la aplicación
- Análisis de calidad del código mediante **SonarCloud**
- Revisión de la separación de responsabilidades entre las diferentes capas
- Corrección de errores de integración
- Reducción de código duplicado

## Contexto

Proyecto académico desarrollado en equipo en la asignatura
**Ampliación a la Ingeniería del Programario — UPC**.

Equipo formado por 7 estudiantes.

## Capturas

### Inicio de sesión
![Login](images/login.png)

### Gestión de ligas
![Ligas](images/ligas.png)

### Gestión de equipos
![Equipos](images/equipos.png)
