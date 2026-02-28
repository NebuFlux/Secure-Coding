# 🔐 CS-405: Secure Coding — Portfolio

**Southern New Hampshire University | CS-405 Secure Coding**
**Developer: Joshua Shoemaker ([@NebuFlux](https://github.com/NebuFlux))**

This repository is the complete portfolio for CS-405 Secure Coding at SNHU, demonstrating applied competency in identifying vulnerabilities, implementing secure C++ solutions, and developing organizational security policy. Each artifact reflects a hands-on approach to the secure software development lifecycle, from low-level memory safety to enterprise-grade policy design.

---
## 📚 Table of Contents

- [Presentation Video](#-presentation-video)
- [Languages & Tools](#️-languages--tools)
- [Coding Exercises](#-coding-exercises)
  - [BufferOverflow.cpp](#️-bufferoverflowcpp)
  - [Encryption.cpp](#-encryptioncpp)
  - [ExceptionHandling.cpp](#️-exceptionhandlingcpp)
  - [GoogleTests.cpp](#-googletestscpp)
  - [NumericOverflow.cpp](#-numericoverflow_shoemaker_joshuacpp)
  - [SQLInjection.cpp](#-sqlinjectioncpp)
- [Course Documents](#-course-documents)
  - [Security Policy](#-cs405-shoemaker-joshua-securitypolicypdf--green-pace-secure-development-policy)
  - [Presentation](#️-cs405-shoemaker-joshua-presentationpdf--green-pace-security-policy-presentation)
  - [Journal](#-cs405-shoemaker-joshua-8-2journalpdf--security-practices-journal)
- [Key Concepts](#-key-concepts-demonstrated)

---

## 📹 Presentation Video

[![CS-405 Final Presentation](https://img.shields.io/badge/YouTube-Watch%20Presentation-red?style=for-the-badge&logo=youtube)](https://youtu.be/4Qexpajtsf8?si=0xeTsjgeQry3NqKb)

---

## 🛠️ Languages & Tools

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=cplusplus&logoColor=white)
![SQLite](https://img.shields.io/badge/SQLite-003B57?style=flat&logo=sqlite&logoColor=white)
![Google Test](https://img.shields.io/badge/Google_Test-Unit_Testing-blue?style=flat)
![PDF](https://img.shields.io/badge/Documentation-PDF-red?style=flat&logo=adobeacrobatreader)

---

## 💻 Coding Exercises

Each program below was provided as a partially complete or intentionally vulnerable C++ exercise. The objective was to identify the vulnerability, implement a secure and policy-compliant solution, and verify correct behavior. Solutions map directly to the Green Pace Secure Development Policy standards STD-001 through STD-010.

---

### 🛡️ BufferOverflow.cpp
`STD-002` · `STD-003` — Range Validation & Safe String Handling

A fixed-size 20-character `char` array accepted user input via `cin >>` with no bounds limit, allowing input longer than the buffer to corrupt adjacent memory including a `const` account number. The fix replaces `cin >>` with `std::cin.getline()` using `sizeof(user_input)` as a hard cap, and uses `cin.fail()` to detect truncation, then clears and flushes the stream with `cin.clear()` and `cin.ignore()`. The user is notified on overflow and limited to three total attempts before the program exits with a non-zero return code, closing the path to repeated abuse.

---

### 🔒 Encryption.cpp
`STD-002` · `STD-009` — Valid Values & RAII Resource Management

The `encrypt_decrypt` function was a stub that copied source bytes to output with no transformation, leaving all file data unprotected. The fix implements XOR-based symmetric encryption by combining each source character with a key character at index `i % key_length`. Since XOR is self-inverse, the same function handles both encryption and decryption. `read_file()` was completed using `std::ifstream` and `std::ostringstream` with error reporting via a custom `errno_msg()` helper, and `save_data_file()` was implemented using `std::ofstream` to write the student name, a cross-platform timestamp, the key, and processed data. Both functions return early and report errors if file operations fail.

---

### ⚠️ ExceptionHandling.cpp
`STD-007` · `STD-010` — Recoverable Throws & Complete Exception Coverage

The program had no exception handling at any level, meaning any runtime failure would crash the process silently with no recovery or diagnostics. A custom `MyException` class was built by inheriting from `std::exception` and overriding `what() const noexcept`, then deployed at multiple call depths alongside `std::logic_error` and `std::domain_error` for division-by-zero and logic failures. The `main()` function wraps all execution in a three-tier catch block (`MyException`, `std::exception`, and `catch(...)`) ensuring no exception can escape unhandled, while inner functions catch and re-throw to propagate context upward.

---

### 🧪 GoogleTests.cpp
`STD-002` · `STD-003` · `STD-006` — Bounds Checking, Safe Access & Assertion-Based QA

The base Google Test fixture was extended with four policy-focused tests to demonstrate the safety difference between `std::vector::at()` and `operator[]`. Two negative tests verify that `at()` correctly throws `std::out_of_range` on an invalid index (`ASSERT_THROW`) and that `operator[]` out-of-bounds access triggers undefined behavior caught by `EXPECT_DEBUG_DEATH` in debug builds. Two positive tests confirm that `at()` succeeds without throwing on a valid index and that `operator[]` is consistent with `at()` when the index is proven safe. Together these tests directly validate STD-002 and STD-003 compliance and are designed to be run under `-fsanitize=address` in CI for full coverage.

---

### 🔢 NumericOverflow_Shoemaker_Joshua.cpp
`STD-008` — Arithmetic Overflow & Underflow Prevention

The `add_numbers` and `subtract_numbers` template functions performed arithmetic across all C++ primitive types with no range guards, silently wrapping or invoking undefined behavior when type limits were exceeded. Pre-operation boundary checks were added using `std::numeric_limits<T>::max()` and `::lowest()`. Comparing the current result against the limit *before* adding or subtracting so undefined behavior is never triggered. When a violation is detected, `std::overflow_error` or `std::underflow_error` is thrown with a detailed `std::ostringstream` message reporting the type, current value, increment, and limit exceeded. The solution was validated as a template across all 14 C++ primitive numeric types including signed, unsigned, and floating-point variants.

---

### 💉 SQLInjection.cpp
`STD-004` — Parameterized Queries & Input Sanitization

The `run_query` function passed raw SQL strings directly to `sqlite3_exec`, making it vulnerable to the tautology-style injections (`OR 1=1`, `OR 'hi'='hi'`) appended by the built-in `run_query_injection` simulator. The industry-standard solution to SQL injection is parameterized queries using `sqlite3_prepare_v2()` with `sqlite3_bind_text()` to bind user input as data rather than executable SQL, which eliminates injection at the architecture level entirely. However, this exercise was intentionally solved using string manipulation to explore whether the problem could be detected and blocked without restructuring the query pipeline. A generic heuristic locates the `NAME=` user input boundary in the query string and scans for any space character beyond it. Since all injected payloads require spaces but valid names do not, this catches every tautology variant without hardcoding specific patterns. If a space is found, the query is blocked and a warning is printed using `std::quoted` to safely display the suspicious input before returning `false`, ensuring `sqlite3_exec` is never reached.

---

## 📄 Course Documents

### 📋 CS405-Shoemaker-Joshua-SecurityPolicy.pdf — Green Pace Secure Development Policy
A complete organizational security policy written for the fictional company Green Pace, standardizing secure coding and architectural practices across a growing development team. The document defines ten security principles mapped to ten C++ coding standards (STD-001 through STD-010), each with compliant and noncompliant code examples, threat level ratings, and recommended static analysis tooling. The policy also covers a Triple-A framework (Authentication, Authorization, Accounting), encryption requirements at rest (AES-256), in flight (TLS 1.3), and in use (homomorphic encryption), plus enforcement procedures, an exceptions process, and a DevSecOps automation strategy integrating Clang, Cppcheck, SonarQube, and Coverity.

### 🎞️ CS405-Shoemaker-Joshua-Presentation.pdf — Green Pace Security Policy Presentation
A technical presentation delivering the Green Pace Secure Development Policy to a development team audience. The deck opens with a defense-in-depth overview using the NHS Cyber Security Architecture model, walks through a threats matrix categorizing all ten risks by likelihood and priority, and maps the ten security principles to their corresponding coding standards. Four slides present live Google Test results from Visual Studio demonstrating policy validation of `at()` vs `operator[]` access safety, followed by a DevSecOps automation summary and a risks/benefits/recommendations analysis identifying current gaps such as missing concurrency rules and third-party dependency scanning.

### 📝 CS405-Shoemaker-Joshua-8-2Journal.pdf — Security Practices Journal
A two-page journal arguing that secure coding must be integrated from the beginning of the SDLC rather than retrofitted at end-stage. The paper covers three themes: early adoption of secure coding standards (citing OWASP and Veracode), cost-benefit justification for proactive remediation in development environments, and the zero trust model as a practical enterprise security framework.

---

## 🔑 Key Concepts Demonstrated

| Concept | Artifact |
|---|---|
| Buffer overflow prevention | BufferOverflow.cpp |
| XOR symmetric encryption & file I/O | Encryption.cpp |
| Multi-level exception hierarchies | ExceptionHandling.cpp |
| Security-focused unit testing | GoogleTests.cpp |
| Numeric overflow/underflow guards | NumericOverflow.cpp |
| SQL injection detection | SQLInjection.cpp |
| Organizational security policy | SecurityPolicy.pdf |
| DevSecOps & threat modeling | Presentation.pdf |
| Secure SDLC & zero trust theory | Journal.pdf |

---

*CS-405 Secure Coding | Southern New Hampshire University | Joshua Shoemaker*
