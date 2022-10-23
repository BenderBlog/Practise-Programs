USE BANK493;

CREATE TABLE customer (
    customer_name CHAR(9),
    customer_street CHAR(20),
    customer_city CHAR(20),
    PRIMARY KEY (customer_name)
);

CREATE TABLE branch (
    branch_name CHAR(30),
    branch_street CHAR(20),
    assets DECIMAL(12,2),
    PRIMARY KEY (branch_name)
);

CREATE TABLE account_of_bank (
    account_number CHAR(10),
    branch_name CHAR(30) NOT NULL,
    balance DECIMAL(12,2),
    PRIMARY KEY (account_number),
    FOREIGN KEY (branch_name) REFERENCES branch(branch_name),
    CONSTRAINT chk_balance CHECK (balance >= 0)
);

CREATE TABLE loan (
    loan_number CHAR(10),
    branch_name CHAR(30),
    amount DECIMAL(12,2),
    PRIMARY KEY (loan_number),
    FOREIGN KEY (branch_name) REFERENCES branch(branch_name)
);

CREATE TABLE depositor (
    customer_name CHAR(9),
    account_number CHAR(10),
    FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
    FOREIGN KEY (account_number) REFERENCES account_of_bank(account_number)
);

CREATE TABLE borrower (
    customer_name CHAR(9),
    loan_number CHAR(10),
    FOREIGN KEY (customer_name) REFERENCES customer(customer_name),
    FOREIGN KEY (loan_number) REFERENCES loan(loan_number)
);