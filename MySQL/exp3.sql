USE BANK493;

# 基于第一次上机创建的银行数据库，创建一个函数，为所有存款账户增加1%的利息。

DELIMITER //
CREATE FUNCTION raise_money () RETURNS VARCHAR(255)
BEGIN
	update account_of_bank set account_of_bank.balance = account_of_bank.balance * 1.01;
	return "Success";
END
DELIMITER ;
select raise_money();

# 创建一个新表branch_total，用于存储各个支行的存款总额（表中有branch_name和total_balance两个属性）。
# 然后在这个表上，创建一个触发器，实现当有用户存款变动（包括增加、删除和更新）时，brach_total表中的存款总额跟着自动更新。

CREATE TABLE branch_total (
	branch_name varchar(50) primary key,
	total_balance numeric(10,2),
	foreign key(branch_name) references branch(branch_name)
);

CREATE TRIGGER branch_total_insert_trigger
AFTER
INSERT ON account_of_bank
FOR EACH ROW 
BEGIN 
	INSERT INTO branch_total(branch_name, branch_total)
	VALUES (new.branch_name, new.balance)
	ON DUPLICATE KEY UPDATE
	total_balance = total_balance + new.balance;
END

CREATE TRIGGER branch_total_update_trigger 
AFTER 
UPDATE ON account_of_bank
FOR EACH ROW
BEGIN
UPDATE branch_total 
	SET total_balance = total_balance - old.balance + new.balance
	WHERE branch_name = old.branch_name;
END

CREATE TRIGGER branch_total_delete_trigger
AFTER
DELETE ON account_of_bank
FOR EACH ROW
BEGIN
	UPDATE branch_total
	SET total_balance = total_balance - old.balance
	WHERE branch_name = old.branch_name;
END
