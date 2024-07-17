
# DATA ANALYTICS APPLICATIONS IN AGRICULTURE 
**(CROP MONITORING APPLICATION)**
***
Data analytics in agriculture involves using large sets of agricultural data to derive insights and make informed decisions. Farmers and agricultural scientists employ various techniques such as predictive modeling, machine learning, and statistical analysis to optimize crop yield, manage resources efficiently, predict weather patterns, monitor soil health, and improve overall farm productivity. By leveraging data analytics, stakeholders in agriculture can make data-driven decisions that lead to sustainable farming practices, increased profitability, and enhanced food security.
## Introduction
This application utilizes data from a network of sensors that measure essential factors such as
nitrogen, potassium, rainfall, phosphorus, soil moisture pH level, temperature, and humidity,
storing it in the cloud or other storage solutions. By analyzing this extensive data, the
application accurately predicts crop yields, helping farmers make informed decisions and
optimize their farming practices. Additionally, it aids in analyzing expected profits based on
historical reports received by the application.

A notable feature of this application is its alert generation system, which automatically activates
irrigation systems and administers fertilizer when soil moisture and pH levels fall below the
threshold. This ensures that crops receive the optimal amount of water and nutrients, promoting
healthier growth and maximizing yield potential. With its precise monitoring and automated
response capabilities, our crop monitoring application enhances efficiency, contributes to
sustainable farming, minimizes resource wastage, and improves overall crop management.

The core issue this research addresses, is the unpredictable nature of crop yields, which affects
farmers' decision-making and income. By predicting crop yields and associated expected
profits, farmers can make more informed decisions about which crops to plant, thereby
minimizing losses and better managing risks. This predictive capability is crucial for stabilizing
the agricultural economy and protecting farmers from drastic price changes.

The study employs machine learning, specifically the decision tree algorithm, to predict crop
yields
## Objectives
- Develop an automatic alert generation system to activate irrigation and fertilizer sprinkling systems by continuously monitoring soil moisture and pH levels.
- Predict crop yields based on real-time data stored in the cloud or other storage solutions.
- Forecast the expected profit of a crop using historical reports submitted by other farmers through the application.
## Methodology
This study aims to develop a comprehensive crop monitoring application with the following key
features and functionalities:

    1. Automatic Alert Generation System

        Implementation:
        - Deploy a network of sensors to monitor critical soil parameters such as moisture and pH levels.
        - Integrate these sensors with a central control system that analyses real-time data.
        - Set threshold levels for soil moisture and ph. When these thresholds are breached, the system will automatically trigger the irrigation or fertilizer sprinkling system to maintain optimal soil conditions

    
    2. Real-time Crop Prediction

        Implementation:
        - Collect real-time data from various sensors measuring factors like nitrogen, potassium, rainfall, temperature, and humidity.
        - Store this data in a cloud database for easy access and analysis.
        - Apply machine learning algorithms, specifically the decision tree algorithm, to analyze the collected data and predict crop yields.
    
    3. Profit Prediction Based on Historical Data

        Implementation:
        - Gather historical data and reports from farmers about crop yields and profits.
        - Store these reports in the cloud database.
        - Analyze the historical data using machine learning techniques to identify patterns and correlations.
        - Use these insights to predict the expected profit for specific crops, helping farmers make informed decisions.



## Data Analysis
The data analysis component of our crop monitoring system involves three main features: alert
generation system, crop prediction, and expected profit prediction. Each feature requires
specific data analysis processes to ensure accurate and efficient functionality.

1. **Alert Generation System**

- Data Collection and Storage:

    -- Real-time Data Collection: Sensor data for soil moisture and pH levels is collected in real-time.

    --Storage: This data is stored in a CSV file using a C++ code that continuously updates with the latest readings.

- Data Preprocessing:

    -- Threshold Setting: Define threshold values for soil moisture and pH levels. These thresholds determine when the irrigation system and fertilizer sprinkling system should be activated.

    -- Data Cleaning: Ensure that the collected data is free from errors or anomalies that could affect the alert system.

- System Implementation:

    -- Alert Generation: When sensor data indicates that soil moisture or pH levels fall below the defined thresholds, the system triggers the irrigation and fertilizer sprinkling systems.

    -- Optimal Condition Monitoring: The system continues to monitor soil conditions. Once optimal levels are restored, the irrigation and fertilization systems are deactivated.

    -- User Notification: Alerts are sent to the user interface of the web application, informing users about the activation and deactivation of the systems.

- Performance Monitoring:

    -- Data Logging: Maintain logs of sensor readings, system activations, and user alerts to monitor system performance and make necessary adjustments.

2. **Crop Prediction**

- Data Collection:

    -- Historical Data: Obtain historical crop data from Kaggle, including various parameters relevant to crop growth.

    -- User Input Data: Collect real-time input data from users via the web application for prediction purposes.

- Data Preprocessing:

    -- Data Cleaning: Remove any inconsistencies or missing values from the historical data to ensure quality.

    --Feature Selection: Identify and select relevant features (e.g., temperature, humidity, soil nutrients) that significantly impact crop growth.

- Model Building:

    -- Algorithm Selection: Implement the ID3 algorithm of the decision tree for crop prediction.

    -- Training: Train the decision tree model using the cleaned and pre-processed historical data.

- Prediction:

    -- Real-time Prediction: When users input new data through the web application and click the predict button, the data is sent to the decision tree model for prediction.
    
    -- Result Display: Display the predicted crop value to the user on the web application.

3. **Expected Profit Prediction**
- Data Collection:

    -- Dummy Data Creation: Create a dummy dataset containing historical reports from farmers, including crop names and associated profits.

    -- Storage: Store this data in a CSV file.

- Data Preprocessing:

    -- Data Cleaning Ensure the dummy data is accurate and free from errors.

    -- Aggregation: Calculate the average profit for each crop based on the historical reports.

- User Interaction:

    -- Crop Name Display: Present the list of crop names to users on the web application.

    -- Profit Display: When a user selects a crop, display the average profit for that crop based on the historical data.

- Analysis:

    -- Profit Calculation: Use statistical methods to calculate the average profit for each crop from the historical data.

## Tech Stack

**Frontend**: HTML, CSS

**Backend and Server side rendering** : Python -> C++ -> Python.


## Run Locally

Clone the project

```bash
  git clone https://github.com/Subrojyoti/crop_monitoring_system.git
```

Go to the project directory

```bash
  cd crop_monitoring_system
```

Install and include dependencies
- Download from nlohmann from [here](https://github.com/nlohmann/json/tree/develop)
- Find the include folder
- Copy and paste the contents of the folder into the directory where all of your `c++` include libraries are stored.




## How to run
1. Open the terminal and compile and run chms.cpp
`g++ chms.cpp -o chms`

`./chms.exe`

2. Open another terminal and compile and run profit_predict.cpp
`g++ profit_predict.cpp -o profit_predict`

`./profit_predict`

3. Compile and run decision.cpp
`g++ decision.cpp -o decision`

`./decision`

4. Now run app.py and it will generate a link for the web application
`python app.py`
## Acknowledgements

 - [IoT in Agriculture](https://ieeexplore.ieee.org/abstract/document/8372905)
 - [Crop price prediction](https://iopscience.iop.org/article/10.1088/1742-6596/1916/1/012042/pdf)
 - [Decision Tree c++ file]( https://github.com/bowbowbow/DecisionTree/blob/master/decision_tree.cpp)
 - [Precision agriculture using IoT data analytics and machine learning](https://www.sciencedirect.com/science/article/pii/S1319157821001282)


## Authors

- [Priya Das](https://github.com/priya-das99)
- [Subrojyoti Paul](https://github.com/Subrojyoti)

