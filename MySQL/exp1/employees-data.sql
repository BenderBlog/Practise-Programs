USE employees;

INSERT INTO employee(employee_name,street,city)
VALUES
	("Darth Vader","Right","Coruscant"),
	("Darth Maul","Right","Coruscant"),
	("Darth Sidious","Right","Coruscant"),
	("Dooku","Right","Coruscant"),
	("Pawn0000001","Troop","Tatooine"),
	("Pawn0000002","Troop","Naboo"),
	("Pawn0000003","Troop","Coruscant"),
	("Pawn0000004","Troop","Coruscant"),
	("Anakin Skywalker","Left","Tatooine"),
	("Luke Skywalker","Left","Coruscant"),
	("Leia","Left","Alderaan"),
	("Amidala","Left","Naboo");

INSERT INTO works(employee_name,company_name,salary)
VALUES
	("Darth Vader","the Empire",100000),
	("Darth Maul","the Empire",50000),
	("Dooku","the Empire",40000),
	("Darth Sidious","the Empire",200000),
	("Pawn0000001","the Empire",2000),
	("Pawn0000002","the Empire",2000),
	("Pawn0000003","the Empire",2000),
	("Pawn0000004","the Empire",2000),
	("Anakin Skywalker","the Republic",70000),
	("Luke Skywalker","the Republic",80000),
	("Leia","the Republic",100000),
	("Amidala","the Republic",100000);

INSERT INTO company(company_name,city) 
VALUES
	("the Empire","Coruscant"),
	("the Republic","Alderaan");

INSERT INTO manages(employee_name,manager_name)
VALUES
	("Darth Vader","Darth Sidious"),
	("Darth Maul","Darth Sidious"),
	("Dooku","Darth Sidious"),
	("Pawn0000001","Darth Vader"),
	("Pawn0000002","Darth Vader"),
	("Pawn0000003","Darth Vader"),
	("Pawn0000004","Darth Vader"),
	("Anakin Skywalker","Amidala"),
	("Leia","Luke Skywalker");
