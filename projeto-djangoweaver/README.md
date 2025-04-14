# Projeto DjangoWeaver

This project is a Django-based web application designed to host a server that performs the following functionalities:
- Converts API calls between JSON and XML formats.
- Generates PDF reports and outputs based on data fetched from a school API.
- Supports user management and token-based authentication for external users to manage email subscriptions.

---

## Features

- **API Conversion**: Seamlessly convert API calls between JSON and XML formats.
- **PDF Generation**: Generate dynamic PDF reports from data fetched from the school API.
- **User Management**: 
  - Register and manage users.
  - Provide user authentication and authorization.
- **Token Authentication**:
  - External users can authenticate using tokens.
  - Manage email subscriptions securely.

---

## Requirements

### Prerequisites
Ensure you have the following installed:
- Python 3.8+
- Django 4.0+
- pip (Python package installer)

---

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/b0ttas/academic-projects-estgp.git
   cd academic-projects-estgp/projeto-djangoweaver

2. Set Up a Virtual Environment:
   ```bash
   python -m venv env
   source env/bin/activate   # On Windows: env\Scripts\activate

3. Install Dependencies:
   ```bash
    pip install -r requirements.txt

5. Set Up the Database: Run the Django migrations to initialize the database:
   ```bash
   python manage.py migrate

5. Run the Development Server: Start the Django server:
   ```bash
   python manage.py runserver

6. Access the Application: Open http://127.0.0.1:8000 in your browser.

## Usage
1. API Conversion
    Endpoints are available to convert data between JSON and XML formats.

2. PDF Report Generation
    Generate PDF reports with information fetched from the school API.

3. Token-Based Authentication
    External users can authenticate and manage email subscriptions securely using token authentication.

## Folder Structure
    projeto-djangoweaver/
    ├── templates/          # HTML templates for the web interface
    ├── static/             # Static files (CSS, JavaScript, Images)
    ├── manage.py           # Django management script
    ├── requirements.txt    # Python dependencies
    └── README.md           # Project documentation

## License
This project is part of the Academic Projects - ESTGP repository and doesn't have a specific license.

## Contact
For any questions or feedback, please reach out to the repository owner at GitHub Profile.
