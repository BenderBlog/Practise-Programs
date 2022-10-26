USE employees;

#3.9.1 Work for the Republic.
select employee.employee_name, employee.city
from employee, works
where employee.employee_name = works.employee_name 
and works.company_name = "the Republic";

#3.9.2 Work for the Republic and salary have more than 100000 dollars.
select employee.employee_name, employee.street, employee.city, works.salary
from employee, works
where employee.employee_name = works.employee_name 
and works.company_name = "the Republic"
and works.salary >= 100000;

#3.9.3 Not work for the Republic.
select employee_name
from works
where company_name != "the Republic";

#3.9.4 Salary higher than all in the Republic
select employee_name, salary
from works
where salary > all(	select salary from works
	where works.company_name = 'the Republic');
	
#3.9.5 All company which set in the same city as "the Republic"
select company_name
from company
where city = all (select city from company where company_name = 'the Republic');

#3.9.6 Find out the company which got the most staff.
select company_name
from works
group by company_name
having count (distinct employee_name) >= all (
	select (count (distinct employee_name))
	from works
	group by (company_name)
);

#3.9.7 Find out the company which got the most staff.

#First print out all.
select company_name, (avg (salary))
from works
group by company_name;

#Now the solution
select company_name, avg(salary)
from works
group by company_name 
having avg (salary) >= all (
	 select (avg (salary))
	 from works
	 group by company_name
);

#3.10.1 Change the db, now Luke Skyworker should live in Naboo
update employee
set city = "Naboo"
where employee_name = "Luke Skywalker";

#3.10.2 For all in the Emperor, decrease salary.
update works 
set salary = IF(salary > 100000, salary * 0.9, salary * 0.97)
where company_name = "the Empire";