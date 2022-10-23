USE employees;

CREATE TABLE employee (
	employee_name CHAR(30),
	street CHAR(30),
	city CHAR(15),
	PRIMARY KEY (employee_name)
);

CREATE TABLE company (
	company_name CHAR(30),
	city CHAR(10),
	PRIMARY KEY (company_name)
);

CREATE TABLE works (
	employee_name CHAR(30),
	company_name CHAR(30),
	salary DECIMAL(12,2),
	PRIMARY KEY (employee_name),
	FOREIGN KEY (employee_name) REFERENCES employee(employee_name),
	FOREIGN KEY (company_name) REFERENCES company(company_name)
);

CREATE TABLE manages (
	employee_name CHAR(30),
	managers_name CHAR(30),
	PRIMARY KEY (employee_name),
	FOREIGN KEY (employee_name) REFERENCES employee(employee_name)
);