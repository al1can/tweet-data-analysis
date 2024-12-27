import selenium
from selenium import webdriver
from selenium.webdriver.common.by import By
from selenium.webdriver.common.keys import Keys
from time import sleep

 Specify the path to the chromedriver executable
PATH = "path_to_chromdriver_file"

# Create a new instance of the Chrome web driver
driver = webdriver.Chrome(PATH)

# Open the Twitter login page
driver.get("https://twitter.com/login")

# Wait for the page to load before continuing
sleep(3)

# Find the username input field using its XPATH and enter a username
username = driver.find_element(By.XPATH,"//input[@name='text']")
username.send_keys("your_username_or_email")

# Find the 'Next' button using its XPATH and click it to move to the password field
next_button = driver.find_element(By.XPATH,"//span[contains(text(),'Next')]")
next_button.click()

# Wait for the next page to load before continuing
sleep(3)

# Find the password input field using its XPATH and enter a password
password = driver.find_element(By.XPATH,"//input[@name='password']")
password.send_keys('your_password')

# Find the 'Log in' button using its XPATH and click it to log in
log_in = driver.find_element(By.XPATH,"//span[contains(text(),'Log in')]")
log_in.click()
