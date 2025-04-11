# Classes Dashboard Project

This project is a web-based dashboard for managing classes, built using Spring Boot for the backend and React for the frontend. It was developed as part of academic projects at ESTGP.

## Features

- User-friendly interface for managing subjects, classes and users (students and teachers).
- Integration of Spring Boot backend with a React frontend.

## Screenshots

Here are some screenshots showcasing the application:

- Screenshot 1: [Dashboard Overview](./screenshots/login-landing.png)
- Screenshot 2: [Class Management](./screenshots/subject.png)
- Screenshot 3: [User Settings](./screenshots/admin-users.png)

> More files are available in the "screenshots" path.

## Installation

### Backend (Spring Boot)
1. Clone the repository:
   ```bash
   git clone https://github.com/b0ttas/academic-projects-estgp.git
   cd academic-projects-estgp/es-spring-react-classes-dashboard/spring
   
2. Build the project:
   ```bash
   mvn clean install
   
3. Run the application:
   ```bash
   mvn spring-bbot:run

## Frontend (React)
1. Navigate to the frontend directory:
   ```bash
   cd academic-projects-estgp/es-spring-react-classes-dashboard/spring/spring/src/main/webapp
   
2. Install dependencies:
   ```bash
   npm install
   
3. Start the development server: 
   ```bash
   npm start

## Usage

1. Open a web browser and navigate to http://localhost:3000.
2. Log in or sign up to manage classes and schedules.
   
Note: By default, new users have the least authorizations (ie. students), changing this requires the use of an admin account.
      This account must be defined on the backend.
