<a id="readme-top"></a>

 | [![Contributors][contributors-shield]][contributors-url] | [![Forks][forks-shield]][forks-url] | [![Stargazers][stars-shield]][stars-url] | [![Issues][issues-shield]][issues-url] | [![MIT License][license-shield]][license-url] | [![LinkedIn][linkedin-shield]][linkedin-url] |

<br />
<div align="center">
  <a href="https://github.com/kossadda/SmartCalc_v2.0">
    <img src="./misc/img/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">SmartCalc v2.0</h3>

  <p align="center">
    <br />
    <a href="https://github.com/kossadda/SmartCalc_v2.0"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/kossadda/SmartCalc_v2.0">View Demo</a>
    /
    <a href="https://github.com/kossadda/SmartCalc_v2.0/issues/new?labels=bug&template=bug-report---.md">Report Bug</a>
    /
    <a href="https://github.com/kossadda/SmartCalc_v2.0/issues/new?labels=enhancement&template=feature-request---.md">Request Feature</a>
  </p>
</div>


<details>
  <summary><strong>Table of Contents</strong></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#scientific-calculator">Scientific Calculator</a></li>
        <li><a href="#credit-calculator">Credit Calculator</a></li>
        <li><a href="#deposit-calculator">Deposit Calculator</a></li>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#required-software">Required software</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>


## About The Project

![Scientific](./misc/img/calculator.png) <br>
![Credit](./misc/img/credit.png) <br>
![Deposit](./misc/img/deposit.png) <br>

The goal of this project is to implement an extended version of a standard calculator using the C++ programming language and the MVC (Model-View-Controller) pattern. In addition to basic arithmetic operations such as addition, subtraction, multiplication, and division, the calculator supports the evaluation of arithmetic expressions with precedence as well as certain mathematical functions (sine, cosine, logarithm, etc.). The calculator also supports the use of the variable `x` and plotting the corresponding function. Additional features include credit and deposit calculators.

### Scientific Calculator

- The program is developed in C++ using the C17 standard and the g++ compiler, along with additional libraries and QT modules.
- The code resides in the `src` folder.
- The build process is managed with a Makefile, which includes standard GNU targets: `all`, `install`, `uninstall`, `clean`, `dvi`, `dist`, and `test`. The installation is placed in the `bin` directory.
- The program is developed following structured programming principles.
- The code is formatted according to the Google Style Guide.
- Unit tests covering the modules responsible for expression evaluation are implemented using the GTest library.
- The graphical user interface (GUI) is built using QT libraries with an API for C17.
- The input can include both integers and floating-point numbers (written using a dot). Numbers in exponential notation are also supported.
- The calculation is performed after the full expression is entered and the `=` button is pressed.
- The program evaluates arbitrary expressions in infix notation, with or without the `x` variable.
- The user can plot a graph of a function defined by an expression containing the `x` variable (complete with axes, a scale indicator, and a grid with adaptive spacing).
    - The user can adjust the graph's scale.
- The domain and range of functions are limited to at least the interval from `-1,000,000` to `1,000,000`.
    - The domain and range for graph plotting must be specified by the user.
- The program guarantees accuracy up to 7 decimal places.
- The user can input up to 255 characters.
- Infix notation expressions support the following arithmetic operations and mathematical functions:

**Arithmetic Operators**:

| Operator Name         | Infix Notation (Classic)   | Prefix Notation (Polish Notation) | Postfix Notation (Reverse Polish Notation) |
| --------------------- | -------------------------- | --------------------------------- | ----------------------------------------- |
| Parentheses           | (a + b)                    | (+ a b)                           | a b +                                     |
| Addition              | a + b                      | + a b                             | a b +                                     |
| Subtraction           | a - b                      | - a b                             | a b -                                     |
| Multiplication        | a * b                      | * a b                             | a b *                                     |
| Division              | a / b                      | / a b                             | a b \                                     |
| Exponentiation        | a ^ b                      | ^ a b                             | a b ^                                     |
| Modulo                | a mod b                    | mod a b                           | a b mod                                   |
| Unary Plus            | +a                         | +a                                | a+                                        |
| Unary Minus           | -a                         | -a                                | a-                                        |

> Expressions where the multiplication sign `*` is omitted are handled.

**Functions**:

| Description                        | Function  |   
| ----------------------------------- | --------- |  
| Calculates cosine                  | cos(x)    |   
| Calculates sine                    | sin(x)    |  
| Calculates tangent                 | tan(x)    |  
| Calculates arccosine               | acos(x)   | 
| Calculates arcsine                 | asin(x)   | 
| Calculates arctangent              | atan(x)   |
| Calculates square root             | sqrt(x)   |
| Calculates natural logarithm       | ln(x)     | 
| Calculates common logarithm        | log(x)    |

It has two working modes:

- Standard mode for evaluating mathematical expressions (including expressions with the `x` variable)
- Graphing mode for plotting mathematical expressions.

1. Most calculations and features were verified against the calculator at `web2.0calc.com`. Additional details were sourced from Google and Windows calculators.
2. The input is validated interactively to help users correct errors in mathematical expressions.
3. Trigonometric and logarithmic functions require parentheses after them.
4. The calculator supports implicit multiplication between numbers/functions/parentheses, such as `5log(2)`.
5. Scientific notation and the Euler number are supported. For example, `5e-2` is interpreted as `0.05`, and `5e*2` as `5*(Euler's number)*2`.
6. When using the `x` variable, a field for entering the value of `x` appears, which is also validated interactively.
7. An expression will not be evaluated if the `x` variable's value is invalid.
8. The domain and range for graphing must be specified by the user and are limited to `{1000000:-1000000}`.
9. A step size for the graph can be specified for more accurate plots. The allowed step size ranges from `{0.001:100}` (note: smaller steps increase computation time for large ranges).
10. Graph zooming and panning are supported.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Credit Calculator

The `Credit Calculator` mode offers:

- Input: total loan amount, loan term, interest rate, loan date, type (annuity or differentiated), early repayment options (shortening the term or reducing payments)
- Output: monthly payment, total interest, total payment, and a monthly report

1. Based on the advanced credit calculator from `calcus.ru`.
2. All user input fields are validated interactively.
3. The loan amount ranges from `{0.01:999999999999.99}`.
4. The loan term ranges from `{1:600}` months, `{1:50}` years.
5. The interest rate ranges from `{0.001:999}`.
6. Upon pressing `Calculate`, a full loan report is generated, including monthly breakdowns and total payments.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Deposit Calculator

The `Deposit Calculator` mode offers:

- Input: deposit amount, deposit term, interest rate, tax rate, deposit date, payment frequency, interest capitalization, and operations (additional deposits or partial withdrawals)
- Output: accrued interest, tax amount, total balance at the end of the term, and a monthly report

1. Based on the deposit calculator from `calcus.ru`.
2. All user input fields are validated interactively.
3. The deposit amount ranges from `{0.01:999999999999.99}`.
4. The deposit term ranges from `{1:18250}` days, `{1:600}` months, `{1:50}` years.
5. The interest rate ranges from `{0.001:999}`.
6. Additional deposits and partial withdrawals are supported.
7. The same range applies to deposit amounts and withdrawal/additional deposit fields.
8. Various interest capitalization periods are available.
9. Upon pressing `Calculate`, a full report is generated, including monthly breakdowns, total interest, and taxes.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


### Built With

<p align="center">
  <p>
    <a href="https://www.cplusplus.com/">
      <img src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" width="80" height="30">
    </a>
    <a href="https://cmake.org/">
      <img src="https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white" width="80" height="30">
    </a>
    <a href="https://www.qt.io/">
      <img src="https://img.shields.io/badge/Qt-%23217346.svg?style=for-the-badge&logo=Qt&logoColor=white" width="80" height="30">
    </a>
  </p>
</p>

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Getting Started

To get a local copy and run it, follow these steps.

### Required software

* CMake
  ```
  sudo apt install cmake
  ```

* Qt
  ```
  sudo apt install qt6-base-dev
  ```

### Installation

1. Install the required software (if missing)
2. Clone the repository
    ```sh
    git clone git@github.com:kossadda/SmartCalc_v2.0.git
    ```
3. Run the installation program
    ```sh
    make install
    ```
4. Run the program manually (`SmartCalc_v2.0/bin/smartcalc`) or enter the command
    ```
    make run
    ```

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Contributing:

<a href="https://github.com/kossadda/SmartCalc_v2.0/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=kossadda/SmartCalc_v2.0" alt="contrib.rocks image" />
</a>

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>


## Contact

Pervin Gabilov - [Telegram](https://t.me/kossadda) / [e-mail](gabiov1997@gmail.com)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ССЫЛКИ И ИЗОБРАЖЕНИЯ MARKDOWN -->
[contributors-shield]: https://img.shields.io/github/contributors/kossadda/SmartCalc_v2.0.svg?style=for-the-badge
[contributors-url]: https://github.com/kossadda/SmartCalc_v2.0/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/kossadda/SmartCalc_v2.0.svg?style=for-the-badge
[forks-url]: https://github.com/kossadda/SmartCalc_v2.0/network/members
[stars-shield]: https://img.shields.io/github/stars/kossadda/SmartCalc_v2.0.svg?style=for-the-badge
[stars-url]: https://github.com/kossadda/SmartCalc_v2.0/stargazers
[issues-shield]: https://img.shields.io/github/issues/kossadda/SmartCalc_v2.0.svg?style=for-the-badge
[issues-url]: https://github.com/kossadda/SmartCalc_v2.0/issues
[license-shield]: https://img.shields.io/github/license/kossadda/SmartCalc_v2.0.svg?style=for-the-badge
[license-url]: https://github.com/kossadda/SmartCalc_v2.0/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/othneildrew
