# 0：什么是SQL
    全称：Structed Query Language 结构化查询语言
    功能：访问，增删改查
    实现：一种RDBMS程序MySQL
    RDBMS:relational Database Management System
        0.1：特点：
            数据表格存储
            每行为记录名称
            每列为数据域
            行列组成表单
            若干表单组成database
        0.2：相关术语
            数据库：关联表的集合
            数据表：数据矩阵
            列：相同类型 （邮政编码）
            行：一个对象的各种数据 （用户订阅）
            冗余：储存量被数据
            主键：用于查询数据 唯一 不重复 不为空 用于检索速度快
            外键：关联俩表
            复合键：（组合键）将多个列表作为一个索引
            索引：快速访问特定信息 是对数据值的一种结构
            参照完整性：不允许引用不存在实体
# 1:通过 SQL 语句定义列（字段）结构，创建后表格自带行列框架

# 2:SQL大学习
#   1.1：基本查询语句
#       1.1：SELECT 1.2：where

SELECT * FROM equipment_borrow;     表名

SELECT equipment_name, borrower FROM equipment_borrow;      只看设备名称和借阅人

SELECT * FROM equipment_borrow 
WHERE status = '已借出';        列 条件筛选

SELECT * FROM equipment_borrow 
WHERE borrower = '张三' AND status = '已借出';      查询“张三借的且未归还” 的记录：
#       1.3：ORDED BY       升序：ASC 降序：SESC

SELECT * FROM users ORDER BY age;

SELECT * FROM products ORDER BY price DESC;

-- 先按部门（dept）升序，同部门内按工资（salary）降序
SELECT * FROM employees ORDER BY dept ASC, salary DESC;

-- 按字符串长度（name列的长度）排序
SELECT name FROM students ORDER BY LENGTH(name) ASC;

SELECT * FROM users WHERE status = 'active' ORDER BY register_time DESC;
#       1.4：DISTINCT       去重指定列（或多列组合）
-- 从 users 表中查询不重复的城市（去除重复城市）
SELECT DISTINCT city FROM users;

-- 查询不重复的（城市+职业）组合（即同一城市且同一职业的记录只保留一条）
SELECT DISTINCT city, profession FROM users;

-- 统计有多少个不同的城市（去重后城市的数量）
SELECT COUNT(DISTINCT city) AS unique_cities FROM users;

-- 查询年龄大于30的用户中，不重复的职业
SELECT DISTINCT profession FROM users WHERE age > 30;
#       1.5：LIMIT
-- 从第 10 条记录开始（偏移量 10，即跳过前 10 条），返回 5 条记录（常用于第 2 页，每页 5 条）
SELECT * FROM users LIMIT 10, 5;
    
-- 获取年龄最大的前 3 位用户（先按年龄降序，再取前 3 条）
SELECT * FROM users ORDER BY age DESC LIMIT 3;

问：不需要循环嘛？
答：比如目的是一页十行 那么翻页操作就是由PYTHON实现的           python和sql分开合作
    （通用公式：偏移量 = (页码-1)*每页条数）
    # 假设用户点击了第 3 页，每页显示 5 条
    page = 3  # 页码，由前端页面传入（如 URL 参数 ?page=3）
    page_size = 5  # 每页条数，固定值或可配置

    # 计算偏移量
    offset = (page - 1) * page_size

    # 拼接 SQL，动态传入 offset 和 page_size
    sql = f"SELECT * FROM users LIMIT {offset}, {page_size};"

    # 执行 SQL 并返回结果给前端（第 3 页数据）
#   1.2：表操作语句
#       2.1：CREAT TABLE
    CREATE TABLE equipment_borrow
        id INT PRIMARY KEY AUTO_INCREMENT,      id列名  INT数据类型   AUTO_INCREMENT：id值在新纪录时自动递增
        equipment_name VARCHAR(100) NOT NULL,      ARCHAR(100)：最多储存100个字符      NOT NULL不为空
        equipment_type VARCHAR(50),  
        borrower VARCHAR(50) NOT NULL,  
        borrow_date DATETIME NOT NULL,  
        return_date DATETIME,       DATETIME：日期时间类型。
        status ENUM('已借出', '已归还') DEFAULT '已借出' 
    );
#       2.2：ALTER TABLE
ADD:
-- 向 users 表添加一个 age 列（整数类型，非空）
ALTER TABLE users ADD age INT NOT NULL;

-- 向表末尾添加一个 nullable 的 email 列
ALTER TABLE users ADD email VARCHAR(100);

MODIFY 或 CHANGE:
-- 将 users 表的 age 列改为 SMALLINT 类型，并允许为 NULL
ALTER TABLE users MODIFY age SMALLINT NULL;

-- 将列名从 age 改为 user_age，同时类型改为 TINYINT
ALTER TABLE users CHANGE age user_age TINYINT;

DROP COLUMN
-- 删除 users 表中的 email 列
ALTER TABLE users DROP COLUMN email;

ADD PRIMARY KEY添加主键约束:
-- 为 students 表的 id 列添加主键
ALTER TABLE students ADD PRIMARY KEY (id);

添加索引（ADD INDEX）
-- 为 users 表的 username 列添加普通索引（索引名可选，默认自动生成）
ALTER TABLE users ADD INDEX idx_username (username);

重命名表（RENAME TO）
-- 将 users 表重命名为 user_info
ALTER TABLE users RENAME TO user_info;

添加外键约束（ADD FOREIGN KEY）
-- 为 orders 表的 user_id 列添加外键，关联 users 表的 id 列
ALTER TABLE orders ADD FOREIGN KEY (user_id) REFERENCES users(id);

问：外键约束什么玩意
答：比如 订单表 和 用户表 必须一一对应 防止 孤儿数据 可以一起操作 比如删除

    举个栗子：
            -- 创建主表 users
            CREATE TABLE users (
            user_id INT PRIMARY KEY,  -- 主键
            username VARCHAR(50)
            );

            -- 创建子表 orders，定义外键约束
            CREATE TABLE orders (
            order_id INT PRIMARY KEY,
            order_no VARCHAR(20),
            user_id INT,
            -- 外键约束：orders.user_id 必须匹配 users.user_id 的值
            FOREIGN KEY (user_id) REFERENCES users(user_id)
                ON DELETE CASCADE  -- 级联删除：若主表用户被删除，子表关联订单也删除
                ON UPDATE CASCADE  -- 级联更新：若主表 user_id 被修改，子表关联字段同步更新
            );有点像类的继承
#       2.3：DROP TABLE     删除整个表
DROP TABLE [IF EXISTS] 表名1, 表名2, ...;

-- 同时删除 orders 和 order_details 表
DROP TABLE IF EXISTS orders, order_details;

#   1.3：子查询与连接
#       3.1：INNER JOIN     关联多个表并筛选出匹配数据
举个例子

                    |   users.id    users.name
                    |       1       张三
                    |       2       李四
                    |       3       王五

                |  orders.order_id  orders.user_id      orders.product
                |   101                 1                   手机	
                |   102                 1	                电脑	
                |   103	                2	                耳机	
                |   104	                4	                键盘

        SELECT 
            users.name,
            orders.order_id, 
            orders.product
        FROM users
        INNER JOIN orders 
            ON users.id = orders.user_id;  -- 连接条件：用户ID匹配

输出：
        |   name	order_id	    product
        |   张三	    101	        手机
        |   张三	    102	        电脑
        |   李四	    103	        耳机
#       3.2：LEFT JOIN      以左表为基准，返回左表的所有记录，以及右表中与左表匹配的记录。
沿用上个例子
如下操作：
        SELECT 
            users.name, 
            orders.order_id, 
            orders.product
        FROM users  -- 左表：users
        LEFT JOIN orders  -- 右表：orders
            ON users.id = orders.user_id;  -- 连接条件：用户ID匹配
结果：
        name	order_id	product	
        张三	101	        手机	
        张三	102	        电脑	
        李四	103	        耳机	
        王五	NULL	    NULL


多关联：
-- 以 users 为基准，关联 orders 和 products
    SELECT u.name, o.order_id, p.product_name
    FROM users u
    LEFT JOIN orders o ON u.id = o.user_id
    LEFT JOIN products p ON o.product_id = p.id;  -- 继续左连接第三张表
#       3.3：RIGHT JOIN     右表为基准      抓住主键就好办
SELECT 列名
FROM 左表
RIGHT JOIN 右表 
  ON 左表.关联列 = 右表.关联列;  -- 连接条件

SELECT 
  users.name,  -- 左表列
  orders.order_id, orders.product  -- 右表列
FROM users  -- 左表
RIGHT JOIN orders  -- 右表（基准表）
  ON users.id = orders.user_id;  -- 连接条件

结果：
            |   name	    order_id	product	
            |   张三	    101	        手机	
            |   张三	    102	        电脑	
            |   李四	    103	        耳机	
            |   NULL	    104	        键盘
#       3.4：FULL JOIN      非原生支持      需要用UNION模拟
    -- 步骤1：左连接（保留左表所有记录）
    SELECT u.name, o.order_id, o.product
    FROM users u
    LEFT JOIN orders o ON u.id = o.user_id

    UNION  -- 合并结果并去重

    -- 步骤2：右连接（保留右表中未被左连接包含的记录）
    SELECT u.name, o.order_id, o.product
    FROM users u
    RIGHT JOIN orders o ON u.id = o.user_id
    WHERE u.id IS NULL;  -- 只取右表中左表无匹配的记录

#   1.4：性能优化与安全性
#       4.1:EXPLAIN         分析 SQL 查询执行计划
举个例子：
有一张 orders 表（order_id 主键，user_id 普通列，无索引

首先执行：
-- 分析单表查询
    EXPLAIN SELECT * FROM users WHERE age > 30;

    -- 分析关联查询
    EXPLAIN SELECT u.name, o.order_id 
    FROM users u 
    JOIN orders o ON u.id = o.user_id 
    WHERE u.age > 30;

执行后，MySQL 会返回一张 “执行计划表”，包含多个字段（如 type、key、rows 等），每个字段都代表查询执行的关键信息。执行后，MySQL 会返回一张 “执行计划表”，包含多个字段（如 type、key、rows 等），每个字段都代表查询执行的关键信息。

执行计划可能显示：
    type: ALL（全表扫描）
    key: NULL（未用索引）
    rows: 10000（预估扫描 1 万行）
    Extra: Using where

给 user_id 添加索引：
ALTER TABLE orders ADD INDEX idx_user_id (user_id);
再次执行 EXPLAIN，会发现：
    type: ref（使用索引匹配）
    key: idx_user_id（使用了新建的索引）
    rows: 10（预估扫描行数大幅减少）

概念：EXPLAIN可以帮助你了解 MySQL 是如何处理一条 SQL 语句的（比如如何连接表、是否使用索引、扫描了多少行数据等），从而优化查询性能。
1. type（连接类型）     表示 MySQL 访问表的方式，直接反映查询效率，从优到劣常见类型：
    system：        表中只有一行数据（如系统表），极少出现。
    const：         通过主键或唯一索引查询，最多返回一行，效率极高。
        示例：SELECT * FROM users WHERE id = 1;（id 是主键）
    eq_ref：        多表连接时，右表通过主键或唯一索引匹配左表，每行只匹配一次（如 INNER JOIN 用主键关联）。
    ref：           非唯一索引匹配，可能返回多行（如普通索引查询）。
    range：         索引范围查询            （如 WHERE age BETWEEN 18 AND 30 或 id > 100）。
    index：         扫描整个索引树          （比全表扫描略好，但仍低效）。
    ALL：           全表扫描                （最差，需优化）。
优化目标：至少达到 range 级别，最好要出现 ALL（全表扫描）。 

2. key（使用的索引）
显示 MySQL 实际使用的索引名称。如果为 NULL，表示未使用任何索引（可能需要添加索引优化）。

3. rows（估计扫描行数）
MySQL 预估需要扫描的行数（非精确值）。数值越小，查询效率越高。如果 rows 远大于实际数据量，可能是索引失效或统计信息过时。

4. Extra（额外信息）
包含优化的关键细节，常见重要值：
#       4.2:TRANSACTION     事务 
举个例子 比如说转账系统中需要两边同步 如果一边出错了另一边也要回滚

        |    id	  name	  balance
        |    1	  张三	  1000
        |    2	  李四	  1000

                -- 1. 开启事务
        START TRANSACTION;

                -- 2. 执行操作（两步必须同时成功）
                -- 张三账户扣款 500
        UPDATE accounts SET balance = balance - 500 WHERE id = 1;
                -- 李四账户收款 500
        UPDATE accounts SET balance = balance + 500 WHERE id = 2;

                -- 3. 检查操作是否正确（实际开发中可能有业务逻辑判断）
                -- 若正确，提交事务（数据生效）
        COMMIT;
                -- 若错误（如余额不足），回滚事务（恢复原状）
                -- ROLLBACK;

当多个事务同时操作同一批数据时，可能出现以下问题：
    脏读：读取到其他事务未提交的临时数据（可能被回滚）。
    不可重复读：同一事务内，多次读取同一数据结果不一致（被其他事务修改并提交）。
    幻读：同一事务内，多次查询结果行数不一致（被其他事务插入 / 删除数据）。

MySQL 通过隔离级别解决这些问题，从低到高为：
    READ UNCOMMITTED（读未提交）：允许脏读，性能最高，安全性最低。
    READ COMMITTED（读已提交）：避免脏读，允许不可重复读和幻读（多数数据库默认级别）。
    REPEATABLE READ（可重复读）：避免脏读和不可重复读，允许幻读（MySQL 默认级别）。
    SERIALIZABLE（串行化）：完全避免所有问题，但并发性能极差（强制事务排队执行）。

查看和设置隔离级别：
    -- 查看当前隔离级别
    SELECT @@transaction_isolation;

    -- 设置全局隔离级别（需重启会话生效）
    SET GLOBAL transaction_isolation = 'READ COMMITTED';

    -- 设置当前会话隔离级别
    SET SESSION transaction_isolation = 'REPEATABLE READ';
#       4.4:GRANT           数据库权限管理的核心工具        用户分配权限
    为指定用户授予特定权限（如 SELECT、INSERT、ALTER 等）。
    权限可精确到全局、数据库、表、列甚至存储过程等不同级别。
用法：
    GRANT 权限列表 ON 作用范围 TO '用户名'@'主机名' [IDENTIFIED BY '密码'] [WITH GRANT OPTION];
    作用范围：指定权限生效的范围（如全局 *.*、某个数据库 db_name.*、某个表 db_name.tbl_name）。
        '用户名'@'主机名'：指定用户及允许登录的主机（% 表示任意主机，localhost 仅本地）。
        IDENTIFIED BY '密码'：可选，创建用户时同时设置密码（若用户已存在，可省略）。
        WITH GRANT OPTION：可选，允许该用户将自己的权限授予其他用户（慎用）。

1. 授予所有权限（除 GRANT OPTION 外）：
    GRANT ALL PRIVILEGES ON *.* TO 'test_user'@'%' IDENTIFIED BY '123456';

2. 数据库级权限（仅对某数据库生效）         授予对 shop_db 数据库的查询、插入、更新权限：
    GRANT SELECT, INSERT, UPDATE ON shop_db.* TO 'test_user'@'%';

3. 表级权限（仅对某表生效）                授予对 shop_db 数据库中 products 表的删除和修改权限：
    GRANT DELETE, ALTER ON shop_db.products TO 'test_user'@'%';

4. 列级权限（仅对某表的特定列生效）         授予对 users 表中 name 和 age 列的更新权限：
    GRANT UPDATE (name, age) ON shop_db.users TO 'test_user'@'%';

5. 授予权限同时允许传播（谨慎使用）         允许 test_user 将自己的权限授予其他用户：
        GRANT SELECT ON shop_db.* TO 'test_user'@'%' WITH GRANT OPTION;
    刷新权限：修改权限后，需执行以下语句使权限立即生效（否则需等待会话重建）：  
        FLUSH PRIVILEGES;
    查看用户权限：
        SHOW GRANTS FOR 'test_user'@'%';

常用权限说明
    权限名	                作用
    SELECT	            允许查询表数据
    INSERT	            允许插入数据
    UPDATE	            允许修改数据
    DELETE	            允许删除数据
    ALTER	            允许修改表结构（ALTER TABLE）
    CREATE	            允许创建数据库 / 表
    DROP	            允许删除数据库 / 表
    GRANT OPTION	    允许授予自己拥有的权限给其他用户
    ALL PRIVILEGES	    所有权限（除 GRANT OPTION 需单独指定）

6. 回收权限：
    REVOKE DELETE ON shop_db.products FROM 'test_user'@'%';
#       4.5:REVOKE          回收已授予用户的权限
    REVOKE 权限列表 ON 作用范围 FROM '用户名'@'主机名';

1. 回收全局权限
    之前授予
        GRANT ALL PRIVILEGES ON *.* TO 'test_user'@'%';
    现在回收
        REVOKE DELETE ON *.* FROM 'test_user'@'%';

2. 回收数据库级权限
    REVOKE INSERT ON shop_db.* FROM 'test_user'@'%';

3. 回收表级权限
    REVOKE ALL PRIVILEGES ON shop_db.products FROM 'test_user'@'%';

4. 回收权限传播能力
    REVOKE GRANT OPTION ON shop_db.* FROM 'test_user'@'%';

5. 回收所有权限
    REVOKE ALL PRIVILEGES, GRANT OPTION FROM 'test_user'@'%';


#   1.5：高级操作
#       5.1:UNION           “张三”在两表都存在，但行数据不同，不会被去重
-- 合并学生和教师的信息，自动去除重复行（此处“张三”在两表都存在，但行数据不同，不会被去重）
    SELECT id, name, age, role FROM students
    UNION
    SELECT id, name, age, role FROM teachers;
#       5.2:UPDATE
1. 更新单行
    假设有 users 表：
            id	        name	        age	        status
            1	        张三	        20	            0
            2	        李四	        22	            1
            3	        王五	        25	            0
    改张三年龄为21：
        UPDATE users
        SET age = 21
        WHERE id = 1;  -- 用主键精准定位单行
2. 更新多行
    所有人的status哦
    UPDATE users
    SET age = 23, status = 0
    WHERE name = '李四';
3. 全场景更新
    UPDATE users SET status = 0;  -- 会修改表中所有行！
示例：多表关联更新
    假设有 orders 表（订单）和 users 表（用户），需根据用户等级更新订单折扣：
        users 表：id、level（用户等级：1 - 普通，2 - 会员）
        orders 表：order_id、user_id（关联 users.id）、discount（折扣，默认 0.95）
    需求：为会员用户（level=2）的订单设置折扣为 0.85。
        UPDATE orders o
        JOIN users u ON o.user_id = u.id  -- 关联订单和用户
        SET o.discount = 0.85  -- 更新订单折扣
        WHERE u.level = 2;  -- 只更新会员的订单
#       5.3:DELETE
1. 单表删除
    DELETE FROM 表名
    WHERE id = 2;  -- 用主键精准删除单行;  -- 可选，指定删除哪些行（无条件则删除全表数据）
2. 多表关联删除
    DELETE o  -- 只删除订单表的记录（o 是 orders 的别名）
    FROM orders o
    JOIN users u ON o.user_id = u.id  -- 关联订单和用户
    WHERE u.is_deleted = 1;  -- 只删除已注销用户的订单
3. 事务保护、
    START TRANSACTION;
    DELETE FROM users WHERE id = 2;
    -- 确认无误后提交
    COMMIT;
    -- 若出错，回滚（数据恢复）
    -- ROLLBACK;
4. 自增主键重置
    DELETE FROM users;
    ALTER TABLE users AUTO_INCREMENT = 1;  -- 重置自增ID为1
#   1.6：数据操作语句
#       6.1:INSERT INTO     插入
1. 简单插入
    INSERT INTO 表名 (列1, 列2, ...)
    VALUES 
    (值1-1, 值1-2, ...),  -- 第一行数据
    (值2-1, 值2-2, ...),  -- 第二行数据
    ...;  -- 更多行
2. 从其他表格复制
    INSERT INTO users (name, age, status)
    SELECT name, age, 1 FROM temp_users WHERE age > 18;
3. 事务包裹
    重要数据插入建议用事务，确保批量插入要么全部成功，要么全部失败：
        START TRANSACTION;
        INSERT INTO users (name) VALUES ('钱七');
        INSERT INTO users (name) VALUES ('孙八');
        COMMIT;  -- 全部成功则提交
        -- 若出错，执行 ROLLBACK; 回滚   
4. 处理与主键冲突
    -- 若 id=1 已存在，则更新 name 和 age；否则插入新记录
    INSERT INTO users (id, name, age)
    VALUES (1, '张三', 21)
    ON DUPLICATE KEY UPDATE 
        name = VALUES(name),  -- 用插入的 name 更新
        age = VALUES(age);    -- 用插入的 age 更新


#   1.7：函数与聚合操作
#       7.1:COUNT           统计
示例：
    id	        name	        age	        email	
    1	        张三	        20	        zhang@test.com	
    2	        李四	        NULL	    NULL	            （age 和 email 为 NULL）
    3	        王五	        25	        wang@test.com	
    4	        赵六	        20	        NULL	            （email 为 NULL）
1. 全体统计 
    SELECT COUNT(*) FROM users;                                 -- 结果：4（共4行记录，包括含NULL的行）
2. 统计非NULL 
    SELECT COUNT(age) FROM users;                               -- 结果：3（id=1、3、4 的 age 非 NULL）
3. 先去重
    SELECT COUNT(DISTINCT age) FROM users;  -- 结果：2
4. 统计符合：
    SELECT COUNT(*) FROM users WHERE age >= 20;  -- 结果：3
#       7.2:SUM             
举个栗子：

        order_id	        user_id	        amount	        quantity	      status	
        1	                1	                300	            2	           1	（金额 300，数量 2）
        2	                1	                200	            1	           1	
        3	                2	                500	            NULL	       1	（quantity 为 NULL）
        4	                2	                500	            3	           0	（status=0，未完成）
        5	                3	                NULL	        2	           1	（amount 为 NULL）

1. 简单操作     计算所有有效订单（status=1）的总金额（amount）：
    SELECT SUM(amount) AS total_amount
    FROM orders
    WHERE status = 1;
2. 计算操作     计算所有有效订单的 “总金额 × 数量”（即总价）：
    SELECT SUM(amount * quantity) AS total_price
    FROM orders
    WHERE status = 1;
3. 去重求和     计算所有不重复金额（amount）的总和（忽略重复值）：
    SELECT SUM(DISTINCT amount) AS distinct_amount_sum
    FROM orders
    WHERE status = 1;
4. 分组求和     按用户（user_id）统计各自的总订单金额：
    SELECT 
        user_id, 
        SUM(amount) AS user_total  -- 按user_id分组求和
    FROM orders
    WHERE status = 1
    GROUP BY user_id;
结果：
        user_id	        user_total	
            1	            500	            （300 + 200）
            2	            500	            （仅 order_id=3 的 500）
            3	            NULL
#       7.3:AVG             （总和 ÷ 非 NULL 值的行数）
简单求和
    SELECT AVG(score) AS math_avg
    FROM scores
    WHERE subject = '数学';

分组求和
    SELECT 
        student_id, 
        AVG(score) AS student_avg  -- 按学生分组求平均
    FROM scores
    GROUP BY student_id;
#       7.4:MIN
SELECT MIN(price) AS min_price FROM products;
#       7.5:MAX