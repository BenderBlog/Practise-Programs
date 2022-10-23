USE BANK493;

# Disable foreign key checks, since all clear.
SET FOREIGN_KEY_CHECKS = 0;

# These two are at the "bottom".
DROP TABLE BANK493.loan;
DROP TABLE BANK493.depositor;

# These two are at the "middle".
DROP TABLE BANK493.account_of_bank;
DROP TABLE BANK493.borrower;

# These two are at the "top".
DROP TABLE BANK493.branch;
DROP TABLE BANK493.customer;

# Re-enable it.
SET FOREIGN_KEY_CHECKS = 1;
