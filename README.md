# carDet
The real-time transmission system for intelligent parking based on YOLO algorithm is an enterprise level management system aimed at improving the safety and efficiency of intelligent parking for automobiles
**Intelligent Parking Real-time Transmission System**

**Project Overview:**

The Intelligent Parking Real-time Transmission System is an enterprise-level management system aimed at enhancing the safety and efficiency of intelligent parking for automobiles. The system primarily handles two core modules: network real-time transmission and YOLO model training. By addressing the issue of frontend-backend speed mismatch, we strive to achieve efficient and stable data transmission while continuously optimizing the YOLO model to meet the demands of real-time transmission.

**Key Features:**

- Real-time Transmission: Achieve rapid real-time transmission of vehicle image data by optimizing network transmission and model inference speed.
- Intelligent Parking: Utilize the YOLO algorithm for vehicle recognition and detection of vacant parking spaces to enhance the automation and efficiency of parking processes.
- Security Assurance: Employ efficient algorithms and technologies to ensure the accuracy and safety of vehicle recognition and parking operations.
- Management System: Provide a user-friendly management interface for administrators to monitor and manage the system.

**System Architecture:**

The system comprises the following two main modules:

1. Network Real-time Transmission Module: Responsible for handling the real-time transmission of vehicle image data, ensuring data is transferred rapidly and stably from the frontend to the backend.
2. YOLO Model Training Module: Continuously optimize the YOLO model to improve the accuracy and speed of vehicle recognition and parking space detection.

**Installation and Configuration:**

1. Clone the project code repository:

```
git clone https://github.com/your_username/project.git
```

2. Install dependencies:

```
cd project
pip install -r requirements.txt
```

3. Configure the project:

- In the `config.py` file, configure network transmission parameters and YOLO model parameters.
- Ensure the correct paths are configured to load the model and data.

**Usage Guide:**

1. Start the real-time transmission module:

```
python realtime_transmission.py
```

2. Start the YOLO model training module:

```
python yolo_training.py
```

3. Access the management system interface:

```
http://localhost:8000/admin
```

**Contributors:**

- [@contributor1](https://github.com/contributor1)
- [@contributor2](https://github.com/contributor2)

**Issues and Feedback:**

For any questions or feedback, please submit an issue on the GitHub project page or contact us via email: [contact@example.com](mailto:contact@example.com)

**License:**

This project is licensed under the [MIT License](LICENSE).
