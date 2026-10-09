# Playcampus

PlayCampus is a desktop application developed as an academic project
for managing college sports competitions.

The system allows users to manage leagues, teams, players, games, and matchdays,
in addition to offering functionality for tracking and viewing player and team statistics.

## Features

The app supports different user roles:

- Administrator
- Captain
- Student / Player

Some of the main features are:

- Registration and login
- Team and player management
- Creation and management of leagues and seasons
- Management of matchdays and games
- Player selection and assignment
- Viewing statistics
- Viewing schedules
- Player and recruitment management
- Leave and league tracking

## Technologies

- **Language:** C++/CLI
- **User Interface:** Windows Forms
- **Database:** MariaDB
- **Version Control:** Git / GitHub
- **Project Management:** Taiga
- **Testing:** Google Test
- **Code Analysis:** SonarCloud

## Architecture

The system uses a layered architecture:

### Presentation Layer
Responsible for user interaction.

### Domain Layer
Contains the use-case controllers and the main
domain classes.

### Data Access Layer
Includes the classes responsible for communicating with the
MariaDB database through query engines and gateways.

This separation allows for distinct responsibilities
and facilitates the maintenance and evolution of the system.

## Work Methodology

The project was developed by a team of 7 students following
an agile methodology based on iterations.

**Taiga** was used for project management, where the following were managed:

- Product backlog
- Iteration backlog
- User stories
- Tasks
- Acceptance criteria

**GitHub** was used for version control, employing a
branching strategy based on:

- `main`
- `develop`
- specific branches for features and tasks

## Quality and Testing

During development, various tools and techniques were used
to improve software quality:

- Unit and functional testing with **Google Test**
- Manual testing of different application workflows
- Code quality analysis using **SonarCloud**
- Review of the separation of responsibilities among the different layers
- Correction of integration errors
- Reduction of duplicate code
