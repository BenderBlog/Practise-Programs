# 基于第一次上机创建的银行数据库，创建一个视图branch_detail，能够显示所有支行的存款客户数量、存款总额、贷款客户数量、贷款总额。
USE BANK493;
CREATE VIEW branch_detail AS
SELECT * FROM
(
	SELECT branch.branch_name AS name_dep,
	 	count(distinct (depositor.customer_name)) as count_dep,
	 	sum(account_of_bank.balance)
 	from branch natural join depositor natural join account_of_bank
 	group by branch_name
) AS deposite,
(
	select branch.branch_name as name_loan,
		count(distinct (borrower.customer_name)) as count_loan,
		sum(loan.amount)
	from branch natural join borrower natural join loan
	group by branch_name
) AS loan
WHERE deposite.name_dep=loan.name_loan;

# 在account的account_number属性上建立索引
CREATE INDEX account_number_index ON BANK493.account_of_bank(account_number);

# 创建角色银行经理branch_manager，银行经理具有插入、删除和更新branch表的权限。
# Use root privilege!
USE BANK493;
CREATE ROLE branch_manager;
GRANT DELETE,UPDATE ON BANK493.branch TO branch_manager;
SELECT User,is_role FROM mysql.user WHERE User="branch_manager";
SHOW GRANTS FOR branch_manager;
GRANT branch_manager TO 'superbart'@'localhost';


