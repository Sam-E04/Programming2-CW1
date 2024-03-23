# Secure Password Manager

## Description
This project is a password manager developed in C++ as part of the coursework for Programming and Algorithms 2. 
It is designed to securely generate, store and retrieve passwords.


<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#explanation">Explanation</a>
      <ul>
        <li><a href="#made-with">Made With</a></li>
        <li><a href="#files">Files</a></li>
        <li><a href="#features">Features</a></li>
      </ul>
    </li>
    <li><a href="#contact">Made By:</a></li>
  </ol>
</details>


## Explanation

### Made With

<img style="width:400px;height:450px;" src="https://upload.wikimedia.org/wikipedia/commons/thumb/1/18/ISO_C%2B%2B_Logo.svg/1200px-ISO_C%2B%2B_Logo.svg.png">

### File Structure

```bash
Programming2-CW1/
├── passwords.txt/  # usernames and passwords are stored here
├── Prog2-Cw1.cpp/  # main c++ code with all functions declared and used
├── Prog2-Cw1.exe/  # compiled .exe file of the cpp file above
└── README.md
```

### Features

+ Handles passwords for multiple unique users
+ Encrypts saved password files using the railfence cipher
+ Generates secure random passwords 
+ Fast password lookup using a retrieve password function

### Functions

+ genPass
+ storePass
+ retrievePass
+ encryptPass
+ decryptPass
+ getNum


## Made By:

Ismail Ahmed Mohamed

im2200078@tkh.edu.eg

<p align="right">(<a href="#readme-top">back to top</a>)</p>
